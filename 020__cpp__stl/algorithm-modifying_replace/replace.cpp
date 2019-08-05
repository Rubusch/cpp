// replace.cpp
/*
  modifying algorithm

  replace - replace every occurrence of some value in a range with another value
  replace_if - change the values of elements for which a predicate is true

                ___     ___
       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 3 | 2 | 1 | 0 |   |
       +---+---+---+---+---+---+---+- -+

         |
         |  replace(arr, arr+7, 2, 5)
         |
        \|/
                ___     ___
       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 5 | 3 | 5 | 1 | 0 |   |
       +---+---+---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


void display(int* arr, int size)
{
  std::cout << "arr: ";
  copy(arr, arr+size, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 0, 1, 2, 3, 2, 1, 0 };
  display(arr, 7);

  cout << "replace() - replace all 2 with 5\n";
  replace(arr, arr+7, 2, 5);
  display(arr, 7);

  cout << "replace_if() - replace all values smaller than 1 with 9\n";
  replace_if(arr, arr+7, bind2nd( less< int >(), 1), 9);
  display(arr, 7);

  cout << "READY.\n";
  return 0;
}
