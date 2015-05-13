// classtemplatespecialization.cpp
/*
  demonstrates the class template specialization
//*/


#include <iostream>


using namespace std;


template< typename T >
class Foobar
{
public:
  void func()
  {
    cout << "Foobar< T >::func()\n";
  }
};


template<>
class Foobar< int >
{
public:
  void func()
  {
    cout << "Foobar< int >::func()\n";
  }
};

int main()
{
  Foobar< int > fb_1;
  Foobar< char > fb_2;

  fb_1.func();
  fb_2.func();

  cout << "READY.\n";
  return 0;
}
