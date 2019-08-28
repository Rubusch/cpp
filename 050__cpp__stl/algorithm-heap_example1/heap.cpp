// heap.cpp
/*
  heapalgorithms

  make_heap - creates a heap out of a range of elements
  pop_heap - remove the largest element from a heap
  push_heap - add an element to a heap
  sort_heap - turns a heap into a sorted range of elements
  (by doing this the heap looses its heap behavior)

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 5, 3, 8, 0, 1, 2, 6, 7 };
  signed int number = sizeof(arr) / sizeof(*arr);
  copy(arr, arr+8, ostream_iterator< int >(cout, " "));
  cout << " : " << number << " elements\n";
  cout << endl;

  cout << "make_heap()\n";
  make_heap(arr, arr+number);
  copy(arr, arr+number, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "pop_heap()\n";
  pop_heap(arr, arr+number);
  --number;
  copy(arr, arr+number, ostream_iterator< int >(cout, " "));
  cout << "and " << arr[number] << "\n";
  cout << endl;

  cout << "push_heap() - 7\n";
  ++number;
  arr[number-1] = 4;
  push_heap(arr, arr+number);
  copy(arr, arr+number, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "sort_heap()\n";
  sort_heap(arr, arr+number);
  copy(arr, arr+number, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
