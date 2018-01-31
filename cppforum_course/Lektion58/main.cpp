// main.cpp
/*
//*/

#include <iostream>
using namespace std;

const int STACK_SIZE=5;

template<class T>
class StackAsVector
{
private:
    T *data;
    int topIndex;
public:
    StackAsVector(int size) // Konstruktor
    {
        data = new T[size];
        topIndex = -1;
    };

    void push(T i)
    {
        assert(topIndex < STACK_SIZE - 1);
        topIndex = topIndex + 1;
        data[topIndex] = i;
    };

    T top()
    {
        return data[topIndex];
    };

    void pop()
    {
        assert(topIndex > -1);
        topIndex = topIndex - 1;
    };

    bool empty()
    {
        return topIndex == -1;
    };
};

