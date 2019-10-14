// bitset.cpp
/*
  bitset

  resources: Kuhlins and Schader (2003)
//*/


#include <bitset>
#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  bitset< 5 > bs_a(6), bs_b(string("10010")), bs_x;
  cout << endl;

  cout << "a = \t\t" << bs_a << "\nb = \t\t" << bs_b << "\nx = \t\t" << bs_x
       << endl;

  cout << "bitlogic\n";
  cout << "a & b = \t" << (bs_a & bs_b) << endl;
  cout << "a | b = \t" << (bs_a | bs_b) << endl;
  cout << "a ^ b = \t" << (bs_a ^ bs_b) << endl;
  cout << endl;

  cout << "set x to 1\n";
  bs_x[3] = 1;
  cout << endl;

  cout << "b.set(2).flip()\n";
  bs_x.set(2).flip();
  cout << endl;

  cout << "x = \t\t" << bs_x << " = " << bs_x.to_ulong() << ", " << bs_x.count()
       << " bit(s) set\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
