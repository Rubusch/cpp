// parametertraits.cpp
/*
  "Traits are a generic programming technique that allows compile-time 
  decisions to be made based on types, much as you would make runtime 
  decisions based on values.

  This makes the resulting code cleaner, more readable, and easier to 
  maintain."

  "Let's call the parameter type that we look for ParameterType.

  IF T is a reference to some type, ParameterType is the same as T (unchanged). 
    Reason: References to references are not allowed."
  ELSE
    IF T is a scalar type (int, float, etc), ParameterType is T. 
      Reason: Fundamental types are best passed by value
    ELSE ParameterType is const T&. 
      Reason: In general, non-fundamental types are best passed by reference"

  "Unfortunately, this scheme fails to pass enumerated types (enums) by value."

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>


/*
  Null Type
//*/
class NullType
{};


/*
  Select
  
  Selects one of two types based upon a boolean constant

  T and U are types: Result evaluates to T if flag is true, 
  and to U otherwise
//*/
template< bool flag, typename T, typename U >
struct Select
{
  typedef T 
    Result;
};

template< typename T, typename U >
struct Select< false, T, U > 
{
  typedef U 
    Result;
};


/*
  Typelist - Typelist
//*/
template< class H, class T >
struct Typelist_
{
  typedef H
    Head;

  typedef T
    Tail;
};


/*
  Typelist - linearizaton
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
  typedef Typelist_< T1, Typelist_< T2, Typelist_< T3, NullType > > > 
    type_t;
};


/*
  Typelist - algorithms
//*/
namespace TL
{
  /*
    Typelist - IndexOf
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
  struct IndexOf< Typelist_< Head, Tail>, T >
  {
  private:
    enum { temp = IndexOf< Tail, T >::value };
    
  public:
    enum { value = (temp == -1 ? -1 : 1 + temp) };
  };
}


/*
  Some typelists
//*/
namespace Private
{
  typedef Typelist< unsigned char, unsigned short int, unsigned int, unsigned long int >::type_t
    UnsignedInts_t;

  typedef Typelist< signed char, short int, int, long int >::type_t
    SignedInts_t;
  
  typedef Typelist< bool, char >::type_t
    OtherInts_t;

  typedef Typelist< float, double >::type_t
    Floats_t;
}


/*
  Type Traits 
//*/
template<typename T>
class TypeTraits
{
private:
  // Reference Traits
  template< class U > struct ReferenceTraits
  {
    enum { result = false };
    typedef U
      ReferredType;
  };

  template< class U > struct ReferenceTraits< U& >
  {
    enum { result = true };
    typedef U 
      ReferredType;
  };

  // Pointer Traits
  template<class U> struct PointerTraits
  {
    enum { result = false };
    typedef NullType 
      PointeeType;
  };
  
  template<class U> struct PointerTraits<U*>
  {
    enum { result = true };
    typedef U 
      PointeeType;
  };

  // Pointer 2 Member Traits
  template< class U >
  struct Ptr2MemTraits
  {
    enum { result = false };
  };

  template< class U, class V >
  struct Ptr2MemTraits< U V::* >
  {
    enum { result = true };
  };
    
public:   
  // basic types
  enum { isStdUnsignedInt = (0 <= TL::IndexOf< Private::UnsignedInts_t, T >::value) };
  enum { isStdSignedInt = (0 <= TL::IndexOf< Private::SignedInts_t, T>::value) };
  enum { isStdFloat = (0 <= TL::IndexOf< Private::Floats_t, T >::value) }; 

  // type evaluations
  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || (0 <= TL::IndexOf< Private::OtherInts_t, T >::value) };

  // evaluation groups
  enum { isStdArith = isStdIntegral || isStdFloat };

  // public evaluations in loki
  enum { isPointer = PointerTraits< T >::result }; 
  enum { isPointer2Member = Ptr2MemTraits< T >::result }; 
  
  // referred type evaluation
  enum { isReference = ReferenceTraits< T >::result };
  typedef typename ReferenceTraits< T >::ReferredType
    ReferredType_t;

  // finally parameter type evaluation:
  // returns the optimal type to be used as a parameter for functions that take T's
  typedef typename Select< isStdArith || isPointer || isPointer2Member, T, ReferredType_t& >::Result 
    ParameterType;
};


/*
  some stupid dummy class
//*/
class DummyClass
{};


/*
  main
//*/
int main()
{
  using namespace std;

  cout << "init..\n";

  // some type
  typedef int 
    Parameter1_t;

  // check optimized type
  typedef TypeTraits< Parameter1_t >::ParameterType 
    Result1_t;

  // output
  cout << "Parameter1_t was \"int\", an optimized function should pass:\t\t \"int\""
       << (TypeTraits< Result1_t >::isPointer  ? " Pointer" : "")
       << (TypeTraits< Result1_t >::isReference ? " Reference" : " Object")
       << endl;


  // next type
  typedef DummyClass
    Parameter2_t;

  // check optimized type
  typedef TypeTraits< Parameter2_t >::ParameterType
    Result2_t;

  // output
  cout << "Paramenter2_t was \"DummyClass\", an optimized function should pass:\t \"DummyClass\""
       << (TypeTraits< Result2_t >::isPointer  ? " Pointer" : "")
       << (TypeTraits< Result2_t >::isReference ? " Reference" : " Object")
       << endl;


  cout << "READY.\n";
  return 0;
}
