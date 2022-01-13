// Templatenotes
/*
  Definition of Template classes and what-happens-here explanation:
  notes on templates in C++

  "class" and "struct" can be used equally, only differences:
  - "struct" by default "public" - "class" by default "private"
  - in template declarations no "struct" is possible
  - "struct" and "class" can be used interchangeably at class declarations
//*/


/********************************************************************************/


/*
  "typename" or "class"

  "typename" and "class" can be used interchangeably in simple template type
  declarations.
//*/
template < typename T >
class Foobar
{
};

Foobar< int > fb;

// ...is the same as...
template < class T >
class Foobar
{
};

Foobar< int > fb;


/*
  type declaration using "typename"

  "typname" in type declaration is not interchangeable with "class"
  Note: some earlier compilers don't support "typename"
//*/
template < typename T >
class Foobar
{
  void foo()
  {
    /*
      Without "typename" this can be a multiplication (x as variable) or
      a pointer definition (x as type).

      Therefore "typename" is necessary when used as type declaration.
    //*/
    typename T::x *ptr;
  }
};


/*
  type declaration in template statement

  here "typename" is not replaceable with "class"
//*/
template < class T, typename T::member >
class Foobar
{
};


/********************************************************************************/


/*
  non-type parameters

  constant non-type template parameters
//*/
template < int >
class Foobar
{
};

Foobar< 77 > fb;


/********************************************************************************/


/*
  pass of a template to a template
//*/
template < template < typename T > class Foo >
class Bar
{
  Foo< int > f;
};

Bar< std::string > b;


/********************************************************************************/


/*
  default template parameters
//*/
template < typename T = char, unsigned int N = 7 >
class Foobar
{
};

// instance that uses "int" and passes the direct value 123
Foobar< int, 123 > fb;

// instance that uses "char" and 7 as template types by default
Foobar<> fb;


/********************************************************************************/


/*
  policy

  Compile-time realizatoin of the strategy pattern
//*/
template < typename PolicyClass >
class Foobar : public PolicyClass
{
};

typedef Foobar< MyPolicy > Foobar_t;
Foobar_t fb;


/********************************************************************************/


/*
  class template specialization

  if another template type e.g. "typename U" would be contained in all
specializations, it would be a partial case of template specialization

  the default parameter is at least at g++ necessary
//*/
template < typename T = int >
class Foobar
{
private:
  T item;

public:
  void func();
};

// specialization
template <>
class Foobar< int >
{
private:
  int item;

public:
  void anotherFunc();
};

Foobar< int > myIntFoo;
Foobar< char > myCharFoo;


/********************************************************************************/


/*
  Templates in multiple file projects

  Source:
  http://www.c-plusplus.de/forum/viewtopic-var-t-is-39467.html


  The standard contains the keyword "export" which would enable to use templates
spread over various files. Nevertheless, so far no compiler supports export for
the usage of templates.

  The idea would be something like the following:
//*/

// in file foobar.h
export template < typename T >
class Foobar
{
public:
  void Func();
};


// in file foobar.cpp
#include "foobar.h"
template < typename T >
void Foobar< T >::Func()
{
}

/*
  While this still isn't possible yet, templates are written into the .h and
.hpp file, respectively. In case for these files the extensions .ipp, .inl or
.tpp are used.

  Find more information:
    Herb Sutter: "Export" Restrictions, Part 1
    Herb Sutter: "Export" Restrictions, Part 2
    Why We Can’t Afford Export
//*/
