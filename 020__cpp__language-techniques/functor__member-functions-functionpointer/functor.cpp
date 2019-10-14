// functionpointer.cpp
/*
  Geronimo the parrot

  Demo on function pointers to member functions.
//*/


#include <iostream>


/*
  Parrot
//*/
class Parrot
{
public:
  void eat() { std::cout << "\tTsk, knick, tsk...\n"; }

  void speak() { std::cout << "\tOh Captain, my Captain!\n"; }
};


/*
  main()
//*/
int main()
{
  using namespace std;
  cout << "Demo: pointer to memberfunctions - function pointer solution\n";
  cout << endl;


  // define a type: pointer to a member function of Parrot,
  // taking no arguments and returning void
  cout << "typedef void (Parrot::* TpMemFun)();\n";
  typedef void (Parrot::*TpMemFun)();
  cout << endl;


  // create an object of that type and initialize it with
  // the address of Parrot::eat
  cout << "TpMemFun pActivity = &Parrot::eat;\n";
  TpMemFun pActivity = &Parrot::eat;
  cout << endl;


  // create a parrot...
  cout << "Parrot geronimo;\n";
  Parrot geronimo;
  cout << endl;


  // ..and a pointer to it
  cout << "Parrot* pGeronimo = &geronimo;\n";
  Parrot *pGeronimo = &geronimo;
  cout << endl;


  // invoke the member function stored in Activity via an object.
  // Notice the use of operator .*
  cout << "(geronimo.*pActivity)();\n";
  (geronimo.*pActivity)();
  cout << endl;


  // same, via pointer. Now we use operator->*
  cout << "(pGeronimo->*pActivity)();\n";
  (pGeronimo->*pActivity)();
  cout << endl;


  // change the activity
  cout << "pActivity = &Parrot::speak;\n";
  pActivity = &Parrot::speak;
  cout << endl;


  // wake up, Geronimo!
  cout << "(geronimo.*pActivity)();\n";
  (geronimo.*pActivity)();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
