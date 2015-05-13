// Prog.cpp
/*
  Verwendung von assert um die Verwendung des Arrays abzusichern.
  assert verlangsamt das Programm und sollte bei der Endanwendung abgeschaltet werden.
//*/

#include <assert.h>
#include <iostream>
using namespace std;

const int STACK_SIZE=5;
class StackAsFixedVector
{
private:
    int data[STACK_SIZE];
    int topIndex;
public:
    // Konstruktor
    StackAsFixedVector()
    {
        topIndex = -1;
    };
    

    // ein Element oben drauflegen
    void push(int i)
    {
        assert(topIndex < STACK_SIZE - 1);
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
    StackAsFixedVector stack;
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
