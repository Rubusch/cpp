// heapalgorithm.cpp
/*
  min/max algorithm

  max - returns the larger of two elements

  (Kuhlins & Schader, 2003)
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
  int val_a = 7;
  int val_b = 3;
  cout << "val_a = " << val_a << ", val_b = " << val_b << endl << endl;

  cout << "max()\n";
  int m = max(val_a, val_b);
  cout << "max = " << m << endl;
  cout << endl;

  cout << "max() using less< int >()\n";
  m = max(val_a, val_b, less< int >());
  cout << "max = " << m << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
