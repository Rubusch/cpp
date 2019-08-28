// locale.cpp
/*
  locale settings
//*/


#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;

  locale loc("");
  cout << "locale:\n" << loc.name() << endl;
  cout << endl;

  cout.imbue(locale(""));
  cout << "a number with decimal separators (imbue):\n" << 1234567 << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
