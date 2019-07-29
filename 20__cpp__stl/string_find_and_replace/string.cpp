// string.cpp
/*
  string - find and replace

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <string>


/*
//*/
std::string upper(std::string str)
{
  for(std::string::size_type idx = 0; idx < str.length(); ++idx){
    str[idx] = static_cast< char >(toupper(str[idx]));
  }

  return str;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  string str("Jack and Jill went up the hill.");
  cout << str << endl << endl;

  cout << "upper()\n";
  str = upper(str);
  cout << str << endl << endl;

  cout << "replace()\n";
  string::size_type idx = str.find(' ');
  while(idx != string::npos){
    str.replace(idx, 1, 1, '_');
    idx = str.find(' ', idx + 1);
  }
  cout << str << endl << endl;

  cout << "READY.\n";
  return 0;
}
