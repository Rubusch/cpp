// localclass.cpp
/*
  Demonstrates a Local Class in a function. Local Classes can be used to
  create trampoline functions.


  "Local clases are an interesting and little-known feature of C++. You can 
  define classes right inside functions, as follows:
  
  void func()
  {
    class Local
    {
      ... member variables ...
      ... member function definitions ...
    };
  }
  
  There are some limitations - local classes cannot define static member 
  variables and cannot access nonstatic local variables. What makes local 
  classes truly interesting is that you can use them in template functions. 
  Local classes defined inside template functions can use the template 
  parameters of the enclosing function.

  Local Classes do have a unique feature, though: They are final."
  
  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>
#include <cstdlib>


using namespace std;


/*
  Abstract Interface class to be derived later on
//*/
class Interface
{
public:
  virtual void doSomething() = 0;
};


/*
  Some function, that returns the Local Class instance
//*/
template<class T, class P>
Interface* MakeAdapter(const T& arg1, const P& arg2)
{

  /*
    Local class instanciated here - just one implementation of the
    interface
  //*/
  class LocalClass : public Interface
  {
  private:
    T arg1_;
    P arg2_;

  public:
    LocalClass(const T& arg1, const P& arg2)
      : arg1_(arg1), arg2_(arg2)
    {
      std::cout << "Local Class initialized.\n";
    }

    ~LocalClass()
    {
      std::cout << "Local Class deleted\n";
    }     

    virtual void doSomething()
    {
      std::cout << "Local Class has received two arguments:\n\t"
                << "LocalClass::arg1_ = " << arg1_ << "\n\t"
                << "LocalClass::arg2_ = " << arg2_ << "\n";
    }
  };

  /*
    ...and returned here
  //*/
  return new (nothrow) LocalClass(arg1, arg2);
}


/*
  ..main
//*/
int main()
{ 
  /*
    init, here we use "nothrow" declaration, because of simplicity. 
    The alternative would be writing an exception and using try/catch
  //*/
  Interface *pLocalObject = NULL;
  if(NULL == (pLocalObject = MakeAdapter< string, int >( "Hello World!", 1234567))){
    std::cerr << "ERROR: allocation failed!\n";
    exit(-1);
  }
  
  /*
    do something
  //*/
  pLocalObject->doSomething();

  /*
    free memory - won't call the dtor?!
  //*/
  delete pLocalObject;


  cout << "READY.\n";
  return 0;
}
