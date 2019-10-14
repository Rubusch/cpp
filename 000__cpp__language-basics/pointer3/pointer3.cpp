// Main.cpp
/*

  Pointer & References

  Both pointers share the same content and address:
        pB = pA;

  Both pointers just share the same content but use different address:
        *pB = *pA;

//*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
  int var = 7;
  cout << " - Usage of Pointers - " << endl;
  cout << endl;
  {
    cout << "Both pointers share the same addresses\n"
         << "if one changes the content of the other changes, too:" << endl;

    cout << "pB = pA;" << endl;
    cout << endl;

    int *pA = NULL;
    int *pB = NULL;

    pA = &var;

    cout << "*pA = " << *pA;
    cout << ", pA = " << pA;
    cout << endl;

    pB = pA;

    cout << "*pA = " << *pA << ", *pB = " << *pB << endl;
    cout << "pA = " << pA << ", pB = " << pB << " (same address)" << endl
         << endl;

    cout << "++*pA;" << endl;
    ++*pA;
    cout << "*pA = " << *pA << ", *pB = " << *pB << endl << endl;

    cout << "--*pB;" << endl;
    --*pB;
    cout << "*pA = " << *pA << ", *pB = " << *pB << endl << endl;
  };
  {
    cout << "Both pointers have different addresses\n"
         << "if one changes the content of the other doesn't change:" << endl;

    cout << "*pB = *pA;" << endl;
    cout << endl;

    int *pA;
    int *pB;
    pA = &var;

    /* pB needs to get memory allocated first (or segfault) !!! */
    pB = new int;

    *pB = *pA;

    cout << "*pA = " << *pA << ", *pB = " << *pB << endl;
    cout << "pA = " << pA << ", pB = " << pB << " (different address)" << endl
         << endl;

    cout << "++*pA;" << endl;
    ++*pA;
    cout << "*pA = " << *pA << ", *pB = " << *pB << endl << endl;

    cout << "--*pB;" << endl;
    --*pB;
    cout << "*pA = " << *pA << ", *pB = " << *pB << endl << endl;

    /* pB needs to free its memory */
    delete pB;
    cout << endl;
  };

  return 0;
};
