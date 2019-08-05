#include <iostream>
#include <algorithm>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  char arr[] = { 'a', 'b', 'c', 'd' };
  bool flag = true;

  do{
    if(flag){
      copy(arr, &arr[2], ostream_iterator< char >(cout, ""));
      cout << endl;
    }
    flag = !flag;

  }while(next_permutation(arr, &arr[4]));

  cout << endl;

  cout << "READY.\n";
  return 0;
}

