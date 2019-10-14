// swapranges.cpp
/*
  modifying algorithm

  swap_ranges - swap two ranges of elements

              ___ ___ ___
         +---+---+---+---+---+---+- -+
  arr_a: | 1 | 3 | 5 | 2 | 4 | 6 |   |
         +---+---+---+---+---+---+- -+

          ___ ___ ___
         +---+---+---+---+- -+
  arr_b: | 9 | 7 | 0 | 8 |   |
         +---+---+---+---+- -+

              |
              | swap_ranges(arr_a+1, arr_a+4, arr_b)
              |
             \|/

              ___ ___ ___
         +---+---+---+---+---+---+- -+
  arr_a: | 1 | 9 | 7 | 0 | 4 | 6 |   |
         +---+---+---+---+---+---+- -+

          ___ ___ ___
         +---+---+---+---+- -+
  arr_b: | 3 | 5 | 2 | 8 |   |
         +---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>


void display(int *arr_a, int siz_a, int *arr_b, int siz_b)
{
  std::cout << "arr_a: ";
  copy(arr_a, arr_a + siz_a, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl;

  std::cout << "arr_b: ";
  copy(arr_b, arr_b + siz_b, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {1, 3, 5, 2, 4, 6};
  int arr_b[] = {9, 7, 0, 8};
  cout << endl;

  display(arr_a, 6, arr_b, 4);

  cout << "swap_ranges()\n";
  swap_ranges(arr_a + 1, arr_a + 4, arr_b);
  cout << endl;

  display(arr_a, 6, arr_b, 4);

  cout << "READY.\n";
  return 0;
}
