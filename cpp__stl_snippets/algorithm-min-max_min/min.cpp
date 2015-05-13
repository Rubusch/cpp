// min.cpp
/*
  min/max algorithm

  min - returns the smaller of two elements

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

  cout << "min()\n";
  int m = min(val_a, val_b);
  cout << "min = " << m << endl;
  cout << endl;

  cout << "min() using less< int >()\n";
  m = min(val_a, val_b, less< int >());
  cout << "min = " << m << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
