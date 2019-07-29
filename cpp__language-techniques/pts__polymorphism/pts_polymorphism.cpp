// pts_polymorphism.cpp
/*
  Demonstrates polymorphism achieved by partial template specialization.

  Using partial specialized templates it is possible to implemente some
  typespecific behaviour, as also keep a common templated behaviour.

  This is polymorphism on a templated level!!
//*/


#include <iostream>


using namespace std;


/*
  common declaration of a two typed templated class - THIS IS ESSENTIAL!
//*/
template< typename U, typename V >
class SomeClass;



/*
  normal templated implementation
//*/
template< typename U, typename V >
class SomeClass
{
private:
  U var1;
  V var2;
  V var3;

public:
  SomeClass(U arg1, V var2, V arg3);
  void output();
};

template< typename U, typename V >
SomeClass< U, V >::SomeClass(U arg1, V arg2, V arg3)
  : var1(arg1), var2(arg2), var3(arg3)
{}

template< typename U, typename V >
void SomeClass< U, V >::output()
{
  cout << "normal templated class\n\tvar1 = " << var1
       << "\n\tvar2 = " << var2
       << "\n\tvar3 = " << var3
       << "\nThis class behaves differently!\n\n";
}



/*
  partial specialized template class implementation
//*/
template< typename U >
class SomeClass< U, int >
{
private:
  U var1;
  int num;
  /*
    the int here is just an example, it's not necessary - has
    nothing to do with the int in the template declaration
  //*/

public:
  SomeClass(U arg1);
  void output();
};

template< typename U >
SomeClass< U, int>::SomeClass( U arg1)
  : var1(arg1), num(777)
{}

template< typename U >
void SomeClass< U, int >::output()
{
  cout << "partial specialized\n\tvar1 = " << var1 << "\n\tnum = " << num << "\n\n";
}



/*
  main..
//*/
int main()
{
  // other polymorphic instance of the same class
  SomeClass< int, string > sc2(123, "Hello", "World!");
  sc2.output();

  // partial specialized template instantiation
  SomeClass< string, int > sc1("Hello World!");
  sc1.output();


  cout << "READY.\n";
  return 0;
}
