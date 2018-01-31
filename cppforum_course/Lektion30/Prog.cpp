// Prog.cpp
/*
   Stack as fixed vector mit Konstruktor (Lektion30), die Groesse
   des Stack ist allerdings vorgegeben.
//*/

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
