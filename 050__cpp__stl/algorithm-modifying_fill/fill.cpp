// fill.cpp
/*
  modifying algorithm

  fill - assign a range of elements a certain value
  fill_n - assign a value to some number of elements

       +---+---+---+---+---+---+---+---+- -+
  arr: | ? | ? | ? | ? | ? | ? | ? | ? |   |
       +---+---+---+---+---+---+---+---+- -+
         |
         | fill(arr, arr+8, 0)
         |
        \|/
       +---+---+---+---+---+---+---+---+- -+
  arr: | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |   |
       +---+---+---+---+---+---+---+---+- -+
         |
         | fill_n(arr+2, 4, 1)
         |
        \|/
       +---+---+---+---+---+---+---+---+- -+
  arr: | 0 | 0 | 1 | 1 | 1 | 1 | 0 | 0 |   |
       +---+---+---+---+---+---+---+---+- -+

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


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init:\n";
  int arr[8];
  display(arr, 8);

  cout << "fill() with 0:\n";
  fill(arr, arr + 8, 0);
  display(arr, 8);

  cout << "fill_n() - fill with 1, starting from the 2nd element for 4 "
          "elements:\n";
  fill_n(arr + 2, 4, 1);
  display(arr, 8);

  cout << "READY.\n";
  return 0;
}
