// typeof.cpp
/*
  Typeof operator usage example:
  Very efficient type independent swap macro.

  typeof() is missing in some C++ standards!
//*/


#include <iostream>

using namespace std;

// typeof
#define SWAP(a,b) { __typeof__(a) temp; temp=a; a=b; b=temp; }

const int ARRSIZE = 10;


void printarray(const char arr[ARRSIZE])
{
  for(int idx=0; idx<ARRSIZE; ++idx){
    cout << arr[idx];
    cout << " ";
  }
  cout << endl;
}


/*
  main
//*/
int main()
{
  char arr[ARRSIZE] = {'A', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

  printarray(arr);


  cout << "mix.." << endl;
  for(int idx=1; idx<ARRSIZE; ++idx){
    SWAP(arr[idx-1], arr[idx]);
  }


  printarray(arr);


  cout << "READY.\n";
  return 0;
}
