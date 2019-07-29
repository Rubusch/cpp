// replacecopy.cpp
/*
  modifying algorithm

  replace_copy - copy a range, replacing certain elements with new ones
  replace_copy_if - copy a range of elements, replacing those for which a predicate is true

                  ___     ___
         +---+---+---+---+---+---+---+- -+
  arr_a: | 0 | 1 | 2 | 3 | 2 | 1 | 0 |   |
         +---+---+---+---+---+---+---+- -+

       replace_copy(arr_a, arr_a+7, arr_b, 2, 5)
                                       |
                  ___     ___          |
         +---+---+---+---+---+---+---+- -+
  arr_b: | 0 | 1 | 5 | 3 | 5 | 1 | 0 |   |
         +---+---+---+---+---+---+---+- -+

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


void display(int* arr_a, int siz_a, int* arr_b, int siz_b)
{
  std::cout << "arr_a: ";
  copy(arr_a, arr_a+siz_a, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl;
  std::cout << "arr_b: ";
  copy(arr_b, arr_b+siz_b, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = { 0, 1, 2, 3, 2, 1, 0 };
  int arr_b[7]; fill(arr_b, arr_b+7, 0);
  display(arr_a, 7, arr_b, 7);

  cout << "replace_copy() - replace 2 with 5,\nand copy the result to arr_b\n";
  replace_copy(arr_a, arr_a+7, arr_b, 2, 5);
  display(arr_a, 7, arr_b, 7);

  cout << "replace_copy_if() - replace all values smaller than 0 with 9,\nand copy the result to the same container\narr_b: ";
  replace_copy_if(arr_b, arr_b+7, ostream_iterator< int >(cout, " "), bind2nd(less< int >(), 1), 9);
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
