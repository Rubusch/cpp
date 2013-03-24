// Main.cpp
/*
  Pointer & References

  Initialisation of pointers with numbers works only, 
  if the the pointer already points to some space.

  1. Declare the pointer
  2. Point to a variable or Space
  3. Initialize the pointer (and the corresponding variable!)
//*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int var = 7;
    int *pVar;

    pVar = &var;
    *pVar = 6;
    
    cout << "var = " << var << ", *pVar = " << *pVar << endl;
    
    int *pErr; 
//    *pErr = 5; // Segmentation Fault - Where to store the '5'?
//    *pErr = var; // Segmentation Fault - Copy the Value of var to where again?

    return 0;
};
