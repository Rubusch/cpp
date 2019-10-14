// queueusage.cpp
/*
  demonstrates the adapter queue (fifo)

           +-+-+-+-+-+
  push --> | | | | | | --> pop
           +-+-+-+-+-+
            |       |
          back     front

  the STL has 3 adapters
  - stack
  - queue
  - priority_queue

  for sequential containers (vector, deque, list)
//*/


#include <iostream>
#include <list>
#include <queue>


int main()
{
  using namespace std;

  cout << "init..\n";
  queue< int, list< int > > fifo;
  cout << endl;

  cout << "populate the queue\n";
  cout << 3 << endl;
  fifo.push(3);
  cout << 5 << endl;
  fifo.push(5);
  cout << 7 << endl;
  fifo.push(7);
  if (fifo.back() != 7) {
    cerr << "something\'s wrong!\n";
  }
  cout << endl;

  cout << "show and remove the elements one by one..\n";
  while (!fifo.empty()) {
    cout << fifo.front() << " ";
    fifo.pop();
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
