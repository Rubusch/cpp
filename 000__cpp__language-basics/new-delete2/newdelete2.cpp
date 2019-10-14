// Main.cpp
/*
  new and delete

  allocate space using "new"
//*/

#include <iostream>
#include <string>
using namespace std;

class Someclass
{
public:
  Someclass() { cout << "Ctor()" << endl; };
  ~Someclass() { cout << "~Dtor()" << endl; };

  void output() { cout << "some class output" << endl; };
};


int main()
{
  // variable
  int a = 10;
  cout << "Variable: " << a << endl;

  // pointer to a dynamic pointee
  int *b = new int(20);
  cout << "Pointer to a dynamic pointee: " << *b << endl;

  // array
  int c[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  cout << "Array: from " << c[0] << " thru " << c[9] << endl;

  // dynamic array
  int *d = new int[10];
  for (int i = 0; i < 10; ++i)
    d[i] = i;
  cout << "Dynamic array: from " << d[0] << " thru " << d[9] << endl;

  // Objectpointer
  cout << "Objectpointer: ";
  Someclass *e = new Someclass();

  cout << endl;
  cout << "Now everything will be deleted!" << endl;
  cout << endl;

  cout << "no delete the variable" << endl;
  cout << "delete the pointee" << endl;
  delete b;
  cout << "no delete[] the array" << endl;
  cout << "delete[] the dynamic array" << endl;
  delete[] d;
  cout << "delete the dynamic object pointer: ";
  delete e;


  return 0;
};
