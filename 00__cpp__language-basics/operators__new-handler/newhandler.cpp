// newhandler.cpp
/*
  demonstrates how to implement a simple new hanlder, a new handler helps to keep on track of
  out-of-memory situations easily

  Be prepared for out-of-memory conditions. (7/Meyers)

TODO: review compilation warning
$ make
g++ -c -g -Wall newhandler.cpp
newhandler.cpp: In instantiation of ‘static void* NewHandlerSupport<T>::operator new(size_t) [with T = Foobar; size_t = long unsigned int]’:
newhandler.cpp:122:26:   required from here
newhandler.cpp:69:4: warning: catching polymorphic type ‘class std::bad_alloc’ by value [-Wcatch-value=]
   }catch(bad_alloc){
//*/


#include <iostream>
#include <string>
#include <cstdlib> // abort


// 0. includes: new definitions in local namespace
#include <new>  // if <new> doesn't compile, try <new.h>

using namespace std; // new_handler needs to be declared


template<class T>
class NewHandlerSupport;
class Foobar;

/*
  1. a simple new-handler - here only a function
//*/
void noMoreMemory()
{
  cerr << "Unable to satisfy request for memory.\n";
  abort();
}


/*
  2. new-handler support class: a class that provides the new-handler support
//*/
template<class T>
class NewHandlerSupport
{
public:
  static new_handler set_new_handler(new_handler p);
  static void* operator new(size_t size);
  // MISSING: "operator delete()" -
  // always implement a "operator delete()" when you're implementing an "operator new()"

private:
  static new_handler currentHandler;
};

template<class T>
new_handler NewHandlerSupport<T>::set_new_handler(new_handler p)
{
  new_handler oldHandler = currentHandler;
  currentHandler = p;
  return oldHandler;
}

template<class T>
void* NewHandlerSupport<T>::operator new(size_t size)
{
  // MISSING: check if size is correct!

  new_handler globalHandler = set_new_handler(currentHandler);
  void* memory;

  try{
    memory = ::operator new(size);
  }catch(bad_alloc){
    set_new_handler(globalHandler);
    throw;
  }

  set_new_handler(globalHandler);

  return memory;
}


/*
  3. a derived class: uses the new-handler support class
//*/
class Foobar : public NewHandlerSupport<Foobar>
{
  string str;

public:
  // ...some code to execute...
  void setString(string s)
  {
    str = s;
  }
  string getString()
  {
    return str;
  }

private:
  static new_handler currentHandler;
};


// 4. global reset: this inits each currentHandler with NULL
template<class T> new_handler NewHandlerSupport<T>::currentHandler;


/*
  5. usage: the new-handler in action
//*/
int main()
{

  /*
    setting the simple new-handler
  //*/


  // set noMoreMemory as new-handler for Foobar
  Foobar::set_new_handler(noMoreMemory);

  // allocate - ..a "Foobar" - if this allocation fails now, call noMoreMemory
  Foobar *pFoobar1 = new Foobar;

  // do something
  pFoobar1->setString("I have a specific new-handler!");
  cout << "pFoobar1:\t" << pFoobar1->getString() << endl;
  cout << endl;


  /*
    reference allocation with a common string and the common new-handler
  //*/


  // reference allocate - ..a (global) string with global allocator
  string *pString = new string;

  // do something
  *pString = "I am a normally allocated string!!";
  cout << "pString:\t" << *pString << endl;
  cout << endl;


  /*
    reset the simple new-handler and remove the function (set to NULL)
  //*/


  // reset the new-handler of Foobar to NULL
  Foobar::set_new_handler(NULL); // 0 == NULL

  // allocate - if this now fails, no new-handler will be called
  Foobar *pFoobar2 = new Foobar;

  // do something
  pFoobar2->setString("I again have the default new-hanlder!!!");
  cout << "pFoobar2:\t" << pFoobar2->getString() << endl;
  cout << endl;


  /*
    outro - free memory
  //*/


  delete pFoobar1; pFoobar1 = NULL;
  delete pString; pString = NULL;
  delete pFoobar2; pFoobar2 = NULL;
  cout << "READY.\n";
  return 0;
}
