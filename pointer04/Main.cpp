// Main.cpp
/*
  Pointer & References

  The pointer pointer shares the content and address with the pointer:
      pVar = &var;

  The pointer pointer contains the same content but uses different address:
      *pVar = var;  
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
        cout << "The pointer pointer shares the same address with another pointer\n" 
             << "if the pointer pointer changes, the content of the pointer changes, too:" 
             << endl;

        cout << "ppVar = &pVar;" << endl;
        cout << endl;
        
        int* pVar = &var;
        int** ppVar; 

        ppVar = &pVar;
        //*ppVar = pVar; // equal?!
        
        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl;
        cout << "pVar = " << pVar << ", *ppVar = " << *ppVar << " (equal address)" 
             << endl << endl;
        
        cout << "++*pVar;" << endl;
        ++*pVar;
        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl << endl;

        cout << "--**ppVar;" << endl;
        --**ppVar;        
        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl << endl;

        cout << endl;
    };
    {
        cout << "The pointer pointer has only the same value as the other ponter\n"
             << "if one changes the content of the pointer pointer doesn't change:"
             << endl;

        cout << "**ppVar = *pVar;" << endl;
        cout << endl;
        
        int* pVar = &var;
        int** ppVar;

        **ppVar = *pVar;

        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl;
        cout << "pVar = " << pVar << ", *ppVar = " << *ppVar << " (different address)" 
             << endl << endl;
        
        cout << "++*pVar;" << endl;
        ++*pVar;
        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl << endl;

        cout << "--**ppVar;" << endl;
        --**ppVar;
        cout << "*pVar = " << *pVar << ", **ppVar = " << **ppVar << endl << endl;

        cout << endl;
    };
    
    
    return 0;
};
