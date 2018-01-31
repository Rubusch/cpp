// getint.cpp
/*
  userinput - read in some text and check if it was an int value,
  in this case transform it to an int,
  else ask again
//*/

#include <iostream>
#include <sstream>
#include <cctype>

/*
  check input value for being a number
//*/
bool isInt(std::string str)
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
  std::string tmpStr;
  std::stringstream tmpStream;

  // ask
  do{
    std::cout << "enter a test value: ";
    std::cin >> tmpStr;
    std::cout << std::endl;
    if(isInt(tmpStr)) break;
  }while(1);

  // convert: string to number
  tmpStream << tmpStr;
  tmpStream >> test_value;

  // print out
  std::cout << "the entered value was: " << test_value << "!\n";

  std::cout << "READY.\n";
  return 0;
}

