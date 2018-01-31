// find.cpp
/*
  non-modifying algorithm

  find - find a value in a given range
  find_if - find the first element for which a certain predicate is true

                     ___     ___
        +---+---+---+---+---+---+- -+
  arr:  | 1 | 3 | 5 | 4 | 2 | 4 |   |
        +---+---+---+---+---+---+- -+
                      |
            find(arr, arr + 6, 4)

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


/*
  helper function for functor
//*/
template< class T > // T has to be an integer type
unsigned int checksum_help( T val)
{
  unsigned int sum = 0;
  while(val > 0){
    sum += val % 10;
    val /= 10;
  }
  return sum;
}


/*
  functor class itself
//*/
template< class T >
class Checksum_t
  : public std::unary_function< T, bool >
{
private:
  const unsigned int sum_;

public:
  explicit Checksum_t(unsigned int sum)
    : sum_(sum) {}

  bool operator()(T val) const { return checksum_help(val); }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr_a[] = { 1, 4, 2, 5, 3, 2 };
  cout << endl;

  cout << "use find()\n";
  const int* idx = find( arr_a, arr_a + 6, 4);
  if(idx != arr_a + 6){ // compares addresses
    cout << "found 2, index " << (idx - arr_a) << endl;
  }
  cout << endl;

  cout << "use find_if()\n";
  const int arr_b[] = { 22, 12, 13, 23, 24, 35 };
  idx = find_if( arr_b, arr_b + 6, Checksum_t< int >(4));
  if(idx != arr_b + 6){ // compares addresses
    cout << *idx << " has the checksum 4." << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
