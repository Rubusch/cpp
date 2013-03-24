// fixedallocator.cpp
/*
//*/

#include <iostream>
#include <cassert>
#include <climits>

#include "fixedallocator.hpp"
#include "smallobject.hpp"


/***************************** Chunks ********************************************************/


/*
  init() initializes a Chunk object
//*/
void FixedAllocator::Chunk_t::init( std::size_t blockSize, unsigned char blocks)
{
  std::cout << "\t\t\tFixedAllocator::Chunk_t::init( std::size_t blockSize, unsigned char blocks)\n";

  // checks
  assert( blockSize > 0);
  assert( blocks > 0);
  assert( (blockSize * blocks) / blockSize == blocks); // overflow check (we are unsigned!)

  // allocate a huge amount of space for data pointer using ::operator new(), this
  // will be splitted in equal blocks to provide it as pool memory
  pData_ = new unsigned char[blockSize * blocks];
  firstAvailableBlock_ = 0;
  blocksAvailable_ = blocks;

  unsigned char idx = 0;
  unsigned char* ptr = pData_;
  for(; idx != blocks; ptr += blockSize){
    *ptr = ++idx;
  }
}


/*
  the allocate() function allocates a block from a Chunk

  you have to pass a size to allocate and to 
  deallocate because Chunk does not hold it
//*/
void* FixedAllocator::Chunk_t::allocate( std::size_t blockSize)
{
  std::cout << "\t\t\tFixedAllocator::Chunk_t::allocate( std::size_t blockSize)\n";

  if( !blocksAvailable_) return 0; 
  
  // overflow check to avoid "unsigned" issues
  if( (firstAvailableBlock_ * blockSize) / blockSize != firstAvailableBlock_) return 0;
  
  unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
  
  // Update firstAvailableBlock_ to point to the next block
  firstAvailableBlock_ = *pResult;
  --blocksAvailable_;

  return pResult;
}


/*
  deallocate() deallocates a block from a Chunk

  you have to pass a size to allocate and to 
  deallocate because Chunk does not hold it
//*/
void FixedAllocator::Chunk_t::deallocate( void* ptr, std::size_t blockSize)
{
  std::cout << "\t\t\tFixedAllocator::Chunk_t::deallocate( void* ptr, std::size_t blockSize)\n";

  // check void*
  assert(ptr >= pData_);
  unsigned char* toRelease = static_cast< unsigned char* >(ptr);
  
  // alignement check
  assert( (toRelease - pData_) % blockSize == 0);
  *toRelease = firstAvailableBlock_;
  firstAvailableBlock_ = static_cast< unsigned char >( (toRelease - pData_) / blockSize);
  
  // truncation check
  assert( firstAvailableBlock_ == (toRelease - pData_) / blockSize);
  ++blocksAvailable_;
}


/*
  release() releases the allocated memory
//*/
void FixedAllocator::Chunk_t::release()
{
  std::cout << "\t\t\tFixedAllocator::Chunk_t::release()\n";
  delete[] pData_;
}


/***************************** FixedAllocator ************************************************/


/*
  performs deallocation, assuming deallocChunk_ points to the correct Chunk
//*/
void FixedAllocator::doDeallocate(void* ptr)
{
  std::cout << "\t\t\tFixedAllocator::doDeallocate(void* ptr)\n";

  // checks
  assert( ptr >= deallocChunk_->pData_);
  assert( ptr < deallocChunk_->pData_ + numBlocks_ * blockSize_);

  // call into the Chunk, will adjust the inner list but won't release memory
  deallocChunk_->deallocate( ptr, blockSize_);
  
  if( deallocChunk_->blocksAvailable_ == numBlocks_){
    Chunk& lastChunk = chunks_.back();

    if( &lastChunk == deallocChunk_){
      // check if we have two last Chunks empty
      if( chunks_.size() > 1 && deallocChunk_[-1].blocksAvailable_ == numBlocks_){
        // two free Chunks, discard the last one
        lastChunk.release();
        chunks_.pop_back();
        allocChunk_ = deallocChunk_ = &chunks_.front();
      }
      return;
    }

    if(lastChunk.blocksAvailable_ == numBlocks_){
      // two free blocks, discard one
      lastChunk.release();
      chunks_.pop_back();
      allocChunk_ = deallocChunk_;
    }else{
      // move the empty Chunk to the end
      std::swap( *deallocChunk_, lastChunk);
      allocChunk_ = &chunks_.back();
    }
  }
}


