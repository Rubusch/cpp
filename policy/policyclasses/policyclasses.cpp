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

  Taken from "Modern C++ Design", Alexandrescu


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


#include <iostream>
#include <cstdlib>


template< typename U, typename allocPolicy_t >
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
    U* u = create();
    std::cout << "\t         ::doSomething() - ok.\n"
              << std::endl;


    std::cout << "\t         ::doSomething() - now destroy\n";
    destroy( &u);
    std::cout << "\t         ::doSomething() - ok.\n"
              << std::endl;

  }


  ~UserClass()
  {
    std::cout << "\tUserClass::~UserClass() - dtor\n";
  }
};


/***************************************************************************************/


/*
  alloc policy

  uses "new" to allocate
//*/
template< class T >
class NewPolicy
{
protected:
  static T* create()
  {
    std::cout << "\t\tNewPolicy::create()\n";

    return new T;
  }


  void destroy( T** t)
  {
    std::cout << "\t\tNewPolicy::destroy( T** t)\n";

    delete *t; *t = NULL;
  }


  ~NewPolicy()
  {
    std::cout << "\t\tNewPolicy::~NewPolicy() - dtor\n";
  }
};


/*
  alloc policy

  uses malloc()
//*/
template< class T >
class MallocPolicy
{
protected:
  static T* create()
  {
    std::cout << "\t\tMallocPolicy::create()\n";

    T* t = NULL;

    // if the allocation of *buf fails, return NULL...
    if(NULL == (t = static_cast< T* >( std::malloc( sizeof(T) )))){
      std::cerr << "\t\t            ::create() - allocation failed\n";
      t = NULL;
    }

    // ...else return it
    return t;
  }


  void destroy( T** t)
  {
    std::cout << "\t\tMallocPolicy::destroy( T** t)\n";

    free(*t); *t = NULL;
  }


  ~MallocPolicy()
  {
    std::cout << "\t\tMallocPolicy::~MallocPolicy() - dtor\n";
  }
};


/***************************************************************************************/


/*
  ..main
//*/
int main()
{
  using namespace std;

  cout << "Allocation Policies\n";

  /*
    create with new
  //*/
  cout << "UserClass< int, NewPolicy< int > >\n";
  typedef UserClass< int, NewPolicy< int > > IntNewUser_t;

  IntNewUser_t intNewUser;

  intNewUser.doSomething();
  cout << endl;


  /*
    create with malloc
  //*/
  cout << "UserClass< int, MallocPolicy< int > >\n";
  typedef UserClass< int, MallocPolicy< int > > IntMallocUser_t;

  IntMallocUser_t intMallocUser;

  intMallocUser.doSomething();
  cout << endl;


  cout << "READY.\n";
  return 0;
}

