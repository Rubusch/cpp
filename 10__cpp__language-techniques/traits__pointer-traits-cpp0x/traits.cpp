// pointertraits.cpp
/*
  "Traits are a generic programming technique that allows compile-time
  decisions to be made based on types, much as you would make runtime
  decisions based on values.

  This makes the resulting code cleaner, more readable, and easier to
  maintain."

  e.g: copy function
  "You would like, then, to implement copy so as to take advantage of
  fancyFastCopyFunction() whenever possible, and fall back on a more
  general conservative algorithm for elaborate types."

  "TypeTraits uses template specialization internally and exposes the
  results.

  For example, the following code determines whether a type T is a
  pointer."

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>
#include <vector>


/*
  Null Type
//*/
class NullType
{};


/*
  Typelist Stuff
//*/
template< class T, class U >
struct Typelist_
{
  typedef T
    Head;

  typedef U
    Tail;
};


/*
  Typelist - linearization
//*/
template< class T1, class T2 = NullType, class T3 = NullType, class T4 = NullType >
struct Typelist
{
  typedef Typelist_< T1, Typelist_< T2, Typelist_< T3, Typelist_< T4, NullType > > > >
    type_t;
};

template< class T1 >
struct Typelist< T1, NullType, NullType, NullType >
{
  typedef Typelist_< T1, NullType >
    type_t;
};

template< class T1, class T2 >
struct Typelist< T1, T2, NullType, NullType >
{
  typedef Typelist_< T1, Typelist_< T2, NullType > >
    type_t;
};

template< class T1, class T2, class T3 >
struct Typelist< T1, T2, T3, NullType >
{
  typedef Typelist_< T1, Typelist< T2, Typelist_< T3, NullType > > >
    type_t;
};


/*
  Typelist - algorithms
//*/
namespace TL
{
  /*
    TypeList structure - IndexOf
  //*/
  template< class TList, class T > struct IndexOf;

  template< class T >
  struct IndexOf< NullType, T >
  {
    enum { value = -1 };
  };

  template< class T, class Tail >
  struct IndexOf< Typelist_< T, Tail >, T >
  {
    enum { value = 0 };
  };

  template< class Head, class Tail, class T >
  struct IndexOf< Typelist_< Head, Tail >, T >
  {
  private:
    enum { temp = IndexOf< Tail, T >::value };

  public:
    enum { value = (temp == -1 ? -1 : 1 + temp) };
  };
}


/*
  Some predefinitions for the Type Traits
//*/
namespace Private
{
  typedef Typelist< unsigned char, unsigned short int, unsigned int, unsigned long int >::type_t
    StdUnsignedInts_t;

  typedef Typelist< signed char, short int, int, long int >::type_t
    StdSignedInts_t;

  typedef Typelist< bool, char >::type_t
    StdOtherInts_t;

  typedef Typelist< float, double >::type_t
    StdFloats_t;
}


/*
  Type Trait
//*/
template< typename T >
class TypeTraits
{
private:
  // pointer traits
  template< class U > struct PointerTraits
  {
    enum { result = false };
    typedef NullType PointeeType;
  };

  template< class U > struct PointerTraits< U* >
  {
    enum { result = true };
    typedef U PointeeType;
  };

public:
  // check if the passed type is a pointer type?
  enum { isPointer = PointerTraits< T >::result };

  // define enums to check types trait-like
  enum { isStdUnsignedInt = TL::IndexOf< Private::StdUnsignedInts_t, T >::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf< Private::StdOtherInts_t, T >::value >= 0 };
  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< Private::StdOtherInts_t, T >::value >= 0 };
  enum { isStdFloat = TL::IndexOf< Private::StdFloats_t, T >::value >= 0 };

  // arithmetic type is either an integral type or a floating point type
  enum { isStdArith = isStdIntegral || isStdFloat };
};


/*
  main

  "You can now gain some insight into the std::vector::iterator
  implementation - is it a plain pointer or an elaborate type?"
//*/
int main()
{
  using namespace std;

  // some example,
  cout << "checking an iterator for beeing a plain pointer or not by traits:\n";
  const bool iterIsPtr = TypeTraits< vector< int >::iterator >::isPointer;
  cout << "vector<int>::iterator is " << (iterIsPtr ? "\"fast\"" : "\"smart\"") << '\n';

  cout << "READY.\n";
  return 0;
}
