// functor.cpp
/*
  Demonstrates a functor using a Bridge pattern and a Handler facade

  +-----------------+                  +-----------------+
  | BaseFunctor     |<>----------------| BaseFunctorImpl |
  +-----------------+                  +-----------------+
         /_\                                  /_\
          |  This bridge pattern constructs    |
          |             the Functor            |
          |                                    |
  +-----------------+                  +-----------------+
  | ConcFunctor     |                  | ConcFunctorImpl |
  +-----------------+                  +-----------------+
  | FunctorImpl<    |                  | algorithm()     |
  |    Result_t     |                  +-----------------+
  |    , Arg_t >    |                     /_\   e.g. usage of 
  +-----------------+                      |    different types
 e.g.| type of operation,                  |
 say,| comparison, addition,               |
 etc.|                                     |
     |                                     |
     |                                     |
     |    +------------------------------------+    
     |    | template<                          |
     +--<>|   typename Result                  |
          |   , typename Arg1                  | 
          |   , typename Arg2 >                |     +--------+
          |   CompareFunctorHandler            |<----| Client | 
          |   : public ConcFunctorImpl         |     +--------+
          +------------------------------------+
          |  bool Functor(uint, uint)          |
          +------------------------------------+
//*/


#include <iostream>


/*
  Base Functor Implementation class

  implements a concept of a functor implementation class
  this base class should work out rather for copy constructors, 
  cloning functions or assignment operators, since operator()()
  can't be implemented fully virtual here without destroying the 
  concept
//*/
template< typename Result >
class BaseFunctorImpl
{
public:
  typedef Result
    Result_t;

  /* 
     more functions e.g. clone()
  //*/
  virtual ~BaseFunctorImpl() = 0;
};

template< typename Result >
BaseFunctorImpl< Result >::~BaseFunctorImpl()
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
template< typename Result, typename Arg1, typename Arg2 >
class ConcFunctorImpl
  : public BaseFunctorImpl< Result >
{};

// template specialization for a concrete functor implementation class
template<>
class ConcFunctorImpl< bool, unsigned int, unsigned int >
  : public BaseFunctorImpl< bool >
{
public:
  typedef unsigned int
    Arg1_t;

  typedef unsigned int
    Arg2_t;

  // returns true if arg1 is smaller than arg2
  virtual Result_t operator()(Arg1_t arg1, Arg2_t arg2)
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
template< typename Impl >
class ConcFunctor
  : public BaseFunctor< typename Impl::Result_t, typename Impl::Arg1_t, typename Impl::Arg2_t >
{
private:
  typedef typename Impl::Result_t
    Result_t;

  typedef typename Impl::Arg1_t
    Arg1_t;

  typedef typename Impl::Arg2_t
    Arg2_t;

  Impl impl_;

public:  
  Result_t operator()( Arg1_t arg1, Arg2_t arg2)
  {
    return impl_(arg1, arg2);
  }
};


/*
  Functor Handler

  a handler can be an advantage to be used as Facade to 'handle' the 
  confusing chaos of functors and functor implementations in behind
//*/
template< typename Result, typename Arg1, typename Arg2 >
class CompareFunctorHandler
  : public ConcFunctorImpl< Result, Arg1, Arg2 >
{
private:
  ConcFunctor< ConcFunctorImpl< Result, Arg1, Arg2 > > f_;

public:
  Result operator()(Arg1 arg1, Arg2 arg2)
  {
    return f_(arg1, arg2);
  }
};


/*****************************************************************************/


/*
  some algorithm function
//*/
void doSort(int* arr, unsigned int arr_size, CompareFunctorHandler< bool, unsigned int, unsigned int > comparator)
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
  CompareFunctorHandler< bool, unsigned int, unsigned int > functorHandler;

  // sort using the functor
  doSort(arr, sizeof(arr)/sizeof(int), functorHandler);

  cout << "after:";
  for(unsigned int idx=0; idx < sizeof(arr) / sizeof(int); ++idx)
    cout << " " << arr[idx];
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
