// swap.cpp
/*
  modifying algorithm
  
  swap - swap the values of two objects

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int val_a = 1
    , val_b = 7;
  cout << endl;

  cout << "before:\t val_a = " << val_a << " and val_b = " << val_b << endl;
  swap(val_a, val_b);
  cout << "after:\t val_a = " << val_a << " and val_b = " << val_b << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
