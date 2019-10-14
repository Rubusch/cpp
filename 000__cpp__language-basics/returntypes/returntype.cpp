// returntype.cpp
/*
  demonstrates getters and related problems (local scope)
//*/


#include <iostream>


class Foobar
{
private:
  int attribute;

public:
  Foobar() : attribute(0) {}

  /*
    locals
  //*/

  int getValue()
  {
    int local = 4;
    std::cout << "\tFoobar::getValue() - \t\t\tvalue = \t" << local
              << ", addr = \t\"" << &local << "\"\n";
    return local;
  }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"

  int &getValueReference()
  {
    int local = 5;
    std::cout << "\tFoobar::getValueReference() - \t\tvalue = \t" << local
              << ", addr = \t\"" << &local << "\"\n";
    std::cout << "\tWARNING: reference to local variable returned!!\n";
    // WARNING: reference to local variable returned!! NEVER DO THIS!!
    return local;
  }

  int *getValuePointer()
  {
    int local = 6;
    std::cout << "\tFoobar::getValuePointer() - \t\tvalue = \t" << local
              << ", addr = \t\"" << &local << "\"\n";
    std::cout << "\tWARNING: reference to local variable returned!!\n";
    // WARNING: reference to local variable returned!! DON'T DO THIS!
    return &local;
  }
#pragma GCC diagnostic pop
  /*
    attributes
  //*/

  int getAttribute()
  {
    attribute = 7;
    std::cout << "\tFoobar::getAttribute() - \t\tattribute = \t" << attribute
              << ", addr = \t\"" << &attribute << "\"\n";
    return attribute;
  }

  int &getAttributeReference()
  {
    attribute = 8;
    std::cout << "\tFoobar::getAttributeReference() - \tattribute = \t"
              << attribute << ", addr = \t\"" << &attribute << "\"\n";
    return attribute;
  }

  int *getAttributePointer()
  {
    attribute = 9;
    std::cout << "\tFoobar::getAttributePointer() - \tattribute = \t"
              << attribute << ", addr = \t\"" << &attribute << "\"\n";
    return &attribute;
  }

  /*
    inner function
  //*/

  void func()
  {
    std::cout << "\tFoobar::func()\n";
    int value = 0;

    std::cout << "\tint getValue()\n";
    value = getValue();
    std::cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value
              << "\"\n";
    std::cout << std::endl;

    /* getValueReference() segfaults here!
        std::cout << "\tint& getValueReference()\n";
        value = getValueReference();
        std::cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" <<
    &value << "\"\n"; std::cout << std::endl;
    // */

    /* getValuePointer() segfaults here!
        int *pointer = NULL;
        std::cout << "\tint* getValuePointer()\n";
        pointer = getValuePointer();
        std::cout << "\t\t\t\t\t\tpointer = \t" << *pointer << ", addr = \t\""
    << pointer << "\"\n"; std::cout << std::endl;
    // */
  }

  /*
    get new instance
  //*/
  int &getNewReference()
  {
    std::cout << "\tFoobar::getNewReference()\n";
    int *local = new int;
    *local = 777;
    return *local;
  }

  int *getNewPointer()
  {
    std::cout << "\tFoobar::getNewPointer()\n";
    return new int;
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  int value = 123;
  int *pointer = NULL;
  Foobar fb;
  cout << "value = \t" << value << ", addr = \t\"" << &value << "\"\n";
  cout << endl;

  /*** Values ***/

  cout << "int getValue()\n";
  value = fb.getValue();
  cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value
       << "\"\n";
  cout << endl;

  /* getValueReference() segfaults here!
    cout << "int& getValueReference()\n";
    value = fb.getValueReference();
    cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value <<
  "\"\n"; cout << endl;
  // */
  /* getValuePointer segfaults here!
    cout << "int* getValuePointer()\n";
    pointer = fb.getValuePointer();
    cout << "\t\t\t\t\t\tpointer = \t" << *pointer << ", addr = \t\"" << pointer
  << "\"\n"; cout << endl;
  // */

  /*** Attributes ***/

  cout << "int getAttribute()\n";
  value = fb.getAttribute();
  cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value
       << "\"\n";
  cout << endl;

  cout << "int& getAttributeReference()\n";
  value = fb.getAttributeReference();
  cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value
       << "\"\n";
  cout << endl;

  cout << "int* getAttributePointer()\n";
  pointer = fb.getAttributePointer();
  cout << "\t\t\t\t\t\tpointer = \t" << *pointer << ", addr = \t\"" << pointer
       << "\"\n";
  cout << endl;

  /*** member functions ***/

  cout << "member function\n";
  fb.func();
  cout << endl;

  /*** miscellaneous ***/

  cout << "miscellaneous\n";

  cout << "int& getNewReference()\n";
  value = fb.getNewReference();
  cout << "\t\t\t\t\t\tvalue = \t" << value << ", addr = \t\"" << &value
       << "\"\n";
  cout << endl;

  cout << "int* getNewPointer()\n";
  pointer = fb.getNewPointer();
  cout << "\t\t\t\t\t\tpointer = \t" << *pointer << ", addr = \t\"" << pointer
       << "\"\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
