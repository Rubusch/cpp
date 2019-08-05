// randomshuffle.cpp
/*
  modifying algorithm

  random_shuffle - randomly re-order elements in some range

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>


/*
  functor as random seed
//*/
template< class T >
class ChuckALuck
{
private:
  unsigned long seed_;

public:
  ChuckALuck(T start = 0) : seed_(start) {}
  T operator()(T times){ return (seed_ = (123123234 * seed_ + 7)) % times; }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
  cout << endl;

  cout << "random_shuffle()\n";
  random_shuffle(arr, arr+7);
  cout << endl;

  cout << "shuffeled normally:\n";
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "use Chuck-A-Luck\n";
  ChuckALuck< int > cal(1);
  random_shuffle(arr, arr+7, cal);
  cout << "and shuffle again:\n";
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
