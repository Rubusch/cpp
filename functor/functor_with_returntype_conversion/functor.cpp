// functor.cpp
/*
  (Alexandrescu, 2001)
//*/


#include <iostream>


#include "functor.hpp"


using namespace std;


/* 
   ignore arguments-not of interest in this example
//*/
const char* testFunction(double, double)
{
  static const char buffer[] = "Hello World!";

  // it's safe to retrun a pointer to a static buffer
  return buffer;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  // init
  cout << "init..\n";
  Functor< string, TYPELIST_2(int, int) > cmd(testFunction);
  cout << endl;
  
  // demonstrates the return type conversion: should print "World!";
  cout << "should print \'World!\'\n> \'" << cmd(10, 10).substr(6) << "\'\n";
  cout << endl;
  
  cout << "READY.\n";
  return 0;
}


