// typeinfo.cpp
/*

  general usage of typeid / type_info mechanism in C++:

  void fun(Base* pObj)
  {
    // compare the two type_info objects corresponding to the type of *pObj and
    // Derived
    std::cout << "Check the typeids:\n";

    if(typeid(*pObj) == typeid(Derived)){
      std::cout << "...aaaaaaaahh, pObj actually points to a Derived object\n";
    }
    // ...
  }

  "If you want to sort type_info objects, again you must actually store pointers
  to type_info, and this time you must use the before member function.
  Consequently, if you want to use STL's ordered containers with type_info, you
  must write a little functor and deal with pointers.

  All this is clumsy enough to mandate a wrapper class around type_info that
stores a pointer to a type_info object and provides:

  - all the member functions of type_info
  - value semantics (public copy constructor and assignment operator)
  - seamless comparisons by defining operator< and operator=="

  resources: Modern C++ Design, Alexandrescu

  Typeid works only when using virtual functions in such a case. This and some
other issues are reasons to avoid using typeid rather in C++.
//*/


#include <iostream>
#include <typeinfo>


/*
  base class - without virtual functions the typeid test won't work!
//*/
class Base
{
public:
  virtual void func();
};

void Base::func() { std::cout << "Base\n"; }


/*
  derived class
//*/
class Derived : public Base
{
public:
  void func();
};

void Derived::func() { std::cout << "Derived\n"; }


/*
  typeid-wrapper
//*/
class Typeinfo
{
private:
  const std::type_info *pInfo_;

public:
  // ctor/dtor
  Typeinfo();
  //*
  Typeinfo(const std::type_info &);
  Typeinfo(const Typeinfo &);
  Typeinfo &operator=(const Typeinfo &);
  bool operator==(const Typeinfo &) const;
};

/*
  ctor
//*/
Typeinfo::Typeinfo() {}

/*
  ctor
//*/
Typeinfo::Typeinfo(const std::type_info &t_i)
{
  // set the pointer to the address of t_i
  pInfo_ = &t_i;
}

/*
  cpy ctor
//*/
Typeinfo::Typeinfo(const Typeinfo &ti) { pInfo_ = ti.pInfo_; }

/*
  assign
//*/
Typeinfo &Typeinfo::operator=(const Typeinfo &ti)
{
  if (&ti == this)
    return *this;

  this->pInfo_ = ti.pInfo_;
  return *this;
}

/*
  equal
//*/
bool Typeinfo::operator==(const Typeinfo &rhs) const
{
  return pInfo_ == rhs.pInfo_;
}


/*
  For this demonstration here a global instance of a Base object.
//*/
Base base;


/*
  A pointer will be passed here, it can point to a Base object or to any
  derived object of Base (or we have a compile error).

  Then the pointer object will be checked if it is of type base, if not it
  HAS to be a derived type.
//*/
void isDerived(Base *pObj)
{
  Typeinfo info = typeid(base);
  if (info == typeid(*pObj)) {
    std::cout << "The passed pointer object is a Base object: DON'T DOWNCAST!";
  } else {
    std::cout << "The passed pointer object is a Derived object: now you can "
                 "downcast.";
  }
  std::cout << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  // init
  cout << "init.." << endl;
  Base b;
  Derived d;

  cout << "check \'b\' if it is of type Base:\n";
  isDerived(&b);
  cout << endl;

  cout << "now check \'d\' if it is of type Base:\n";
  isDerived(&d);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
