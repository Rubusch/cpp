// fundamentaltraits.cpp
/*
  "Traits are a generic programming technique that allows compile-time
  decisions to be made based on types, much as you would make runtime
  decisions based on values.

  This makes the resulting code cleaner, more readable, and easier to
  maintain."

  resources: Modern C++ Design, Alexandrescu

  Implementation of type traits for fundamental types, like int,
  double, char, etc..
//*/


#include <iostream>


/*
  Null Type
//*/
class NullType
{
};


/*
  Typelist - the Typelist
//*/
template < class T, class U >
struct Typelist_ {
  typedef T Head;

  typedef U Tail;
};


/*
  Typelist - linearization
//*/
template < class T1, class T2 = NullType, class T3 = NullType,
           class T4 = NullType >
struct Typelist {
  typedef Typelist_<
      T1, Typelist_< T2, Typelist_< T3, Typelist_< T4, NullType > > > >
      type_t;
};

template < class T1 >
struct Typelist< T1, NullType, NullType, NullType > {
  typedef Typelist_< T1, NullType > type_t;
};

template < class T1, class T2 >
struct Typelist< T1, T2, NullType, NullType > {
  typedef Typelist_< T1, Typelist_< T2, NullType > > type_t;
};

template < class T1, class T2, class T3 >
struct Typelist< T1, T2, T3, NullType > {
  typedef Typelist_< T1, Typelist_< T2, Typelist_< T3, NullType > > > type_t;
};


/*
  Typelist - algorithms
//*/
namespace TL
{
  /*
    Typelist - IndexOf
  //*/
  template < class TList, class T >
  struct IndexOf;

  template < class T >
  struct IndexOf< NullType, T > {
    enum { value = -1 };
  };

  template < class T, class Tail >
  struct IndexOf< Typelist_< T, Tail >, T > {
    enum { value = 0 };
  };

  template < class Head, class Tail, class T >
  struct IndexOf< Typelist_< Head, Tail >, T > {
  private:
    enum { temp = IndexOf< Tail, T >::value };

  public:
    enum { value = (temp == -1 ? -1 : 1 + temp) };
  };
} // namespace TL


/*
  Conversion - Conversion Helper

  Helper types Small and Big - guarantee that sizeof(Small) < sizeof(Big)
//*/
namespace Private
{
  template < class T, class U >
  struct ConversionHelper {
    typedef char Small;
    struct Big {
      char dummy[2];
    };
    static Big Test(...);
    static Small Test(U);
    static T MakeT();
  };
} // namespace Private


/*
  Conversion - Conversion

  Figures out the conversion relationships between
  two type Invocations (T and U are types):

  a) Conversion< T, U >::exists
  returns (at compile time) true if there is an implicit
  conversion from T to U (e.g. Derived to Base)

  b) Conversion< T, U >::exists2Way
  returns (at compile time) true if there are both conversions
  from T to U and from U to T (e.g. int to char and back)

  c) Conversion< T, U >::sameType
  returns (at compile time) true if T and U represent the
  same type

  Caveat: might not work if T and U are in a private inheritance
  hierarchy
//*/
template < class T, class U >
struct Conversion {
  typedef Private::ConversionHelper< T, U > Helper;
#ifndef __MWERKS__
  enum {
    exists =
        sizeof(typename Helper::Small) == sizeof(Helper::Test(Helper::MakeT()))
  };
#else
  enum { exists = false };
#endif
  enum { exists2Way = exists && Conversion< U, T >::exists };
  enum { sameType = false };
};

template < class T >
struct Conversion< T, T > {
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};

template < class T >
struct Conversion< void, T > {
  enum { exists = 1, exists2Way = 0, sameType = 0 };
};

template < class T >
struct Conversion< T, void > {
  enum { exists = 1, exists2Way = 0, sameType = 0 };
};

template <>
class Conversion< void, void >
{
public:
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};


/*
  Type Traits - the Type Traits
//*/
template < typename T >
class TypeTraits
{
private:
  /*
    private block - same as pointer traits to a member
  //*/
  template < class U >
  struct PointerTraits {
    enum { result = false };
    typedef NullType PointeeType;
  };

  template < class U >
  struct PointerTraits< U * > {
    enum { result = true };
    typedef U PointeeType;
  };

public:
  // typelists
  typedef Typelist< unsigned char, unsigned short int, unsigned int,
                    unsigned long int >::type_t UnsignedInts_t;

  typedef Typelist< signed char, short int, int, long int >::type_t
      SignedInts_t;

  typedef Typelist< bool, char >::type_t OtherInts_t;

  typedef Typelist< float, double >::type_t Floats_t;

  // type evaluations
  enum { isStdUnsignedInt = TL::IndexOf< UnsignedInts_t, T >::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf< SignedInts_t, T >::value >= 0 };
  enum {
    isStdIntegral = isStdUnsignedInt || isStdSignedInt ||
                    TL::IndexOf< OtherInts_t, T >::value >= 0
  };
  enum { isStdFloat = TL::IndexOf< Floats_t, T >::value >= 0 };

  // evaluation groups
  enum { isStdArith = isStdIntegral || isStdFloat };
  enum { isStdFundamental = isStdArith || Conversion< T, void >::sameType };
};


/*
  Dummy class - for testing
//*/
class DummyClass
{
};


/*
  main
//*/
int main()
{
  using namespace std;

  typedef DummyClass type1_t;

  cout << "type1_t (DummyClass) is an integral type?\t ";
  bool isIntegralType = TypeTraits< type1_t >::isStdIntegral;
  cout << (isIntegralType ? "\"true\"" : "\"false\"") << " (false)" << endl;
  cout << endl;

  cout << "type1_t (DummyClass) is a fundamental type?\t ";
  bool isFundamentalType = TypeTraits< type1_t >::isStdFundamental;
  cout << (isFundamentalType ? "\"true\"" : "\"false\"") << " (false)" << endl;
  cout << endl;

  typedef int type2_t;

  cout << "type2_t (int) is an integral type?\t ";
  isIntegralType = TypeTraits< type2_t >::isStdIntegral;
  cout << (isIntegralType ? "\"true\"" : "\"false\"") << " (true)" << endl;
  cout << endl;

  cout << "type2_t (int) is a fundamental type?\t ";
  isFundamentalType = TypeTraits< type2_t >::isStdFundamental;
  cout << (isFundamentalType ? "\"true\"" : "\"false\"") << " (true)" << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
