// traits
/*
  simple implementation of a type trait to check for member pointers

  example www.c-plusplus.de/forum
//*/

#include <iostream>


/*
  trait
//*/
template < typename T >
struct is_member_pointer {
  static const bool value = false;
};

template < typename Result, typename Class >
struct is_member_pointer< Result(Class::*) > {
  static const bool value = true;
};


/*
  class to test
//*/
struct SomeClass {
  int a;
};


/*
  template function
//*/
template < typename MemberPointer >
void foo(MemberPointer memptr)
{
  std::cout << "is member pointer? "
            << is_member_pointer< MemberPointer >::value << std::endl;
}


/*
  main..
//*/
int main()
{
  foo(&SomeClass::a);
  // correspondes to the following and results in being "1"
  // foo< int SomeClass::* >( &SomeClass::a );

  foo(12);
  // correspondes to the following and results in being "0"
  // foo< int >( 12 );

  std::cout << "READY.\n";
  return 0;
}
