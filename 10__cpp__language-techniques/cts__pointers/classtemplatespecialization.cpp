// pts_pointers.cpp
/*
  An example that shows the use of partial template specialization using pointer types
  to avoid mainly duplicate code.

  (idea: http://www.learncpp.com/cpp-tutorial/146-partial-template-specialization/)
//*/


#include <iostream>


using namespace std;

/*
  IMPORTANT: forward declaration!

  necessary template declaration to specify the type in a further implementation
//*/
template< class T >
class Storage;


/*
  the partial specialized template implementation
//*/
template<typename T>
class Storage<T*> // specialization the implementation for pointer types
{
private:
  T* value;

public:
  // ctor
  Storage(T &initValue)
  {
    // allocate a new pointer and set it to initValue
    value = &initValue;
  }

  // some functions
  void output()
  {
    std::cout << "content:\t#" << *value << "#" << std::endl;
  }
};


/*
  main..
//*/
int main()
{
  // declare a pointer instance to show it works
  int x = 7;
  Storage<int*> pIntStorage(x);

  cout << "pointer instance - ";
  pIntStorage.output();


  // if the pointer assignment worked out then changing x will change the
  // objects content, too
  x = 9;

  cout << "Reset \'x\' \t- ";
  pIntStorage.output();


  cout << "READY.\n";
  return 0;
}
