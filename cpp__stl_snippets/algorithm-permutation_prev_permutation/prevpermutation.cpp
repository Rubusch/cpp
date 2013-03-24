// prevpermutation.cpp
/*
  permutation algorithm

  prev_permutation - generates the next smaller lexicographic permutation of a range of elements

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>


/*
  faculty implementation
//*/
template< int n > struct Faculty
{
  enum { value = n * Faculty< n-1 >::value };
};

template<> struct Faculty<0>
{
  enum { value = 1 };
};

/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 3, 2, 1 }; // has to be ordered this way!!!
  const int number = sizeof(arr) / sizeof(*arr);
  int idx = Faculty<number>::value;
  copy(arr, arr+3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  do{
    cout << --idx << ". permutation: ";
    copy(arr, arr+number, ostream_iterator< int >(cout, " "));
    cout << endl;

  }while(prev_permutation(arr, arr+number));
  cout << endl;

  cout << "READY.\n";
  return 0;
}
