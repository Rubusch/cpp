// sametype.cpp
/*
  Check if a conversion is possible because it's the same type.

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>
#include <vector>


/*
  class Conversion
//*/
template<class T, class U>
class Conversion
{
private:
  typedef char Small;
  class Big{ char dummy[2]; };
  static Small Test( const U& );
  static Big Test(...);
  static T MakeT();

public:
  enum{ exists = sizeof(Test(MakeT())) == sizeof(Small) };

  // check for the same type
  enum{ sameType = false };
};


/*
  sameType will be implemented as partial specialization of class Conversion
//*/
template<class T>
class Conversion<T, T>
{
public:
  // check for typeconversion
  enum{ exists = 1, sameType = 1 };
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "Conversion from \'double\' to \'int\':\t\t" << ((Conversion<double, int>::exists) ? "exists." : "failed!") << '\n'
       << "Conversion from \'char\' to \'char*\':\t\t" << ((Conversion<char, char*>::exists) ? "exists." : "failed!") << '\n'
       << "Conversion from \'size_t\' to \'vector<int>\':\t" << ((Conversion<size_t, vector<int> >::exists) ? "exists" : "failed!") << '\n'
       << "Conversion from \'double\' to \'double\':\t\t" << ((Conversion<double, double>::exists) ? "exists." : "failed!") << '\n';
  cout << endl;

  cout << "Ready.\n";
  return 0;
}
