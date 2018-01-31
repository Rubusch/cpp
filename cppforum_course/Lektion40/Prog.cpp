// Prog.cpp
/*
  Arrays: Arrayzeiger und operator[]
//*/

#include <iostream>
using namespace std;

void printArray(int *pi, int size)
{
    for(int i=0;i<size; ++i)
        cout << pi[i] << endl;
};


int main()
{
    int array[5] = {1,2,3,4,5};
    printArray(array,5);

    return 0;
};


