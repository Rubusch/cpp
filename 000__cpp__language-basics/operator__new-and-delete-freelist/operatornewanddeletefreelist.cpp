// freelist.cpp
/*
  - Demonstrates the usage of a ::operator new() and ::operator delete() using a
free list
  - The freelist implementation uses the default memory pool

  overloading "new" and "delete" allows to allocate less memory than using the
global
  "::operator new()" and is probably even faster.


  1. understanding issues: "operator delete() doesn't call delete to free the
memory?!"

  Answer: "Listen to me carefully: there is no memory leak.

  A memory leak arises when memory is allocated, then all pointers to that
memory are lost. Absent garbage collection or some other extralinguistic
mechanism, such memory cannot be reclaimed. But this design has no memory leak,
because it's never the case that all pointers to memory are lost. Each big block
of memory is first broken down into Foobar-sized chunks, and these chunks are
then placed

  on the free list. When clients call Foobar::operator new, chunks are removed
from the free list, and clients receive pointers to them. When clients call
operator delete, the chunks are put back on the free list. With this design, all
memory chunks are either in use as Foobar objects (in which case it's the
clients' responsibility to avoid leaking their memory) or are on the free list
(in which case there's a pointer to the memory). There is no memory leak.

  Nevertheless, the blocks of memory returned by ::operator new are never
released by Foobar::operator delete, and there has to be some name for that.
There is. You've created a memory pool. Call it semantic gymnastics if you must,
but there is an important difference between a memory leak and a memory pool. A
memory leak may grow indefinitely, even if clients are wellbehaved, but a memory
pool never grows larger than the maximum amount of memory requested by its
clients."

  Scott Meyers, Effective C++, Item 10


  2. it's easy here to introduce something like a garbage collection to free the
memory automatically when it's not used anymore, but this definitely will slow
down the proggy. The memory pool is the prefered (and common) strategy here!
//*/


#include <iostream>
#include <new> // if <new> doesn't compile, try <new.h>


class FoobarRepresentation
{
  // ...
};


/*
  declare a class with "operator new()" and "operator delete()"
//*/
class Foobar
{
public:
  static void *operator new(size_t size);
  static void operator delete(void *rawDeadObj, size_t size);
  // ...

private:
  union {
    FoobarRepresentation *rep; // allocated objs
    Foobar *next;              // objs in the freelist
  };

  // this class specific constant tells how many objs fit in one memory block
  static const int BLOCK_SIZE;

  // head
  static Foobar *headOfFreeList;
};


/*
  init the static data elements and define the functions
//*/
Foobar *Foobar::headOfFreeList; // headOfFreeList doesn't need explicitely to be
                                // set to NULL
const int Foobar::BLOCK_SIZE = 512;

void *Foobar::operator new(size_t size)
{
  std::cerr << "I am the overloaded Foobar::operator new()"
            << std::endl; // some comment

  // check size
  if (size != sizeof(Foobar))
    return ::operator new(size);

  Foobar *ptr = headOfFreeList;

  if (ptr) {
    headOfFreeList = ptr->next;
  } else {
    // freelist is empty, thus allocate another memory block
    Foobar *newBlock =
        static_cast< Foobar * >(::operator new(BLOCK_SIZE * sizeof(Foobar)));

    // create new freelist, but exclude 0. element (head), the 0. element will
    // be returned
    for (int idx = 1; idx < BLOCK_SIZE - 1; ++idx) {
      newBlock[idx].next = &newBlock[idx + 1];
    }

    // terminate with NULL
    newBlock[BLOCK_SIZE - 1].next = 0;

    // set ptr to the first memory block, as also headOfFreeList
    ptr = newBlock;
    headOfFreeList = &newBlock[1];
  }

  return ptr;
}

void Foobar::operator delete(void *rawDeadObj, size_t size)
{
  std::cerr << "I am the overloaded Foobar::operator delete()"
            << std::endl; // some comment

  // check
  if (NULL == rawDeadObj)
    return;

  if (size != sizeof(Foobar)) {
    ::operator delete(rawDeadObj);
    return;
  }

  Foobar *deadObj = static_cast< Foobar * >(rawDeadObj);

  // reset the start of the freelist and the next pointer
  deadObj->next = headOfFreeList;
  headOfFreeList = deadObj;
}


/*
  usage of the freelist
//*/
int main()
{
  Foobar *pFoobar = new Foobar;

  // do something...

  delete pFoobar;
  pFoobar = NULL;

  // allocate new memory for the same pointer
  pFoobar = new Foobar;

  // do something...

  delete pFoobar;
  pFoobar = NULL;

  std::cout << "READY.\n" << std::endl;
  return 0;
}
