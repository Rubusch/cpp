// boolvector.cpp
/*
  vector bool - dynamic, "unlimited" bitset

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  vector< bool > vb(5); // 5 x false
  copy(vb.begin(), vb.end(), ostream_iterator< bool >(cout));
  cout << endl << endl;

  cout << "negate element 0\n";
  vb.front().flip();
  copy(vb.begin(), vb.end(), ostream_iterator< bool >(cout));
  cout << endl << endl;

  cout << "swap element 0 and element \'back\'\n";
  vector< bool >::swap(vb.at(0), vb.back());
  copy(vb.begin(), vb.end(), ostream_iterator< bool >(cout));
  cout << endl << endl;

  cout << "add 2 elements: true and false\n";
  vb.push_back(true);
  vb.push_back(false);
  copy(vb.begin(), vb.end(), ostream_iterator< bool >(cout));
  cout << endl << endl;

  cout << "negate all elements\n";
  vb.flip();
  copy(vb.begin(), vb.end(), ostream_iterator< bool >(cout));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
