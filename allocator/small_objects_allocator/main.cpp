// main.cpp
/*
  Implementation of an allocator

  Problem Statement: overhead of the standard allocator when
  allocating a huge amount of "small objects".

  "In addition to being slow, the genericity of the default C++ allocator makes
  it very space inefficient for small objects. The default allocator manages a
  pool of memory, and such management often requires some extra memory. Usually,
  the bookkeeping memory amounts to a few extra bytes (4 to 32) for each block
  allocated with new. If you allocate 1024-byte blocks, the per-block space
  overhead is insignificant (0.4% to 3%). If you allocate 8-byte objects, the
  per-object overhead becomes 50% to 400%, a figure big enough to make you worry
  if you allocate many such small objects.

  (...)

  Therefore, for poor performance of the default allocator makes it a bump on
  the road toward efficient C++ programs. Seasoned C++ programmers instintively
  avoid constructs that foster using free store allocation because they know
  its costs from experience."

  "SmallObjectAllocator provides general allocation and deallocation functions.
  A SmallObjectAllocator holds several FixedAllocator objects, each specialized
  for allocating objects of one size. Depending on the number of bytes
  requested, SmallObjectAllocator dispatches memory allocation requests to one
  of its FixedAllocators or to the default::operator new if the size requested
  is too large."

  +---------------------------------------------------------------+
  | SmallObject            Object-level services                  |
  |                        Transparent - you derive your classes  | Layer 4
  |                        only from SmallObject                  |
  +---------------------------------------------------------------+
  | SmallObjectAllocator   Able to allocate small objects of      |
  |                        various sizes                          | Layer 3
  |                        Configurable parameters                |
  +---------------------------------------------------------------+
  | FixedAllocator         Allocates only objects of one given    |
  |                        size                                   | Layer 2
  |                                                               |
  +---------------------------------------------------------------+
  | Chunk                  Allocates objects of one given size    |
  |                        Has a fixed upper limit of number of   | Layer 1
  |                        objects allocated                      |
  +---------------------------------------------------------------+

  For efficiency reason Chunk does not define constructors or destructors,
  everything is public -> struct. Defining even proper copy mechanisms at this
  level hurts efficiency at upper levels, where we store Chunk objects in a
  vector.

  Taken from "Modern C++ Design", Alexandrescu

  "(...) You will note that it works best for single alloation of a fixed size
  (for allocation of different sizes, they actually create different internal
  allocators). Thus, it would not work well with std::vector or other similar
  containers that does allocation of a block of memory (and of varied size)."

  "This implementation is actually not thread-safe by itself."

  Taken from "http://www.codeproject.om/KB/cpp/allocator.aspx"


  Usage:
      allocation of memory
      SmallObject<DEFAULT_CHUNK_SIZE, MAX_SMALL_OBJECT_SIZE>::operator new( size_of_pointer);

      calls:
      SmallObject<>::operator new()
        \-->SmallObject::MySmalObjectAllocator::allocate() else ::operator new()
            \-->SmallObjectAllocator::allocate()
               \-->FixedAllocator::allocate()
                  \-->FixedAllocator::Chunk::allocate()
                  [list handling of FixedAllocator::Chunk]


      free of memory
      SmallObject<DEFAULT_CHUNK_SIZE, MAX_SMALL_OBJECT_SIZE>::operator delete( ptr, sizeof(*ptr));

      calls:
      SmallObject<>::operator delete()
        \-->SmallObjectAllocator::MySmallObjectAllocator::deallocate()
           \-->SmalObjectAllocator::deallocate()
              \-->FixedAllocator::deallocate()
                 \-->FixedAllocator::doDeallocate()
                    \-->FixedAllocator::Chunk::deallocate()
//*/


#include <iostream>


#include "smallobject.hpp"


/*
  in case uncomment this to check serial allocation of elements
//*/
//#define SERIAL_ALLOCATION


/*
  forward declaration of static Member - supposed to be called once: here!
//*/
SmallObject::SmallObjectAllocator_t
  SmallObject::smallObjectAllocator;


int main()
{
  using namespace std;

  // init
  unsigned long int *ptr = NULL;


  // allocate
  cout << "\nallocat test: single allocation...\n";
  std::size_t ptrSiz = sizeof( *ptr);
  ptr = static_cast< unsigned long int* >( SmallObject::operator new( ptrSiz));
  cout << "\nok.\n"
       << endl;

  // write something into
  cout << "\ninitialize allocated memory...\n";
  *ptr = 1234567890;
  cout << "*ptr = " << *ptr << endl;
  cout << "\nok.\n"
       << endl;

  // delete
  cout << "\nfree allocated memory...\n";
  SmallObject::operator delete( ptr, sizeof(*ptr)); ptr = NULL;
  cout << "\nok.\n"
       << endl;


#ifdef SERIAL_ALLOCATION

  // serial allocation
  cout << "\nallocate / delete test: several allocations...";

  int idx=0;
  for(idx = 1; idx < 10; ++idx){

    // allocate
    cout << "\nallocat test: single allocation...\n";
    ptr = static_cast< unsigned long int* >( SmallObject::operator new( sizeof(*ptr)));
    cout << "\nok.\n"
         << endl;

    // write something into
    cout << "\ninitialize allocated memory...\n";
    *ptr = 1234567890;
    cout << "\nok.\n"
         << endl;

    // delete
    cout << "\nfree allocated memory...\n";
    SmallObject::operator delete( ptr, sizeof(*ptr)); ptr = NULL;
    cout << "\nok.\n"
         << endl;
  }
#endif


  cout << "READY.\n";
  return 0;
}

