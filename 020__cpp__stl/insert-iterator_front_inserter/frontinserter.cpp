// frontinserter.cpp
/*
  insert iterator demonstrated with a front_inserter on a deque<int>

  output:
  6 2 3 5 1 6 2 3 5 1 0 0 0

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <deque>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 1, 5, 3, 2, 6 };
  deque< int > deq(3U, 0);
  cout << endl;

  cout << "front_insert_iterator< deque< int > >(deq)\n";
  copy( arr, arr + 5, front_insert_iterator< deque< int > >(deq));
  cout << endl;

  cout << "front_inserter(deq)\n";
  copy( arr, arr + 5, front_inserter(deq));
  cout << endl;

  cout << "output:\n";
  copy(deq.begin(), deq.end(), ostream_iterator<int>(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
