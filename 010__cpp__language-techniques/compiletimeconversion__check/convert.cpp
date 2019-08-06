// convert.cpp
/*
  convertibility at compile-time

"Given two arbitrary types T and U that you know nothing about, how can you
detect whether or not U inherits form T? Discovering such relationships at
compiletime is key to implementing advanced optimizations in generic libraries.
In a generic function, you can rely on an optimized algorithm if a class
implements a certain interface. Discovering this at compile time means not
having to use dynamic_cast, which is costly at runtime."

"The idea of conversion detection relies on using sizeof in conjunction with
overloaded functions. We provide two overloads of a function: One accepts the
type to convert to (U), and the other accepts just about anything else. We call
the overloaded function with a temporary of type T, the type whose
convertibility to U we want to determine. If the function that accepts a U gets
called, we know that T is convertible to U; if the fallback function gets called,
then T is not convertible to U. To detect which function gets called, we arrange
the two overloads to return types of different sizes, and then we discriminate
with sizeof. The types themselves do not matter, as long as they have different
sizes."

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>
#include <vector>


/*
  conversion from T to U
//*/
template< class T, class U >
class Conversion
{
private:
  /*
    the following stuff only needs to be declared
  //*/
  typedef char Small;
  class Big { char dummy[2]; };
  static Small Test( const U& );
  static Big Test(...);
  static T MakeT();

public:
  /*
    the important step is this here - checking if conversion is possible or not
  //*/
  enum{ exists = sizeof( Test( MakeT() ) ) == sizeof( Small ) };
};



/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "Conversion from \'double\' to \'int\':\t\t" << ( ( Conversion< double, int >::exists ) ? "exists." : "failed!" ) << '\n'
       << "Conversion from \'char\' to \'char*\':\t\t" << ( ( Conversion< char, char* >::exists ) ? "exists." : "failed!" ) << '\n'
       << "Conversion from \'size_t\' to \'vector<int>\':\t" << ( ( Conversion< size_t, vector< int > >::exists ) ? "exists" : "failed!" ) << '\n';
  cout << endl;

  cout << "READY.\n";
  return 0;
}
