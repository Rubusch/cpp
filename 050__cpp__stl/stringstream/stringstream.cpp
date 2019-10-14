// stringstream.cpp
/*
  stringstream - convert number to string and vice versa

  resources: Kuhlins and Schader (2003)
//*/


#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


/*
  convert double to string
//*/
std::string double2string(double db)
{
  std::ostringstream os;
  os << std::setprecision(2) << std::fixed << std::showpoint << db
     << " (as string)";
  return os.str();
}


/*
  convert string to double
//*/
double string2double(const std::string &str)
{
  double db;
  std::istringstream(str) >> db;
  return db;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  const string euro = double2string(12.34);
  cout << "euro: " << euro << endl;
  cout << endl;

  cout << "euro (as number): " << string2double(euro) << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
