// Main.cpp
/*
  Pointer & References

  The pointer shares the content and address with the variable:
      pVar = &var;

  The pointer contains the same content but uses different address:
      *pVar = var;
  This needs pVar to have allocated memory first!
//*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << " - Usage of Pointers - " << endl;
    cout << endl;
    {
        cout << "The pointer shares the same address with a variable\n"
             << "if the variable changes the content of the pointer changes, too:"
             << endl;

        cout << "pVar = &var;" << endl;
        cout << endl;

        int var = 7;
        int* pVar = NULL; // same as: int* pVar = &var
        pVar = &var;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << "&var = " << &var << ", pVar = " << pVar << " (equal address)" << endl;

        cout << "++var;" << endl;
        ++var;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << "--*pVar;" << endl;
        --*pVar;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << endl;
    };
    {
        cout << "The pointer shares the value with a variable\n"
             << "if the variable changes the content of the pointer doesn't change:"
             << endl;

        cout << "*pVar = var;" << endl;
        cout << endl;

        int var = 7;
        int* pVar = NULL;

        /* NEEDS ALLOCATION OR SEGFAULT */
        pVar = new int;

        *pVar = var;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << "&var = " << &var << ", pVar = " << pVar << " (different address)" << endl;

        cout << "++var;" << endl;
        ++var;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << "--*pVar;" << endl;
        --*pVar;

        cout << "var = " << var << ", *pVar = " << *pVar << endl;
        cout << endl;

        /* FREE ALLOCATION */
        delete pVar;
    };

    return 0;
};
