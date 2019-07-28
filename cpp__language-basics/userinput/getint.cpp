// getint.cpp
/*
  userinput - read in some text and check if it was an int value,
  in this case transform it to an int,
  else ask again
//*/

#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

/*
  check input value for being a number
//*/
bool isInt(string str)
{
  for(unsigned int idx=0; idx < str.size(); ++idx){
    if(!isdigit(str.at(idx))) return false;
  }
  return true;
}


/*
  some main
//*/
int main()
{
  // init
  int test_value = 0;
  string tmpStr;
  stringstream tmpStream;

  // ask
  do{
    cout << "enter a test value: ";
    cin >> tmpStr;
    cout << endl;
    if(isInt(tmpStr)) break;
  }while(1);

  // convert: string to number
  tmpStream << tmpStr;
  tmpStream >> test_value;

  // print out
  cout << "the entered value was: " << test_value << "!\n";

  cout << "READY.\n";
  return 0;
}

