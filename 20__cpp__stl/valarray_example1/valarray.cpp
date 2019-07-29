// valarray.cpp
/*
  valarray - example

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>


/*
  operator <<
//*/
template< class T >
std::ostream& operator<<(std::ostream& os, const std::valarray< T >& va)
{
  for(size_t idx = 0; idx < va.size(); ++idx){
    os << va[idx] << " ";
  }
  return os;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 1, 3, 5, 7, 9 };
  valarray< int > va_x(arr, 5), va_y(arr, 5);
  cout << "x = \t\t" << va_x << "\ny = \t\t" << va_y << endl;
  cout << endl;

  cout << "polulate va_y with other values, here, the index\n";
  for(size_t idx = 0; idx < va_y.size(); ++idx){
    va_y[idx] = idx;
  }
  cout << "x = \t\t" << va_x << "\ny = \t\t" << va_y << endl;
  cout << endl;

  cout << "reverse() - va_x\n";
  reverse(&va_x[0], &va_x[va_x.size()]);
  va_x -= 1;
  cout << "x = \t\t" << va_x << endl;
  cout << endl;

  cout << "abs() - init new valarray z\n";
  valarray< int > va_z = abs(va_x - va_y);
  cout << "z = \t\t" << va_z << endl;
  cout << endl;

  cout << "sum()\n";
  for( int idx = 0; idx < 5; ++idx) cout << ((idx == 0) ? "" : " + ") << va_z[idx];
  cout << " = " << va_z.sum() << endl;
  cout << endl;

  cout << "cshift(2)\nz = \t\t" << va_z.cshift(2) << endl;
  cout << endl;

  cout << "valarray< bool >\n";
  valarray< bool > va_bool(va_z > 1);
  cout << "va/bool = \t" << boolalpha << va_bool << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
