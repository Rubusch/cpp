// Main.cpp
/*
  Use of a simple template function.
//*/

#include <iostream>

using namespace std;


template < class T >
void swap(T *a, T *b)
{
  T tmp = *a;
  *a = *b;
  *b = tmp;
};


int main()
{
  int a = 5, b = 10;
  cout << "a = " << a << ", b = " << b << endl;

  swap< int >(&a, &b);
  cout << "swap" << endl;

  cout << "a = " << a << ", b = " << b << endl;

  return 0;
};
