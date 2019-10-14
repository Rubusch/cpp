// typeid.cpp
/*
  the example demonstrates the usage of typeid
//*/

#include <iostream>
#include <typeinfo> // typeid

class SomeClass
{
};
class AnyClass
{
};

int main()
{
  using namespace std;

  string str = "asdfasdf";
  long longVar1 = 11111111, longVar2 = 22222222;
  SomeClass sc;
  AnyClass ac;
  char *pChar = NULL;

  cout << "typeid() test\n";

  cout << endl;

  cout << "The type of \'str\' is:\t\t" << typeid(str).name()
       << "\t\t(string)\n";
  cout << "The type of \'longVar1\' is:\t" << typeid(longVar1).name()
       << "\t\t(long)\n";
  cout << "The type of \'longVar2\' is:\t" << typeid(longVar2).name()
       << "\t\t(long)\n";
  cout << "The type of \'sc\' is:\t\t" << typeid(sc).name()
       << "\t(class SomeClass)\n";
  cout << "The type of \'ac\' is:\t\t" << typeid(ac).name()
       << "\t(class AnyClass)\n";
  cout << "The type of \'*pChar\' is:\t" << typeid(*pChar).name()
       << "\t\t(dereferenced pointer to char)\n";
  cout << "The type of \'pChar\' is:\t\t" << typeid(pChar).name()
       << "\t\t(pointer to char)\n";

  cout << endl;

  if (typeid(str) == typeid(longVar1)) {
    cout << "\'str\' and \'longVar1\' have the same type" << endl;
  } else {
    cout << "\'str\' and \'longVar1\' don\'t have the same type!" << endl;
  }


  if (typeid(longVar1) == typeid(longVar2)) {
    cout << "\'longVar1\' and \'longVar2\' have the same type" << endl;
  } else {
    cout << "\'longVar1\' and \'longVar2\' don\'t have the same type!" << endl;
  }


  if (typeid(sc) == typeid(ac)) {
    cout << "\'sc\' and \'ac\' have the same type" << endl;
  } else {
    cout << "\'sc\' and \'ac\' don\'t have the same type!" << endl;
  }

  cout << endl;


  cout << "READY.\n";
  return 0;
}
