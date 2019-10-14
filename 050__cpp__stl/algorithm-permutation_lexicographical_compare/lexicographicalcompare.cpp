// lexicographicalcompare.cpp
/*
  permutation algorithm

  lexicographical_compare - returns true if one range is lexicographically les
than another

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>


/*
  output-helper
//*/
void display(int *arr_a, int size_a, int *arr_b, int size_b)
{
  std::cout << "arr_a: \t";
  copy(arr_a, arr_a + size_a, std::ostream_iterator< int >(std::cout, " "));
  std::cout << "\narr_b: \t";
  copy(arr_b, arr_b + size_b, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {1, 7, 3, 5, 2};
  int arr_b[] = {1, 7, 3, 6};
  display(arr_a, 5, arr_b, 4);

  cout << "lexicographical_compare()\n";
  bool is = lexicographical_compare(arr_a, arr_a + 5, arr_b, arr_b + 4);
  cout << "arr_a < arr_b in relation to operator< " << boolalpha << is << endl;
  cout << endl;

  cout << "lexicographical_compare() using less< int >()\n";
  is = lexicographical_compare(arr_a, arr_a + 5, arr_b, arr_b + 4,
                               less< int >());
  cout << "arr_a < arr_b in relation to operator< " << boolalpha << is << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
