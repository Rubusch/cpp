// number to string to number
/*
  simple conversion
//*/

#include <iostream>
#include <sstream> /* C++98 style */
#include <string>

using namespace std;


/*
  main..
//*/
int main()
{
  // string to int
  string szNumber("777");
  int iNumber = 0;

  // C++98
  cout << "C++98: string (" << szNumber << ") -> number (" << iNumber << ")\n";
  std::istringstream iss(szNumber);
  iss >> iNumber;
  if (iss.fail())
    cerr << "Failed!" << endl;
  cout << "result: number " << iNumber << endl;
  cout << endl;

  // C++11
  szNumber = "777";
  iNumber = 0;
  cout << "C++11: string (" << szNumber << ") -> number (" << iNumber << ")\n";
  iNumber = std::stoi(szNumber);
  cout << "result: number " << iNumber << endl;
  cout << endl;

  // int to string
  // C++98
  szNumber = "";
  iNumber = 777;
  cout << "C++98: number (" << iNumber << ") -> string (" << szNumber << ")\n";
  std::stringstream ss;
  ss << iNumber;
  szNumber = ss.str();
  cout << "result: string '" << szNumber << "'" << endl;
  cout << endl;

  // C++11
  szNumber = "";
  iNumber = 777;
  cout << "C++11: number (" << iNumber << ") -> string (" << szNumber << ")\n";
  szNumber = std::to_string(iNumber);
  cout << "result: string '" << szNumber << "'" << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