/*
  finds the Chunk corresponding to a pointer, using an efficient search
//*/
FixedAllocator::Chunk_t* FixedAllocator::vicinityFind(void* ptr)
{
  std::cout << "\t\t\tFixedAllocator::Chunk_t* FixedAllocator::vicinityFind(void* ptr)\n";
  
  // checks
  assert( !chunks_.empty());
  assert( deallocChunk_);
  
  const std::size_t chunkLength = numBlocks_ *blockSize_;
  
  Chunk* lo = deallocChunk_;
  Chunk* hi = deallocChunk_ + 1;
  Chunk* loBound = &chunks_.front();
  Chunk* hiBound = &chunks_.back() + 1;

  for(;;){
    /*
      check lo
    //*/
    if( lo){
      // return lo if element starts at lo->pData_ and is within chunkLength size
      if( (ptr >= lo->pData_) && (ptr < lo->pData_ + chunkLength)){
        return lo;
      }

      // increment search
      if( lo == loBound) lo = 0;
      else --lo;
    }

    /*
      in parallel check hi
    //*/
    if( hi){
      // return hi if element starts at hi->pData_ and is within chunkLength size
      if( (ptr >= hi->pData_) && (ptr < hi->pData_ + chunkLength)){
        return hi;
      }
      
      // increment search
      if( ++hi == hiBound) hi = 0;
    }
  }
  
  // something failed!
  assert( false);
  return NULL;
} 


/*
  constructor creates a FixedAllocator object of a fixed block size
  
  blockSize is the size of the whole block
  at a single allocation, only this "blockSize" will be allocated as amount of blocks,
  on the other side this also results in a group of equal sized blocks 
  (at maximum blockSize of size, then ::operator new() will allocate new space)
//*/
FixedAllocator::FixedAllocator(std::size_t blockSize)
  : blockSize_( blockSize)
  , allocChunk_(NULL)
  , deallocChunk_(NULL)
{
  std::cout << "\t\t\tFixedAllocator::FixedAllocator(std::size_t blockSize) - ctor\n";

  // checks
  assert( blockSize_ > 0);

  // reset the list pointers
  prev_ = next_ = this;

  // calculate number of blocks with numBlocks temp variable
  std::size_t numBlocks = DEFAULT_CHUNK_SIZE / blockSize;

  // check if cast of numBlocks from std::size_t is "ok"
  if( numBlocks > UCHAR_MAX) numBlocks = UCHAR_MAX;
  else if( numBlocks == 0) numBlocks = 8 * blockSize;

  // cast to uchar
  numBlocks_ = static_cast< unsigned char >(numBlocks);

  // if writing numBlocks to the class member fails -> assert fails!
  assert(numBlocks_ == numBlocks);
}


/*
  copy ctor - creates a FixedAllocator object of a fixed block size
//*/
FixedAllocator::FixedAllocator(FixedAllocator const& copy)
  : blockSize_( copy.blockSize_)
    , numBlocks_( copy.numBlocks_)
    , chunks_( copy.chunks_)
{
  std::cout << "\t\t\tFixedAllocator::FixedAllocator(FixedAllocator const& copy) - cpy ctor\n";

  prev_ = &copy;
  next_ = copy.next_;
  copy.next_->prev_ = this;
  copy.next_ = this;

  // copying contents
  allocChunk_ = copy.allocChunk_;
  deallocChunk_ = copy.deallocChunk_;
}


/*
  basically perform the same copy like in the copy ctor
//*/
FixedAllocator& FixedAllocator::operator=(const FixedAllocator& rhs)
{
  std::cout << "\t\t\tFixedAllocator& FixedAllocator::operator=(const FixedAllocator& rhs)\n";

  FixedAllocator copy( rhs);
  copy.swap( *this);
  return *this;
}


