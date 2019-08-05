// conversion.hpp
/*
  Taken from the loki, formerly "TypeManip.h"

  The typemapper's are missing.
//*/

#ifndef CONVERSION_TOOLS
#define CONVERSION_TOOLS


/*
  NullType definition
//*/
class NullType
{};


/*
  select
//*/
template< bool flag, typename T, typename U >
struct Select
{
  typedef T Result;
};

template< typename T, typename U >
struct Select< false, T, U >
{
  typedef U Result;
};


/*
  conversion

  checks the conversion relationship of two types
  - conversion exists
  - exists roundtrip (2 ways)
  - is the same type

  caveat: might not work if T and U are in a private inheritance hierarchy
//*/
namespace Private
{
  template< class T, class U >
  struct ConversionHelper
  {
    typedef char Small;
    struct Big { char dummy[2]; };
    static Big Test(...);
    static Small Test(U);
    static T MakeT();
  };
}

// common definition
template< class T, class U >
struct Conversion
{
  typedef Private::ConversionHelper< T, U > H;

  // macro for Metrowerks CodeWarrior tool on windows
#ifndef __MWERKS__
  enum { exists = sizeof(typename H::Small) == sizeof(H::Test(H::MakeT())) };
#else
  enum { exists = false; };
#endif
  enum { exists2Way = exists && Conversion< U, T >::exists };
  enum { sameType = false };
};

// partial template specification
template< class T >
struct Conversion< T, T >
{
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};

template< class T >
struct Conversion< void, T >
{
  enum { exists = 1, exists2Way = 0, sameType = 0 };
};

template< class T >
struct Conversion< T, void >
{
  enum { exists = 1, exists2Way = 0, sameType = 0 };
};

template<>
class Conversion< void, void >
{
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};

// macro definition - avoid macros!
#define SUPERSUBCLASS(T,U) \
( Conversion< const U*, const T* >::exists && \
!Conversion< const T*, const void* >::sameType )

#endif

