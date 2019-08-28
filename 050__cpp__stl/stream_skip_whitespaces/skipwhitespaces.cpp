// skipwhitespaces.cpp
/*
  stream operations

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;

  // init
  char ch1, ch2, ch3, ch4;

  cout << "Enter \'1 2 3 4<ENTER>\', separated by whitespaces and have a look on the output.\n";
  cin >> ch1 >> ch2;
  cin.unsetf(ios_base::skipws);
  cin >> ch3 >> ch4;

  // output
  cout << "read values: (" << ch1 << ") (" << ch2 << ") (" << ch3 << ") (" << ch4 << ")\n";
  cout << "after the first two values the skipws has been unset\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
