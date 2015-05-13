// main.cpp
/*
//*/

#include <iostream>
using namespace std;

template<class T>
void swap(T *pa, T *pb)
{
    T tmp = *pa;
    *pa = *pb;
    *pb = tmp;
};
