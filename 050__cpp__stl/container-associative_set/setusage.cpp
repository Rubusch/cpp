// setusage.cpp
/*
  demonstrates set

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


#include <iostream>
#include <set>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  typedef set< int, greater< int > > int_set;
  int_set is;
  is.insert(2);
  is.insert(4);
  is.insert(1);
  is.insert(3);
  if (is.insert(5).second) {
    cout << "5 has been inserted\n";
  }
  cout << endl;

  cout << "set up pair\n";
  pair< int_set::const_iterator, bool > pa = is.insert(2);
  if (!pa.second) {
    cout << *pa.first << " is already in the set\n";
  }
  cout << endl;

  cout << "set contains:\n";
  for (int_set::const_iterator iter = is.begin(); iter != is.end(); ++iter) {
    cout << *iter << " ";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
