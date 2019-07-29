// fixedallocator.hpp
/*
  The class contains the Layer 0 Chunk in the Layer 1 FixedAllocator


  Offers services for allocating fixed-sized objects



  Layer 1 - FixedAllocator

  Its capacity should be limited only by the available memory. To achieve this,
  FixedAllocator aggregates a vector of Chunk objects. Whenever an allocation
  request occurs, FixedAllocator looks for a Chunk that can accommodate the
  request. If all chunks are filled up, FixedAllocator appends a new Chunk.

  FixedAllocator satisfies most of the allocations in constant time, with
  occasional slowdowns caused by finding and adding a new block.
//*/


#ifndef FIXED_ALLOCATOR
#define FIXED_ALLOCATOR


#include <vector>


class FixedAllocator
{
private:
  typedef struct Chunk
  {
    /*
      Layer 0 - Chunk

      Nothing is private - Chunk is a Plain Old Data (POD) structure
      defined inside FixedAllocator and manipulated only by it
    //*/
    void init( std::size_t blockSize, unsigned char blocks);
    void* allocate( std::size_t blockSize);
    void deallocate( void* ptr, std::size_t blockSize);
    void release();
    unsigned char* pData_;

    // index of the first block available in this chunk
    unsigned char firstAvailableBlock_;

    // number of blocks available in this chunk
    unsigned char blocksAvailable_;
  } Chunk_t;

  // internal functions
  void doDeallocate(void* ptr);
  Chunk_t* vicinityFind(void* ptr);

  // data
  std::size_t blockSize_;
  unsigned char numBlocks_;

  // use a vector< Chunk > as basic Chunk source
  typedef std::vector< Chunk > Chunks;
  Chunks chunks_;

  Chunk* allocChunk_;
  Chunk* deallocChunk_;

  // for ensuring proper copy semantics
  mutable const FixedAllocator* prev_;
  mutable const FixedAllocator* next_;

public:
  // ctors
  explicit FixedAllocator( std::size_t blockSize = 0);
  FixedAllocator( FixedAllocator const& copy);
  FixedAllocator& operator=( const FixedAllocator&);
  ~FixedAllocator();

  void swap( FixedAllocator& rhs);

  // allocate a memory block
  void* allocate();

  // deallocate a memory block previsously allocated with allocate()
  // (if that's not the case, the behaviour is undefined)
  void deallocate(void* ptr);

  // returns the block size with which the FixedAllocator was initialized
  std::size_t blockSize() const;

  // comparison operator for sorting
  bool operator<( std::size_t rhs) const;
};

#endif
