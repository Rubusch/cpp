/*
  C++11 - rvalue reference, move semantics and perfect forwarding
  (Meyers / item 25)

  Use 'std::move' on rvalue referneces and 'std::forward' on
  universal references!!!

  Local objects which could be returned fall under the RVO (return value
  optimization), and should not be moved or forwarded.

  Avoid using 'std::forward' with rvalue references, even worse is the idea of
  using 'std::move' with universal references!!!



  DEFINITIONS (by Scott Meyers)

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  universal reference - the type of the function parameter is rvalue reference
              to type template parameter


  move semantics: makes it possible for compilers to replace expensive copying
  operations with less expensive moves. In the same way that copy constructors
  and copy assignment operators give you control over what it means to copy
  objects, move constructors and move assignment operators offer control over
  the semantics of moving. Move semantics also enables the creation of move-only
  types, such as 'std::unique_ptr', 'std::future' and 'std::thread'.

  perfect forwarding: makes it possible to write function templates that take
  arbitrary arguments and forward them to other functions such that the target
  funcitons receive exactly the same arguments as were passed to the forwarding
  functions



  DEFINITIONS (by cppreference.com)

  glvalue ('generalized' lvalue) is an expression whose evaluation determines
          the identity of an object, bit-field, or function

  prvalue ('pure' rvalue) is an expression whose evaluation either
        - computes the value of the operand of an operator (such prvalue has
          no result object), or
        - initializes an object or a bit-field (such prvalue is said to have
          a result object). All class and array prvalues have a result object
          even if it is discarded. In certain contexts, temporary
          materialization occurs to create a temporary as the result object;

  xvalue (an 'eXpiring' value) is a glvalue that denotes an object or bit-field
          whose resources can be reused

  lvalue (so-called, historically, because lvalues could appear on the
          left-hand side of an assignment expression) is a glvalue that is not
          an xvalue
          examples: *a, --a, ++a

  rvalue (so-called, historically, because rvalues could appear on the
          right-hand side of an assignment expression) is a prvalue or an xvalue
          examples: &a, a--, a++

  Names of rvalue reference variables are lvalues and have to be converted to
  xvalues to be bound to the function overloads that accept rvalue reference
  parameters, which is why move constructors and move assignment operators
  typically use std::move
  One exception is when the type of the function parameter is rvalue reference
  to type template parameter ("forwarding reference" or "universal reference"),
  in which case std::forward is used instead.



  CONCLUSION

  - apply 'std::move' to rvalue references and 'std::forward' to universal
    references the last time each is used

  - do the same thing for rvalue references and universal references being
    returned from functions that return by value

  - never apply 'std::move' or 'std::forward' to local objects if they would
    otherwise be eligible for the return value optimization!!!

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class Fruit
{
protected:
  string name_;

public:
  /*
    template< typename T >
    void setName(T&& name)
    {
      cout << "CALLED: setName(T&&) - UNIVERSAL REFERENCE, BAD IDEA (catches
  all)!!!" << endl; name_ = name;
    }
  // */

  // !!! if these are not '{}', vtable errors will follow !!!
  virtual void setName(const string &name) {}
  virtual void setName(string &&name) {}

  // needed for virtual functions in derived classes
  virtual ~Fruit(){};
};


class Lemon : public Fruit
{
public:
  // to make this visible the function 'initializer()' has to have a
  // template declaration!
  //
  // alternatively both classes were derived from class Fruit, the virtual
  // functions override their base class's versions, but since in
  // 'initializer()' a base class reference / pointer is passed, still the
  // additional 'universal reference' version of the function 'setName()'
  // won't be called
  //
  // this changes when 'initializer()' becomes a template function, template
  // type deduction can be used and objects of class Orange or Lemon behave as
  // full such objects even passed by a base class reference or pointer,
  // respectively
  template < typename T >
  void setName(T &&name)
  {
    cout << "CALLED: setName(T&&) - UNIVERSAL REFERENCE, BAD IDEA (catches "
            "all)!!!"
         << endl;
    name_ = name;
  }

  virtual void setName(const string &name) override
  {
    cout << "CALLED: setName(const string&) - set from const lvalue" << endl;
    name_ = name;
  }

  virtual void setName(string &&name) override
  {
    cout << "CALLED: setName(string&&) - set from rvalue" << endl;
    name_ = name;
  }
};


class Orange : public Fruit
{
public:
  virtual void setName(const string &name) override
  {
    cout << "CALLED: setName(const string&) - set from const lvalue" << endl;
    name_ = name;
  }

  virtual void setName(string &&name) override
  {
    cout << "CALLED: setName(string&&) - set from rvalue" << endl;
    name_ = name;
  }
};

// for comments on template declaration see above comment
template < typename T >
void initializer(T &fruit, string name)
{
  cout << name << ": rvalue initialization" << endl;
  fruit.setName("foo");
  cout << endl;

  cout << name << ": lvalue initialization" << endl;
  string str = name;
  fruit.setName(str);
  cout << endl;
}


int main(void)
{
  Lemon lemon;
  Orange orange;

  initializer(lemon, "Lemon");
  initializer(orange, "Orange");

  cout << "READY." << endl;
}
