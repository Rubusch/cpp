// multisetusage.cpp
/*
  multiset

  +-----------------+----------------+------------------+
  |                 | one occurance  | more occurances  |
  |                 |                |                  |
  +-----------------++================+=================+
  | only keys       || set            | multiset        |
  +-----------------++----------------+-----------------+
  | keys and values || map            | multimap        |
  +-----------------++----------------+-----------------+

  resources: Kuhlins and Schader (2003)
//*/

#include <set>
#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  const int arr[] = { 1, 4, 3, 2, 2, 3, 5, 1, 7, 6, 5 };
  multiset< int, greater< int > > ms(arr, arr+8);
  cout << endl;

  cout << "init multiset iterator\n";
  multiset< int, greater< int > >::iterator ms_ins = ms.insert(2);
  cout << endl;

  cout << "set up multiset iterator\n";
  ms.insert(ms_ins, 3);
  cout << endl;

  cout << "sorting..\n";
  cout << "elements contained:\n";
  for( multiset< int, greater< int > >::const_iterator iter = ms.begin()
         ; iter != ms.end()
         ; ++iter){
    cout << *iter << " ";
  }
  cout << endl << endl;

  cout << "count()\n";
  cout << "3 is contained " << ms.count(3) << " times\n";
  cout << endl;

  cout << "erase()\n";
  const multiset< int, greater< int > >::size_type n = ms.erase(2);
  cout << "2 has been erased " << n << " times\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
