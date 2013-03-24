// ostreamiterator.cpp
/*
  ostream iterator

  (Kuhlins & Schader, 2003)
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

  cout << "init\n";
  vector< int > vec;
  cout << endl;

  cout << "reserve space for 4 elements on the vector\n";
  vec.reserve(4);
  cout << endl;

  cout << "populate the vector with 4 elements\n";
  for(int idx = 1; idx <= 4; ++idx){
    vec.push_back(idx);
  }
  cout << endl;

  cout << "vec = ";
  copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
