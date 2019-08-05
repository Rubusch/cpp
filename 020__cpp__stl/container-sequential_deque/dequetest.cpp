// dequetest.cpp
/*
  demonstrates deque

  the STL has 3 sequential containers:
  - vector
  - deque
  - list
//*/

#include <iostream>
#include <deque>

/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "init...\n";
  deque< int > deq;

  cout << "usage\n";
  for(int idx=0; idx<=18; ++idx){
    if(idx % 3){
      deq.push_back(idx);
    }else if(!deq.empty()){
      cout << deq.front() << " served, still pending: ";
      deq.pop_front();
      for(unsigned int jdx=0; jdx < deq.size(); ++jdx){
        cout << deq[jdx] << " ";
      }
      cout << endl;
    }
  }

  cout << "READY.\n";
  return 0;
}

