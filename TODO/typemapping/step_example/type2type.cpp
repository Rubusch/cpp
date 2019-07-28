/*
  demo example to use polymorphy via type_mapping for function calls
 */

#include <iostream>

using namespace std;

class StepForward;
class StepToTheLeft;
class StepToTheRight;
class NoStep;



// Type2Type Trick
template< typename T >
struct Type2Type
{
  typedef T OriginalType;
};






template< class U >
StepForward* doStep( const U& arg, Type2Type< EStepID_Forward > )
{
  return new StepForward( arg );
}

template< class U >
StepToTheRight* doStep( const U& arg, Type2Type< EStepID_Right > )
{
  return new StepToTheRight( arg );
}

template< class U >
StepToTheLeft* doStep( const U& arg, Type2Type< EStepID_Left > )
{
  return new StepToTheLeft( arg );
}

template< class U, class T >
NoStep* doStep( const U& arg, Type2Type< T > )
{
  // default
  return new NoStep();
}


// TODO

class StepForward
{
  // TODO
};


int main()
{
  // TODO
  return 0;
}
