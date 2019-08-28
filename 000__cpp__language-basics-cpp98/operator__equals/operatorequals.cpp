// opequality.cpp
/*
  demonstrates overloading of the operator==()
//*/

#include <iostream>


template<class T>
class SomeType
{
private:
  T value;

public:
  // ctor
  SomeType(T t);

  // func
  T getVal() const;

  // operator
//*
  bool operator==(const SomeType<T>& rhs) const;
/*/
  // outside of class it would be somethin like
  inline
  bool operator==(const SomeType<T>& lhs, const SomeType<T>& rhs) const
  {
    return lhs.getVal() == rhs.getVal();
  }
// */
};

template<class T>
SomeType<T>::SomeType(T t)
:value(t)
{}

template<class T>
T SomeType<T>::getVal() const
{
  return value;
}

//*
template<class T>
bool SomeType<T>::operator==(const SomeType<T>& rhs) const
{
  // by default only compares the size with an int rhs int value
  return value == rhs.getVal();
}
// */


/*
  some main
//*/
int main()
{
  // init
  SomeType<int> a(7), b(77);
  std::cout << "a = " << a.getVal() << "\nb = " << b.getVal() << std::endl;
  std::cout << std::endl;

  // comparison
  std::cout << "(a == b) -> " << "(" << a.getVal() << " == " << b.getVal() << ") -> " << (a == b) << std::endl;
  std::cout << std::endl;

  std::cout << "READY.\n";
  return 0;
}
