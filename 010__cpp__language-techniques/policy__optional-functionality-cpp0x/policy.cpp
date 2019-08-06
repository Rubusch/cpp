// optionalpolicy.cpp
/*
  It gets even better. C++ contributes to the power of policies by providing an
  interesting feature. If a member function of a class template is never used,
  it is not even instantiated - the compiler does not look at it at all, except
  perhaps for syntax checking.

  The policies must stand in front of the UserClass in this case. It is not
  possible to replace them here using forward declarations.

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>
#include <cstdlib>


/******************************************************************************/


/*
  alloc policy

  uses "new" to allocate
//*/
template< typename T >
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
template< typename T >
class MallocPolicy
{
protected:
  static T* create()
  {
    std::cout << "\t\tMallocPolicy::create()\n";

    static T* t = NULL;

    // if the allocation of *buf fails, return NULL...
    if(NULL == (t = static_cast< T* >( std::malloc( sizeof(T*) )))){
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


/******************************************************************************/


/*
  User Class
//*/
template< typename U >
class UserClass
 : public NewPolicy< U >
{
private:
  using NewPolicy< U >::create;
  using NewPolicy< U >::destroy;

public:
  void doSomething()
  {
    std::cout << "\tUserClass::doSomething()\n";


    std::cout << "\t         ::doSomething() - create some variable\n";
    U* u = create();
    std::cout << "\t         ::doSomething() - ok.\n"
              << std::endl;


    std::cout << "\t         ::doSomething() - init the variable\n";
    *u = 123;
    std::cout << "\t         ::doSomething() - " << *u << ".\n"
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


/*
  Remark:
  This can be implemented using "std::string", but remember that "std::string"
  is "const char*", which makes "std::string* equal to "const char**" as also
  "T*", this means using malloc, we might have to allocate char* AND char**. Or
  we get a signal 11 / SIGSEGV!!!

  To avoid hasseling with this issues and getting even more cryptic code, here
  only a simple example using "char" instead of "std::string" ;)

  Hence this example demonstrates the usage of a different template type for the
  policy than for the "user" class, too.
//*/
template<>
class UserClass< std::string >
  : public MallocPolicy< char >
{
private:
  using MallocPolicy< char >::create;
  using MallocPolicy< char >::destroy;

public:
  void doSomething()
  {
    std::cout << "\tUserClass::doSomething()\n";


    std::cout << "\t         ::doSomething() - create some variable\n";
    char* u = create();
    std::cout << "\t         ::doSomething() - ok.\n"
              << std::endl;


    std::cout << "\t         ::doSomething() - init the variable\n";
    *u = 'x';
    std::cout << "\t         ::doSomething() - \'" << *u << "\'.\n"
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


/******************************************************************************/


/*
  ..main
//*/
int main()
{
  using namespace std;

  cout << "Allocation Policies\n";

  /*
    create with 'int' and 'NewPolicy'
  //*/
  cout << "UserClass< int >\n";

  typedef UserClass< int >
    IntNewUser_t;

  IntNewUser_t intNewUser;

  intNewUser.doSomething();
  cout << endl;


  /*
    create with 'std::string' and 'MallocPolicy'

    internally we will still use 'char' and NOT a 'const char*' as
    'std::string' might be!
  //*/
  cout << "UserClass< std::string >\n";
  typedef UserClass< std::string >
    StringMallocUser_t;

  StringMallocUser_t stringMallocUser;

  stringMallocUser.doSomething();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
