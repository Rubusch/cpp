// stackusage.cpp
/*
  demonstrates the adapter stack (lifo)


  push --\   /--> pop
          | |
         +---+
  top -- |   |
         +---+
         |   |
         +---+
         |   |
         +---+


  the STL has 3 adapters
  - stack
  - queue
  - priority_queue

  for sequential containers (vector, deque, list)
//*/

#include <stack>
#include <list>
#include <iostream>

int main()
{
  using namespace std;

  cout << "init...\n";
  stack< int, list< int > > lifo;
  cout << endl;

  cout << "push 5 on the stack\n";
  lifo.push(5);
  cout << endl;

  cout << "show and pop the first element:\n";
  if(lifo.top() == 5){
    cout << lifo.top() << endl;
    lifo.pop();
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
