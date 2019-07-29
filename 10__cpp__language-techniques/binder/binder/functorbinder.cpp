// functorbinder.cpp
/*
  demonstrates the recursive use of a functor and a handmade binder

  See the STL for bind1st and bind2nd binders, for more flexibility either you
  need to write manually a binder or you need to use the boost::binder()
//*/


#include <iostream>
#include <vector>
#include <algorithm>


/*
  step 1/3: definition of a functor
//*/
template< class T >
struct EqualsTo
{
  //  bool operator()(const T& arg1, const T& arg2) const { return arg1 > arg2; }
  bool operator()(const T& arg1, const T& arg2) const {
    std::cout << "arg1: '" << arg1 << "', arg2: '" << arg2 << "'" << std::endl;
    // the implementation of an operation
    // to be implemented here
    return arg1 == arg2;
  }
};


/*
  step 2/3: another functor to do a recursive functor call to be able to use a
  unary operation for two arguments
//*/
template< class Operation, class T >
class Binder
{
private:
  const Operation op_;
  const T item_;

public:
  Binder( const Operation& op, const T& arg)
    : op_(op), item_(arg)
  {}

  bool operator()(const T& item) const { return op_( item, item_); }
};


/*
  step 3/3: a function to connect the two functors.. in STL this is used as "trait"

  This is just a function call! The instance of "Binder" is only locally here
  within the scope of the function, therefore there is no reference to the
  actual instance. Binder works as Functor!
//*/
template< class Operation, class T > inline
Binder< Operation, T > bindit( const Operation& op, const T& item)
{
  return Binder< Operation, T >(op, item);
}


/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "init a vector with 10 random elements\n";
  vector< int > vec( 1, 12 );
  vec.push_back( 23 );
  vec.push_back( 34 );
  vec.push_back( 45 );
  vec.push_back( 50 );
  vec.push_back( 666 );
  vec.push_back( 777 );
  vec.push_back( 888 );
  cout << endl;

  cout << "look for \'50\' within these elements\n";
  vector< int >::iterator iter = find_if( vec.begin(), vec.end(), bindit( EqualsTo< int >(), 50));
  cout << endl;

  cout << "\'50\' was contained? -> " << ((iter != vec.end()) ? "Yes!" : "No!" ) << endl;

  cout << "READY.\n";
  return 0;
}
