// Main.cpp
/*
  Pointer & References

  A reference is another name for a variable and contains even the same address.
  It can only be initialized at Deklaration time.

  A reference cannot be NULL!
//*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
  int var = 7;
  int &rVar = var;

  cout << "var: " << var << ", rVar: " << rVar << endl;
  cout << "&var: " << &var << ", &rVar: " << &rVar << endl;

  cout << "rVar = 666;" << endl;
  rVar = 666;

  cout << "var: " << var << endl;

  return 0;
};
