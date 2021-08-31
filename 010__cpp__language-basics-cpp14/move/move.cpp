/*
  C++11 - rvalue reference, move semantics and perfect forwarding
  (Meyers / item 23)



  DEFINITIONS (by Scott Meyers)

  lvalue - has an address, e.g. a user maintained variable or memory
           with accessible address

  rvalue - has no accessible address, e.g. a plain number value
           (stored only temporarlily)

  universal reference
         - the type of the function parameter is rvalue
           reference to type template parameter


  move semantics: makes it possible for compilers to replace expensive
  copying operations with less expensive moves. In the same way that
  copy constructors and copy assignment operators give you control
  over what it means to copy objects, move constructors and move
  assignment operators offer control over the semantics of
  moving. Move semantics also enables the creation of move-only types,
  such as 'std::unique_ptr', 'std::future' and 'std::thread'.

  perfect forwarding: makes it possible to write function templates
  that take arbitrary arguments and forward them to other functions
  such that the target funcitons receive exactly the same arguments as
  were passed to the forwarding functions



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

  Names of rvalue reference variables are lvalues and have to be
  converted to xvalues to be bound to the function overloads that
  accept rvalue reference parameters, which is why move constructors
  and move assignment operators typically use std::move
  One exception is when the type of the function parameter is rvalue
  reference to type template parameter ("forwarding reference" or
  "universal reference"), in which case std::forward is used instead.



  CONCLUSION

  - 'std::move' performs an unconditional cast to an rvalue. In and of itself,
  it doesn't move anything

  - 'std::forward' casts its argument to an rvalue only if that argument is
  bound to an rvalue

  - neither 'std::move' nor 'std::forward' do anything at runtime

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template < typename T >
typename remove_reference< T >::type &&my_move11(T &&param)
{
  using ReturnType = typename remove_reference< T >::type &&;
  return static_cast< ReturnType >(param);
}

template < typename T >
decltype(auto) my_move14(T &&param)
{
  using ReturnType = remove_reference_t< T > &&;
  return static_cast< ReturnType >(param);
}


int main(void)
{
  string str = "first", another_str = "second", yet_another_str = "third";
  vector< string > vec;


  // copy, still leaves original existent
  cout << "copy:" << endl;
  cout << "vec.push_back( str )" << endl;
  vec.push_back(str);
  cout << "after, str = '" << str << "' [" << &str << "]" << endl;
  cout << endl;

  cout << "content of " << endl
       << "vec[0]: '" << vec[0] << "' [" << &vec[0] << "]" << endl;
  cout << endl;


  // move, passes ownership and existence via cast (nothing at runtime),
  // original does not exist anymore (undefined)
  cout << "move:" << endl;
  cout << "vec.push_back( std::move( str ) )" << endl;
  vec.push_back(std::move(str));
  cout << "after, str = '" << str << "' [moved, original should be empty]"
       << endl;
  cout << endl;

  cout << "content of " << endl
       << "vec[0]: '" << vec[0] << "' [" << &vec[0] << "]," << endl
       << "vec[1]: '" << vec[1] << "' [" << &vec[1] << "]" << endl;
  cout << endl;


  // C++11 version
  cout << "move - just a remove_reference cast (C++11):" << endl;
  cout << "vec.push_back( std::my_move11( str ) )" << endl;
  vec.push_back(my_move11(another_str));
  cout << "after, another_str = '" << another_str
       << "' [moved, original should be empty]" << endl;
  cout << endl;

  cout << "content of " << endl
       << "vec[0]: '" << vec[0] << "' [" << &vec[0] << "]," << endl
       << "vec[1]: '" << vec[1] << "' [" << &vec[1] << "]," << endl
       << "vec[2]: '" << vec[2] << "' [" << &vec[2] << "]" << endl;
  cout << endl;


  // C++14 version
  cout << "move - just a remove_reference cast (C++14):" << endl;
  cout << "vec.push_back( std::my_move14( str ) )" << endl;
  vec.push_back(my_move14(yet_another_str));
  cout << "after, yet_another_str = '" << yet_another_str
       << "' [moved, original should be empty]" << endl;
  cout << endl;

  cout << "content of " << endl
       << "vec[0]: '" << vec[0] << "' [" << &vec[0] << "]," << endl
       << "vec[1]: '" << vec[1] << "' [" << &vec[1] << "]," << endl
       << "vec[2]: '" << vec[2] << "' [" << &vec[2] << "]," << endl
       << "vec[3]: '" << vec[3] << "' [" << &vec[3] << "]" << endl;
  cout << endl;


  cout << "READY." << endl;
}
