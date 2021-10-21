// Main.cpp
/*
  new and delete

  a class has a pointer to allocated memory
  a caller allocates a pointer to that class
  the caller deletes its pointer

  variations with
  - std::shared_ptr<>()
  - new/delete

  play around with the options, use mtrace
  $ export MALLOC_TRACE="$(pwd)/out.txt"
  $ ./newdelete.exe
  $ mtrace ./out.txt

  -> when clear looks as follows (mtrace is a C tool)
  $ ./newdelete.exe && mtrace ./out.txt
    Ctor()
    Pointer to a dynamic pointee:
    some class output '77'
    delete the pointee
    Dtor()
    READY.

    Memory not freed:
    -----------------
       Address     Size     Caller
    0x01eba3d8    0x400  at 0xb6c5cb04
 */

#include <iostream>
#include <memory>
#include <mcheck.h> /* memcheck */


using namespace std;


class SomeClass
{
/*
  int *mPtr = nullptr;
/*/
  std::unique_ptr< int > mPtr;
// */

public:
  SomeClass();
  ~SomeClass();
  void output();
};

SomeClass::SomeClass()
{
  cout << "Ctor()" << endl;
/*
  mPtr = new (std::nothrow) int;
/*/
  mPtr = make_unique< int >();
// */
  *mPtr = 77;
}

SomeClass::~SomeClass()
{
   /* FIX: should have a delete to mPtr */

//   delete mPtr;
   cout << "Dtor()" << endl;
}

void
SomeClass::output() {
  cout << "some class output '" << *mPtr << "'" << endl;
}


int main()
{
  mtrace();

  // pointer to a dynamic pointee
//*
  SomeClass *ptr = new SomeClass();
/*/
  std::shared_ptr< SomeClass > ptr = std::make_shared< SomeClass >();
// */
  cout << "Pointer to a dynamic pointee: " << endl;
  ptr->output();

  cout << "delete the pointee" << endl;

  delete ptr; /* MEMLEAK: does not free ptr->mPtr */
  ptr = nullptr;

  cout << "READY." << endl;
  muntrace();

  exit(EXIT_SUCCESS);
};
