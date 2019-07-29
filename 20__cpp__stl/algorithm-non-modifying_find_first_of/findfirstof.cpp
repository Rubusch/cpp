// findfirstof.cpp
/*
  non-modifying algorithm

  find_first_of - search for any one of a set of elements

           +---+---+---+---+- -+
  arr_a:   | 3 | 7 | 5 | 2 |   |
           +---+---+---+---+- -+

                    ___     ___
           +---+---+---+---+---+- -+
  arr_b:   | 4 | 6 | 2 | 4 | 7 |   |
           +---+---+---+---+---+- -+
                     |
     find_first_of(arr_b, arr_b + 5, arr_a, arr_a + 4)

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr_a[] = { 3, 7, 5, 2 };
  const int arr_b[] = { 4, 6, 2, 4, 7 };
  cout << endl;

  cout << "find_first_of() - first example\n";
  const int* ptr = find_first_of(arr_b
                                 , arr_b+5
                                 , arr_a
                                 , arr_a+4);
  if(ptr != arr_b + 5){
    cout << *ptr << " is the first element which is contained in arr_b and in arr_a.\n";
  }
  cout << endl;

  cout << "find_first_of() - second example\n";
  ptr = find_first_of(arr_b
                      , arr_b+5
                      , arr_b
                      , arr_b+4
                      , not_equal_to< int >());
  if(ptr != arr_b + 5){
    cout << *ptr << " is the first element contained in arr_b but NOT in arr_a.\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
