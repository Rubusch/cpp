// smallobjectallocator.cpp
/*
//*/


#include <algorithm>
#include <cassert>
#include <iostream>


#include "smallobjectallocator.hpp"


/*
  creates an allocator for small objects given Chunk size
  and maximum 'small' object size
//*/
SmallObjectAllocator::SmallObjectAllocator(std::size_t chunkSize,
                                           std::size_t maxObjectSize)
    : pLastAlloc_(NULL), pLastDealloc_(NULL), chunkSize_(chunkSize),
      maxObjectSize_(maxObjectSize)
{
  std::cout << "\t\tSmallObjectAllocator::SmallObjectAllocator( std::size_t "
               "chunkSize, std::size_t maxObjectSize) - ctor\n";
}


/*
  allocates 'numBytes' memory uses an internal pool of
  FixedAllocator objects for small objects
//*/
void *SmallObjectAllocator::allocate(std::size_t numBytes)
{
  std::cout << "\t\tSmallObjectAllocator::allocate( std::size_t numBytes)\n";

  // use default allocator if size execedes capacity of Small Object Allocator
  if (numBytes > maxObjectSize_)
    return operator new(numBytes);

  // if final pointer exists and number of allocated bytes is correct, allocate
  if (pLastAlloc_ && (pLastAlloc_->blockSize() == numBytes)) {
    return pLastAlloc_->allocate();
  }

  // else set up iterator,...
  Pool::iterator iter = std::lower_bound(pool_.begin(), pool_.end(), numBytes);
  if ((iter == pool_.end()) || (iter->blockSize() != numBytes)) {
    iter = pool_.insert(iter, FixedAllocator(numBytes));
    pLastDealloc_ = &*pool_.begin();
  }

  // ...init iterator...
  pLastAlloc_ = &*iter;

  // ...and allocate memory
  return pLastAlloc_->allocate();
}


/*
  deallocates memory previously allocated with allocate
  (undefined behaviour if you pass any other pointer)
//*/
void SmallObjectAllocator::deallocate(void *ptr, std::size_t numBytes)
{
  std::cout << "\t\tSmallObjectAllocator::deallocate( void* ptr, std::size_t "
               "numBytes)\n";

  // of the allocated blocks exceeded the amount of pre-allocated blocks,
  // return the ::operator delete()
  if (numBytes > maxObjectSize_)
    return operator delete(ptr);

  // if final dealloc pointer exists, and amounts of blocks is ok, deallocate
  if (pLastDealloc_ && (pLastDealloc_->blockSize() == numBytes)) {
    pLastDealloc_->deallocate(ptr);
    return;
  }

  // else create iterator to the final position...
  Pool::iterator iter = std::lower_bound(pool_.begin(), pool_.end(), numBytes);

  // ...check it...
  assert(iter != pool_.end());
  assert(iter->blockSize() == numBytes);

  // ...init it...
  pLastDealloc_ = &*iter;

  // ...and free the memory to the last position of the alloc list
  pLastDealloc_->deallocate(ptr);
}
