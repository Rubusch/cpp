// Main.cpp

#include <iostream>

using namespace std;

int main()
{
  // a is 5
  int a = 5;
  cout << "a = " << a << ";\t\t// [5]" << endl;
  cout << endl;

  // pointer pa points to address of a
  cout << "int *pa = &a;" << endl;
  int *pa = &a;
  cout << endl;

  cout << "*pa = 6;" << endl;
  *pa = 6; // assign *pa, pa has memory - the variable 'a' - to be assigned
  cout << "\t// " << "a: " << a << " [6]" << endl;
  cout << endl;

  a = 7;
  cout << "a = " << a << ";\t\t// [7]" << endl;
  cout << "\t// " << "*pa: " << *pa << " [7]" << endl;
  cout << endl;

  // pointer pb is now pa, pb points also to a
  cout << "int *pb = pa;" << endl;
  int *pb = pa;
  cout << "\t// " << "*pb: " << *pb << " [7]" << endl;
  cout << endl;

  // pointer to pointer ppa points to address of pa
  cout << "int **ppa = &pa;" << endl;
  int **ppa = &pa;
  cout << "\t// " << "**ppa: " << **ppa << " [7]" << endl;
  cout << endl;

  // assign the address of pb to the content of ppa
  cout << "ppa = &pb;" << endl;
  ppa = &pb;
  cout << "\t// " << "**ppa: " << **ppa << " [7]" << endl;
  cout << endl;

  // pb points now to the address of b
  int b = 8;
  cout << "int b = " << b << ";\t// [8]" << endl;
  cout << "pb = &b;" << endl;
  pb = &b;
  cout << "\t// " << "**ppa: " << **ppa << " [8]"
       << endl; // pointer of pointer ppa prints 8 [b]
  cout << endl;

  cout << "int c = 9;" << endl;
  int c = 9;
  cout << endl;

  cout << "int &rc = c;" << endl;
  int &rc = c; // int reference to c which is 9
  cout << endl;

  cout << "\t// " << "c: " << c << " [9]" << endl;
  cout << "\t// " << "rc: " << rc << " [9]" << endl;
  cout << endl;

  cout << "rc = 2;" << endl;
  rc = 2;
  cout << "\t// " << "c: " << c << " [2]" << endl;
  cout << endl;

  return 0;
};
