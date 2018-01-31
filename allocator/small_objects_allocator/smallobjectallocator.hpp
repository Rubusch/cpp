// smallobjectallocator.hpp
/*
  Layer 3 - SmallObjectAllocator

  Offers services for allocating small-sized objects

  The third layer in our architecture consists of SmallObjectAllocator,
  a class capable of allocating objects of any size. SmallObjectAllocator
  does so by aggregating several FixedAllocator objects. When
  SmallObjectAllocator receives an allocation request, it either forwards
  it to the best matching Fixedallocator object or passes it to the default
  ::operator new().
//*/

#ifndef SMALL_OBJECT_ALLOCATOR
#define SMALL_OBJECT_ALLOCATOR


#include <vector>


#include "fixedallocator.hpp"


class SmallObjectAllocator
{
private:
  // forbit copying, etc - only declaration as private!
  SmallObjectAllocator( const SmallObjectAllocator&);
  SmallObjectAllocator& operator=( SmallObjectAllocator const&);

  // pool = std::vector< FixedAllocator >
  typedef std::vector< FixedAllocator > Pool;
  Pool pool_;

  FixedAllocator* pLastAlloc_;
  FixedAllocator* pLastDealloc_;
  std::size_t chunkSize_;
  std::size_t maxObjectSize_;

public:
  SmallObjectAllocator( std::size_t chunkSize, std::size_t maxObjectSize);

  void* allocate( std::size_t numBytes);
  void deallocate( void* ptr, std::size_t numBytes);
};

#endif
