// priorityqueueusage.cpp
/*
  demonstrates the adapter priority_queue 
              
            /---> pop
           |
         +---+
         |   |- - -> top
         +---+
         |   |
         +---+
         |   |

  push ->|   |

         |   |
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


#include <queue>
#include <deque>
#include <functional>
#include <iostream>

/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  priority_queue< int, deque< int >, greater< int > > pque;
  cout << endl;

  cout << "push " << 1 << endl;
  pque.push(1);
  cout << endl;

  cout << "push " << 7 << endl;
  pque.push(7);
  cout << endl;

  cout << "push " << 3 << endl;
  pque.push(3);
  cout << endl;

  cout << "push " << 5 << endl;
  pque.push(5);
  cout << endl;

  cout << "pop out the elements (priority \"greater\")..\n";
  while(!pque.empty()){
    cout << pque.top() << " ";
    pque.pop();
  }
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
