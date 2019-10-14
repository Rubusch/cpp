// smallobject.hpp
/*
  layer 4

  SmallObject overloads operator new and operator delete. This way, whenever you
  create an object derived from SmallObject, the overloads enter into action and
  route the request to the fixed allocator object.
//*/


#ifndef SMALL_OBJECT
#define SMALL_OBJECT


#include <iostream>


#include "smallobjectallocator.hpp"


// macros
#ifndef DEFAULT_CHUNK_SIZE
#define DEFAULT_CHUNK_SIZE 4096
#endif

#ifndef MAX_SMALL_OBJECT_SIZE
#define MAX_SMALL_OBJECT_SIZE 64
#endif


class SmallObject
{
private:
  /*
    layer 3 - private type definition of SmallObjectAllocator
  //*/
  struct MySmallObjectAllocator : public SmallObjectAllocator {
    MySmallObjectAllocator()
        : SmallObjectAllocator(DEFAULT_CHUNK_SIZE, MAX_SMALL_OBJECT_SIZE)
    {
      std::cout << "\tSmallObject::MySmallObjectAllocator::"
                   "MySmallObjectAllocator() - ctor\n";
    }
  };

  // typedef
  typedef struct MySmallObjectAllocator SmallObjectAllocator_t;

  // static instance
  static SmallObjectAllocator_t smallObjectAllocator;

public:
  /*
    operator new()
  //*/
  static void *operator new(std::size_t size)
  {
    std::cout << "\tSmallObject::operator new( std::size_t size)\n";
#if (MAX_SMALL_OBJECT_SIZE != 0) && (DEFAULT_CHUNK_SIZE != 0)
    return smallObjectAllocator.allocate(size);
#else
    return ::operator new(size);
#endif
  }


  /*
    operator delete()
  //*/
  static void operator delete(void *ptr, std::size_t size)
  {
    std::cout
        << "\tSmallObject::operator delete( void* ptr, std::size_t size)\n";
#if (MAX_SMALL_OBJECT_SIZE != 0) && (DEFAULT_CHUNK_SIZE != 0)
    smallObjectAllocator.deallocate(ptr, size);
#else
    ::operator delete(ptr, size);
#endif
  }


  /*
    dtor - virtual, empty
  //*/
  virtual ~SmallObject() { std::cout << "\t~SmallObject() - dtor\n"; }
};

#endif
