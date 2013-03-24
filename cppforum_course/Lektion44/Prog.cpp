// Prog.cpp
/*
  Konstruktor mit Argumenten und Destruktor.
  Nur Klasse - kein Programm.
  Die Klasse zeigt die richtige Verwendung von assert() in diesem
  Zusammenhang.
//*/

#include <iostream>
#include <assert.h>
using namespace std;

class StackAsVector
{
private:
   int *data;
   int topIndex;
   int stack_size;// ---> zum Sichern der Größe,
      // die im Konstruktor angegeben wurde
public:
   StackAsVector(int size)// Konstruktor
   {
      data=new int[size];
      topIndex=-1;
      stack_size=size;// ---> Sichern dieses Wertes
   };
   void push(int i)// ein Element oben drauflegen
   {
      assert(topIndex<stack_size-1); // --> hier wird
         // dieser Wert dann benötigt
      topIndex=topIndex+1;
      data[topIndex]=i;
   };
};

