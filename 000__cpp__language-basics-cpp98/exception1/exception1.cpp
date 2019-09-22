// exception.cpp
/*
  demonstrates the usage of exceptions


  exception specifications
  It is possible to implement costumized exceptions, so called "exception specifications" but generally they're
  rather considered as problematic (by 95 / meyers) and templates and exception specifications don't fit
  together!! ;-)



  Ctor

  if a constructor uses exceptions and an exception is to be thrown, the ctor has to clean up the ALREADY
  generated stuff. Partly constructed objects won't be destroyed by the destructor!

  e.g. in ctor:
  // ...
  try{
    if(imageFileName != ""){
      theImage = new Image(imageFileName);
    }
    if(audioClipFileName != ""){
      theAudioClip = new AudioClip(audioClipFileName);
    }
  }catch(...){
    delete theImage;
    delete theAudioClip;
    throw;
  }
  // ...



  Dtor

  Avoid exceptions in the descturctor (More Effective C++ / 11 / Meyers). The only possibility is to use
  uncaught_exceptions() in the destructor to catch the left thrown exceptions.



  forwarding of exception

  Exceptions can be thrown and passed by value, reference and pointer. A copy of an exception uses the static
  copy constructor! A "catch(const void*)" catches every exception which was thrown as a pointer, but exceptions
  should be thrown as reference (More Effective C++ / 13 / Meyers). References can lead to the slicing problem
  but avoid memory problems!

  e.g.:
  catch(Widget &w){
    // ...   // handle exception
    throw;   // throw exception again in order to forward
  }

  catch(Widget& w){
    // ...   // handle exception
    throw w; // throw COPY of exception in order to forward
  }



  Miscellaneous

  To pass a temporary object to a NOT constant parameter for functions is NOT allowed, but for exceptions!

  There is NO implicit type conversion for exceptions!


  ---


  EXCEPTIONS

  * If a function should forward all exceptions if it is not supposed to handle
    the exceptions or to absorb exceptions.

  * Destructors, operator delete() or operator delete[]() are supposed to handle
    exceptions and should never throw or forward an exception.

  * Basic Exception Guarantee (Dave Abrahams): Make sure that in presence of
    exceptions there are no resource leaks, already allocated memory must be
    freed at exception handling.

  * Advanced Exception Guarantee (Dave Abrahams): Keep the state unchanged at
    presence of exceptions, i.e. "go back to before the exception was thrown"
    (not possible with streams or already placed output.

  * Absolute Guarantee (Herb Sutter): Make sure no exceptions are needed.



  DEFINITIONS

  * exception safety: code still works correctly in presence of exceptions

  * exception neutrality: forwards all exceptions without integrity problems



  RESOURCES

  * Exceptional C++, Herb Sutter, 2000

//*/


#include <iostream>
#include <cstdlib> // exit()


template<class T>
class SomeClass
{
private:
  T *ptr;

public:
  // ctor
  SomeClass(T t)
    : ptr(NULL)
  {
    std::cout << "\tSomeClass::SomeClass() - ctor, allocate something\n";

    try{
      ptr = new T;
    }catch(...){ // ... catches every exception
      std::cerr << "ERROR: allocation failed" << std::endl;
      delete ptr;
      throw;
      exit(-1);
    }

    // init
    *ptr = t;
  }


  // empty ctor
  SomeClass()
    : ptr(NULL)
  {
    std::cout << "\tSomeClass::SomeClass() - ctor, NULL\n";
  }


  // dtor - since we have a dynamic pointer!
  ~SomeClass()
  {
    std::cout << "\tSomeClass::~SomeClass() - dtor\n";
    delete ptr;
    ptr = NULL;
  }


  /*
    getter

    contains the exception handling to test
  //*/
  T getVal()
  {
    std::cout << "\tSomeClass::getVal()\n";
    try{
      if(NULL == ptr){

        // throw exception
        throw "pointer was NULL";
      }

      std::cout << "\t\tTHIS IS ONLY VISIBLE WHEN NO EXCEPTION WAS THROWN!\n";
      return *ptr;
    }catch(char const* str){ // catches a thrown string exception
      std::cerr << "ERROR: " << str << std::endl;
    }

    /*
      interesting issue

      returning NULL won't compile and returning 0 would throw an internal
      BasicString exception, which would abort the proggy
    //*/
    return "*** ptr was not allocated ***";
  }
};


/*
  some main
//*/
int main()
{
  using namespace std;

  /*
    remark:
    THIS IS NOT A INSTANTIATION - THIS IS A FUNCTION CALL, THE FUNCTION DOESN'T EXIST!
    SomeClass< string > sc_1();
  //*/

  cout << "init instance 1\n";
  SomeClass< string > sc_1;
  cout << endl;

  cout << "get content:\n";
  cout << sc_1.getVal() << endl;
  cout << endl;

  cout << "init instance 2\n";
  SomeClass< string > sc_2("Hello World!");
  cout << endl;

  cout << "get content:\n";
  cout << sc_2.getVal() << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
