// functor.cpp
/*
  simple basic functor example
//*/


#include <iostream>


/*
  a simple Functor class, in C this might be a function pointer in a callback
  (a function that takes a function pointer as argument and returns a result)

  'struct' or 'class' is equal, but 'struct' is 'public' by default
//*/
struct CompareFunctor
{
  /*
    returns true if arg1 is smaller than arg2
  //*/
  bool operator()(unsigned int arg1, unsigned int arg2)
  {
    return arg1 < arg2;
  }
};


/*
  some sorting function
//*/
void doSort(int* arr, unsigned int arr_size, CompareFunctor comparator)
{
  if(arr_size < 2) return;

  int tmp=0;
  unsigned idx=arr_size-2;

  bool swapped = true; 

  do{
    if(idx == arr_size-2){
      if(!swapped) break;
      idx=0;
      swapped = false;
    }else ++idx;

    if(!comparator(arr[idx], arr[idx+1])){
      tmp = arr[idx];
      arr[idx] = arr[idx+1];
      arr[idx+1] = tmp;
      
      swapped = true;
    }

  }while(true);
}


/*
  some main..
//*/
int main()
{
  using namespace std;

  int arr[] = { 3, 4, 6, 1, 7, 5, 2 };

  cout << "before:";
  for(unsigned int idx=0; idx < sizeof(arr) / sizeof(int); ++idx)
    cout << " " << arr[idx];
  cout << endl << endl;

  // use the functor
  CompareFunctor functor;

  // sort using the functor
  doSort(arr, sizeof(arr)/sizeof(int), functor);

  cout << "after:";
  for(unsigned int idx=0; idx < sizeof(arr) / sizeof(int); ++idx)
    cout << " " << arr[idx];
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
