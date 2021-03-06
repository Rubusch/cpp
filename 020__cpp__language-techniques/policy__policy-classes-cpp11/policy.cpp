// policyclasses.cpp
/*
  Policies and policy classes help in implementing safe, efficient, and highly
  customizable design elements. A policy defines a class interface or a class
  template interface. The interface consists of one or all of the following:
  inner type definitions, member functions, and member variables.

  This example is writen using "class" instead of "struct", the only differences
  between "struct" and "class" in C++ are:
  - class is by default "private", struct is by default "public"
  - only the word "class" can be used in template declarations similarly to
    typename. Furthermore a declaration of a "class" is allowed to be done using
    the keyword "struct" and vice versa.

  resources: Modern C++ Design, Alexandrescu


  A policy consists in:

  - User Classes
    Template classes that are derived (public or private!) from policy classes,
        the type of the policy is passed as template type, e.g.:

      template< typename allocPolicy_t >
      class UserClass : public allocPolicy_t
      {
      ...

  - The used function of the Policy Class should be declared via using directive
    in the User Class

  - Policy Classes
    Due to the applied inheritance everything can be implemented in protected or
        even private mode.

  - The usage consists in defining the type out of the User Class using the
    right Policy Classes and getting an instance of that to work withh
      typedef UserClass< int, NewPolicy< int > >
        IntNewUser_t;

      IntNewUser_t intNewUser;

      intNewUser.doSomething();
 */


#include <cstdlib>
#include <iostream>


/*
  the user class implements something as the Template Method Pattern via
  templates, alternatively an pImpl pointer to a corresponding implementation
  may be passed

  to the outside only one access method (alternatively ctor or operator()
  overloaded) is available, here doSomething(), the internal implementation
  comes from a separate implementor, pImpl or here 'policy' as a template
 */
template < typename U, typename allocPolicy_t >
class UserClass : public allocPolicy_t
{
private:
  using allocPolicy_t::create;
  using allocPolicy_t::destroy;

public:
  void doSomething()
  {
    std::cout << "\tUserClass::doSomething()\n";

    std::cout << "\t         ::doSomething() - create some variable\n";
    auto u_obj = create(); // 'U*' is returned
    std::cout << "\t         ::doSomething() - ok.\n" << std::endl;


    std::cout << "\t         ::doSomething() - now destroy\n";
    destroy(&u_obj);
    std::cout << "\t         ::doSomething() - ok.\n" << std::endl;
  }


  ~UserClass() { std::cout << "\tUserClass::~UserClass() - dtor\n"; }
};


/***************************************************************************************/


/*
  alloc policy

  uses "new" to allocate - allocator, can also be implemented as static
singleton

  policy: is passed as template argument!
//*/
template < class T >
class NewPolicy
{
protected:
  static T *create()
  {
    std::cout << "\t\tNewPolicy::create()\n";
    return new T;
  }


  void destroy(T **t)
  {
    std::cout << "\t\tNewPolicy::destroy( T** t)\n";
    delete *t;
    *t = nullptr;
  }


  virtual ~NewPolicy() { std::cout << "\t\tNewPolicy::~NewPolicy() - dtor\n"; }
};


/*
  alloc policy

  uses malloc()

  policy: is passed as template argument!
//*/
template < class T >
class MallocPolicy
{
protected:
  static T *create()
  {
    std::cout << "\t\tMallocPolicy::create()\n";

    T *t = nullptr;

    // if the allocation of *buf fails, return NULL...
    if (nullptr == (t = static_cast< T * >(std::malloc(sizeof(T))))) {
      std::cerr << "\t\t            ::create() - allocation failed"
                << std::endl;
      t = nullptr;
    }

    // ...else return it
    return t;
  }


  void destroy(T **t)
  {
    std::cout << "\t\tMallocPolicy::destroy( T** t)" << std::endl;
    free(*t);
    *t = nullptr;
  }


  virtual ~MallocPolicy()
  {
    std::cout << "\t\tMallocPolicy::~MallocPolicy() - dtor" << std::endl;
  }
};


/***************************************************************************************/


/*
  ..main
//*/
int main()
{
  using namespace std;

  cout << "Allocation Policies" << endl;

  /*
    create with new
  //*/
  cout << "UserClass< int, NewPolicy< int > >" << endl;
  using IntNewUser_t = UserClass< int, NewPolicy< int > >;
  IntNewUser_t intNewUser;
  intNewUser.doSomething();
  cout << endl;


  /*
    create with malloc
  //*/
  cout << "UserClass< int, MallocPolicy< int > >" << endl;
  using IntMallocUser_t = UserClass< int, MallocPolicy< int > >;
  IntMallocUser_t intMallocUser;
  intMallocUser.doSomething();
  cout << endl;


  cout << "READY." << endl;
  return 0;
}