/*
  dtor
//*/
FixedAllocator::~FixedAllocator()
{
  std::cout << "\t\t\tFixedAllocator::~FixedAllocator() - dtor\n";

  if(prev_ != this){
    prev_->next_ = next_;
    next_->prev_ = prev_;
    return;
  }

  assert( prev_ == next_);
  Chunks::iterator iter = chunks_.begin();
  for(; iter != chunks_.end(); ++iter){
    assert( iter->blocksAvailable_ == numBlocks_);
    iter->release();
  }
}


/*
  swap
//*/
void FixedAllocator::swap(FixedAllocator& rhs)
{  
  std::cout << "\t\t\tFixedAllocator::swap(FixedAllocator& rhs)\n";

  std::swap( blockSize_, rhs.blockSize_);
  std::swap( numBlocks_, rhs.numBlocks_);

  // uses vector<>::swap()
  chunks_.swap(rhs.chunks_);

  std::swap( allocChunk_, rhs.allocChunk_);
  std::swap( deallocChunk_, rhs.deallocChunk_);
}


/*
  Only when the cache is depleted does FixedAllocator need to go the 
  standard route by forwarding the allocation nrequest to a Chunk. 
  This is a promising strategy, but it works badly with certain 
  allocation and deallocation trends that are common to small-object 
  use.

  There are four main trends in allocating small objects:

  Bulk allocation
  Many small objects are allocated at the same time. For example, this 
  is the case when you initialize a collection of pointers to small 
  objects.

  Deallocation in same order
  Many small objects are deallocated in the smae order as they were 
  allocated. This happens when most STL containers are destroyed.

  Deallocation in reverse order
  Many small objects are deallocated in the reverse order of their 
  allocation. This trend occurs naturally in C++ programs as you call 
  functions that manipulate small objects. Function arguments and 
  temporary stack variables follow this trend.

  Butterlfy allocation and deallocation
  Objects are created and destroyed without following a certain order. 
  This happens as your program is running and has occasional need for 
  small objects.
//*/
void* FixedAllocator::allocate()
{
  std::cout << "\t\t\tFixedAllocator::allocate()\n";

  if(allocChunk_ == NULL || allocChunk_->blocksAvailable_ == 0){ 

    // no available memory in this chunk, try to find one
    // remember Chunks == vector< struct Chunk > and chunks_ is and instance of that
    Chunks::iterator iter = chunks_.begin();

    for(;; ++iter){
      if( iter == chunks_.end()){
        // all filled up-add a new chunk
        chunks_.reserve(chunks_.size() +1);
        Chunk newChunk;
        newChunk.init( blockSize_, numBlocks_);
        chunks_.push_back( newChunk);
        allocChunk_ = &chunks_.back();
        deallocChunk_ = &chunks_.front();
        break;
      }
            
      if( iter->blocksAvailable_ > 0){ 
        // found a chunk
        allocChunk_ = &*iter;
        break;
      }
    }
  }
  assert( allocChunk_ != NULL);
  assert( allocChunk_->blocksAvailable_ > 0);

  return allocChunk_->allocate( blockSize_);
}
  

/*
  deallocate a memory block previsously allocated with allocate()
  (if that's not the case, the behaviour is undefined)
//*/
void FixedAllocator::deallocate(void* ptr)
{
  std::cout << "\t\t\tFixedAllocator::deallocate(void* ptr)\n";

  assert( !chunks_.empty());
  assert( &chunks_.front() <= deallocChunk_);
  assert( &chunks_.back() >= deallocChunk_);

  // find Chunk
  deallocChunk_ = vicinityFind( ptr);
  
  // check if Chunk was NOT empty
  assert( deallocChunk_);

  // call doDeallocate()
  doDeallocate( ptr);
}


/*
  returns the block size with which the FixedAllocator was initialized
//*/
std::size_t FixedAllocator::blockSize() const
{ 
  std::cout << "\t\t\tFixedAllocator::blockSize()\n";

  return blockSize_;
}
 

/*
  comparison operator for sorting
//*/
bool FixedAllocator::operator<(std::size_t rhs) const
{ 
  std::cout << "\t\t\tFixedAllocator::operator<(std::size_t rhs)\n";

  return (rhs > blockSize()); 
}
