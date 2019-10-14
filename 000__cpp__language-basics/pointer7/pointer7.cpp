// Main.cpp

#include <iostream>

using namespace std;

int main()
{
  // a is 5
  int a = 5;
  cout << a << endl;

  // pointer pa points to address of a
  int *pa = &a;

  *pa = 6; // assign *pa, pa has memory - the variable 'a' - to be assigned
  cout << "a: " << a << " [6]" << endl; // a prints '6'

  a = 7;                                    // assign a
  cout << "*pa: " << *pa << " [7]" << endl; // *pa prints '7'

  // pointer pb is now pa, pb points also to a
  int *pb = pa;
  cout << *pb << endl;

  // pointer to pointer ppa points to address of pa
  int **ppa = &pa;
  cout << **ppa << endl;

  // assign the address of pb to the content of ppa
  ppa = &pb;
  cout << "**ppa: " << **ppa << " [7]" << endl;

  // pb points now to the address of b
  int b = 8;
  pb = &b;
  cout << "**ppa: " << **ppa << " [8]"
       << endl; // pointer of pointer ppa prints 8 [b]

  int c = 9;
  int &rc = c; // int reference to c which is 9

  cout << "c: " << c << ", rc: " << rc << endl;
  rc = 2;
  cout << "c: " << a << endl;

  return 0;
};
