// example.cpp
/*
  set algorithm - multiset operations

  undefined behavior for unsorted input data!

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;
  
  cout << "init\n";
  int arr_a[] = { 2, 4, 4, 4, 6, 6, 8 };
  int arr_b[] = { 3, 4, 4, 6, 9, 9 };
  const multiset< int > multi_a(arr_a, arr_a+7);
  const multiset< int > multi_b(arr_b, arr_b+6);
  ostream_iterator< int > os_iter(cout, " ");
  cout << "multi_a: \t";
  copy(multi_a.begin(), multi_a.end(), os_iter);
  cout << "\nmulti_b: \t";
  copy(multi_b.begin(), multi_b.end(), os_iter);
  cout << endl << endl;

  cout << "set_union()\n";
  set_union(multi_a.begin(), multi_a.end(), multi_b.begin(), multi_b.end(), os_iter);
  cout << endl << endl;

  cout << "set_intersection()\n";
  set_intersection(multi_a.begin(), multi_a.end(), multi_b.begin(), multi_b.end(), os_iter);
  cout << endl << endl;

  cout << "set_difference()\n";
  set_difference(multi_a.begin(), multi_a.end(), multi_b.begin(), multi_b.end(), os_iter);
  cout << endl << endl;

  cout << "set_symmetric_difference()\n";
  set_symmetric_difference(multi_a.begin(), multi_a.end(), multi_b.begin(), multi_b.end(), os_iter);
  cout << endl << endl;

  cout << "includes()\n";
  cout << "multi_a includes multi_b: " 
       << boolalpha 
       << includes(multi_a.begin(), multi_a.end(), multi_b.begin(), multi_b.end()) 
       << endl;
  cout << endl;   

  cout << "READY.\n";
  return 0;
}
