// istreamiterator.cpp
/*
  demonstrates an istream iterator on a vector< int >

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "Enter numbers, separated by a whitespace, followed by an 'x' and hit ENTER:\n";
  istream_iterator< int > start_it(cin);
  istream_iterator< int> end_it;
  cout << endl;

  cout << "set up a vector< int >\n";
  vector< int > vec(start_it, end_it);
  cout << endl;

  cout << "vec = ";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
