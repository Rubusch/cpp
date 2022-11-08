// Main.cpp
/*
  Pointer & References

  Initialization of pointers with numbers works only, if the the
  pointer already points to some space.

  1. Declare the pointer
  2. Point to a variable or space
  3. Initialize the pointer (and the corresponding variable!)
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
  int var = 7;
  int *pVar = NULL;

  pVar = &var;
  *pVar = 6;

  cout << "var = " << var << ", *pVar = " << *pVar << endl;

  int *pErr = NULL;
  cout
      << "\"*pErr = var\" or \"*pErr = 5\" results in \"Segmentation fault\"..."
      << endl;

  //    *pErr = 5;    /* Segmentation Fault - Where to store the '5', still
  //    nothing allocated? */

  *pErr = var; /* Segmentation Fault - Copy the Value of var to where again? */

  return 0;
};
