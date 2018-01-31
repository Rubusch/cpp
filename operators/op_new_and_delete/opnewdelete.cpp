// newdelete.cpp
/*
  overloading of "oerator new()" and "operator delete()"

  Adhere the convention when writing "operator new()" and "operator delete()". (8/Meyers)
//*/


#include <iostream>
#include <new> // sometimes this won't be accepted, try <new.h>


/*
  1. Foobar class with overloaded operators
//*/
class Foobar
{
private:
  std::string str;

public:
  static void* operator new(size_t size);
  /*
    in case of a new-handler ::operator new() can have one more parameter:
      void* operator new(size_t size, new-handler p)

    if the new handler is not used either it is possible to overload:
      void* operator new(size_t size, new-handler p);
      void* operator new(size_t size);

    or to provide a default parameter (remember 0 == NULL):
      void* operator new(size_t size, new-handler p = 0);

    (9/Meyers)
  //*/

  static void operator delete(void* rawMemory, size_t size);

  // ...
  inline void setString(std::string s){ str = s; }
  inline std::string getString(){ return str; }
};

void* Foobar::operator new(size_t size)
{
  // check size
  if(size != sizeof(Foobar))
    return ::operator new(size);

  // MISSING: in case use a new-handler here

  void* memory;
  try{
    memory = ::operator new(size);
  }catch(std::bad_alloc){
    std::cerr << "Uh-oh.. something went wrong with the \"operator new()\"" << std::endl; // some comment
    // MISSING: in case of a modified new-handler reset here to the global new-handler
    throw;
  }
  std::cerr << "\"operator new()\" succeeded!" << std::endl; // some comment

  return memory;
}

void Foobar::operator delete(void* rawMemory, size_t size)
{
  // check pointer
  if(rawMemory == 0) return;

  // check that the size is correct
  if(size != sizeof(Foobar)){
    std::cerr << "global \"operator delete()\" was used" << std::endl; // some comment
    ::operator delete(rawMemory);
    rawMemory = NULL;
    return;
  }

  // do the specific implementation here: free allocated memory
  Foobar *memory = static_cast<Foobar*>(rawMemory);
  ::operator delete(memory); // here just a normal delete :-)
  memory = NULL;

  std::cerr << "\"operator delete()\" succeeded!" << std::endl; // some comment

  return;
}


/*
  3. usage of the operators
//*/
int main()
{
  // init - use overloaded new
  Foobar *pFoobar = new Foobar;

  pFoobar->setString("I have an overloaded \"operator new()\"");
  std::cout << pFoobar->getString() << std::endl;

  // free memory - use overloaded delete
  delete pFoobar;
  pFoobar = NULL;

  std::cout << "READY.\n" << std::endl;
  return 0;
}
