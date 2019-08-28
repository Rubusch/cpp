// foreach.cpp
/*
  non-modifying algorithm

  for_each - apply a function to a range of elements

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


template< class T >
class SumUp
  : public std::unary_function< T, void >
{
private:
  T sum_;

public:
  explicit SumUp( const T& sum = T())
    : sum_(sum) {}

  void operator()( const T& tmp){ sum_ += tmp; }
  T getSum() const { return sum_; }
};


/*
  a or b
//*/
void a_or_b(int idx)
{
  std::cout << ((idx % 2 == 0) ? 'a' : 'b');
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 0, 1, 2, 3, 4, 5 };
  cout << endl;

  cout << "use for_each()\n";
  for_each( arr + 1, arr + 5, a_or_b);
  cout << endl;

  cout << "init class sum using for_each()\n";
  SumUp< int > sum = for_each( arr + 1, arr + 5, SumUp< int >());
  cout << endl;

  cout << "output:\n";
  cout << " " << sum.getSum();
  cout << endl << endl;

  cout << "...which is actually the same like the following implementation (doing the same):\n";
  cout << " " << (for_each( arr + 1, arr + 5, SumUp< int >())).getSum();
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
