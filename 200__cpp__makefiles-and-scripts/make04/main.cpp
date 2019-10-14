// main.cpp
/*
//*/

#include <iostream>
using namespace std;
#include "alpha.h"
#include "beta.h"

// main method
int main()
{
  cout << "main()" << endl;

  // generate instance of A
  A a;
  a.generateB();

  // generate instance of B
  B b;
  b.doSomething();

  return 0;
};
