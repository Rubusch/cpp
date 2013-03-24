// Prog.cpp
/*
   Stack as vector mit Konstruktor (Lektion30), die Groesse 
   des Stack kann nun verschieden vorgegeben werden.
//*/

#include <iostream>
#include <assert.h>
using namespace std;

const int STACK_SIZE=5;
class StackAsVector
{
private:
    int *data;
    int topIndex;
public:
    // Konstruktor
    StackAsVector(int size)
    {
        data = new int[size];
        topIndex = -1;
    };
    

    // ein Element oben drauflegen
    void push(int i)
    {
        assert(topIndex < STACK_SIZE -1);
        topIndex = topIndex + 1;
        data[topIndex] = i;
    };
    

    // das oberste Element lesen
    int top()
    {
        return data[topIndex];
    };
    

    // das oberste Element entfernen
    void pop()
    {
        assert(topIndex > -1);
        topIndex = topIndex - 1;
    };
    

    // ist der Stack leer?
    bool empty()
    {
        return topIndex == -1;
    };
};


int main()
{
    StackAsVector stack = StackAsVector(5);
    int i;
    for(i=0;i<5;++i){
        int input;
        cin >> input;
        stack.push(input);
    }
    while(!stack.empty()){
        cout << stack.top() << endl;
        stack.pop();
    };
};
