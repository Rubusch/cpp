// functor.cpp
/*
  Demonstrates a functor using a bridge pattern

                   +-----------------+                  +-----------------+
                   | BaseFunctor     |<>----------------| BaseFunctorImpl |
                   +-----------------+                  +-----------------+
                           /_\                                  /_\
                            |  This bridge pattern constructs    |
                            |             the Functor            |
                            |                                    |
  +--------+       +-----------------+                  +-----------------+
  | Client |------>| ConcFunctor     |                  | ConcFunctorImpl |
  +--------+       +-----------------+                  +-----------------+
                   | FunctorImpl<    |                  | algorithm()     |
                   |    Result_t     |                  +-----------------+
                   |    , Arg_t >    |
                   +-----------------+

//*/


#include <iostream>


// forward declarations
template< typename Result_t > class BaseFunctorImpl;
template< typename Result_t, typename Arg1_t, typename Arg2_t > class ConcFunctorImpl;
template< typename Result_t, typename Arg1_t, typename Arg2_t > class BaseFunctor;
class ConcFunctor;

void doSort(int* arr, unsigned int arr_size, ConcFunctor comparator);


/*
  Base Functor Implementation class

  implements a concept of a functor implementation class
  this base class should work out rather for copy constructors,
  cloning functions or assignment operators, since operator()()
  can't be implemented fully virtual here without destroying the
  concept
//*/
template< typename Result_t >
class BaseFunctorImpl
{
public:
  virtual ~BaseFunctorImpl() = 0;
};

template< typename Result_t >
BaseFunctorImpl< Result_t >::~BaseFunctorImpl()
{}


/*
  Concrete Functor Implementation class

  the class has the concrete implementation of the algorithm to be performed
  to gain even more flexibility in a lib or having a huge amount of diferent
  implementations, the class should only contain trunks like this:

  virtual Result_t operator()(Arg1_t, Arg2_t) = 0;

  Extensions here might be for instance:
  - comparator for int
  - comparator for double
  - comparator for unsigned long
  ...

  Extensions for derived classes of this might be e.g. (each one can be
  teplatitized for various types again..):
  - comparator
  - multiplicator
  - divisor
  ...
//*/
template< typename Result_t, typename Arg1_t, typename Arg2_t >
class ConcFunctorImpl
  : public BaseFunctorImpl< Result_t >
{
public:
  /*
    returns true if arg1 is smaller than arg2
  //*/
  Result_t operator()(Arg1_t arg1, Arg2_t arg2)
  {
    return arg1 < arg2;
  }
};


/*
  Base Functor class

  implements a concept for a functor class
//*/
template< typename Result_t, typename Arg1_t, typename Arg2_t >
class BaseFunctor
{
public:
  virtual Result_t operator()(Arg1_t arg1, Arg2_t arg2) = 0;
  virtual ~BaseFunctor() = 0;
};

template< typename Result_t, typename Arg1_t, typename Arg2_t >
BaseFunctor< Result_t, Arg1_t, Arg2_t >::~BaseFunctor()
{}


/*
  the functor itself

  calls an implementation initialized by concrete types

  Extensions here might be diferent invokations of Implementors
  depending on the types and names (bridge pattern), so e.g.
  - functor for comparison
  - functor for multiplication
  ...
  (depending on types, etc)
//*/
class ConcFunctor
  : public BaseFunctor< bool, unsigned int, unsigned int >
{
public:
  typedef ConcFunctorImpl< bool, unsigned int, unsigned int >
    Impl_t;

private:
  Impl_t impl_;

public:
  bool operator()( unsigned int arg1, unsigned int arg2)
  {
    return impl_(arg1, arg2);
  }
};


/*****************************************************************************/


/*
  some algorithm function
//*/
void doSort(int* arr, unsigned int arr_size, ConcFunctor comparator)
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
  ConcFunctor functor;

  // sort using the functor
  doSort(arr, sizeof(arr)/sizeof(int), functor);

  cout << "after:";
  for(unsigned int idx=0; idx < sizeof(arr) / sizeof(int); ++idx)
    cout << " " << arr[idx];
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
