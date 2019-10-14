// generate.cpp
/*
  modifying algorithm

  generate - saves the result of a function in a range
  generate_n - saves the result of N applications of a funcion

       +---+---+---+---+---+---+- -+
  arr: | ? | ? | ? | ? | ? | ? |   |
       +---+---+---+---+---+---+- -+
         |
         | fill(arr, arr+8, 0)
         |
        \|/
       +---+---+---+---+---+---+- -+
  arr: | 1 | 2 | 3 | ? | ? | ? |   |
       +---+---+---+---+---+---+- -+
         |
         | fill_n(arr+2, 4, 1)
         |
        \|/
       +---+---+---+---+---+---+- -+
  arr: | 1 | 2 | 3 | 4 | 5 | 6 |   |
       +---+---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>


void display(int *arr, int size)
{
  std::cout << "arr: ";
  copy(arr, arr + size, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


template < class T >
class Counter
{
private:
  T idx_;

public:
  Counter(T start = 1) : idx_(start) {}
  T operator()() { return ++idx_; }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[6];
  fill(arr, arr + 6, 0);
  display(arr, 6);

  cout << "generate() - set the first 3 elements\n";
  generate(arr, arr + 3, Counter< int >());
  display(arr, 6);

  cout << "generate_n() - set 3 elements starting at the 3rd one\n";
  generate_n(arr + 3, 3, Counter< int >(4));
  display(arr, 6);

  cout << "READY.\n";
  return 0;
}
