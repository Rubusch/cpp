// findreverse.cpp
/*
  reverse_iterator() used for find()

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 2, 3, 1, 5, 3, 4, 1, 7 };
  cout << endl;

  cout << "use find() - for \'4\'\n";
  const reverse_iterator< const int* > rev_iter
    = find(reverse_iterator< const int* >( arr + 6)
            , reverse_iterator< const int* >(arr)
           , 4); // search for '4'
  cout << endl;

  cout << "use reverse_iterator\n";
  if( rev_iter != reverse_iterator< const int* >(arr)){
    cout << "last " << *rev_iter
         << " in arr has index " << (rev_iter.base() - 1 - arr)
         << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
