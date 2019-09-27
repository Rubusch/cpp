// typelist.cpp
/*
  "Everything related to Typelist, except the definition
  of Typelist itself, lives in the TL namespace."

  resources: Modern C++ Design, Alexandrescu

  TODO: get type2type trick running to avoid duplicate types
//*/


#include <iostream>

#include "conversion.hpp"


/*
  The typelist itself
//*/
template< class T, class U >
struct Typelist
{
  typedef T
    Head;

  typedef U
    Tail;
};


/*
  Linearizing Typelist Creation

  The "old fashion" implementation uses macros
  TODO: replace by "new style"
//*/
#define TYPELIST_1(T1) Typelist< T1, NullType >
#define TYPELIST_2(T1, T2) Typelist< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist< T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist< T1, TYPELIST_3(T2, T3, T4) >
  // can be extended here...
//*/


/*
  Typelist algorithms live in the TL namespace
//*/
namespace TL
{
  /*
    Calculating Length
    TODO apply!

    Using Length you can write things like:
      std::type_info* intsRtti[Length< SignedIntegrals >::value];
  //*/
  template< class TList >
  struct Length;

  template<> struct Length< NullType >
  {
    enum { value = 0 };
  };

  template< class T, class U >
  struct Length< Typelist< T, U > >
  {
    enum { value = 1 + Length< U >::value };
  };


  /*
    Indexed Access
    TODO apply!

    The declaration of a template for an indexed operation would look like this:
      template< class TList, unsigned int index > struct TypeAt;

    Algorithm:
    IF TList is non-null and i is zero, then Result is the head of TList
    ELSE
      IF TList is non-null and index i is nonzero, then Result is obtained by applying
        TypeAt to the tail of TList and i-1
      ELSE there is an out-of-bound access that translates into a compile-time error
  //*/

  // basic template form
  template< class TList, unsigned int index >
  struct TypeAt;

  // head
  template< class Head, class Tail >
  struct TypeAt< Typelist< Head, Tail >, 0 >
  {
    typedef Head
      Result;
  };

  // any element
  template< class Head, class Tail, unsigned int i >
  struct TypeAt< Typelist< Head, Tail >, i>
  {
    typedef typename TypeAt< Tail, i-1 >::Result
      Result;
  };


  /*
    Searching Typelists
    TODO apply!

    Algorithm:
    IF TList is NullType, then value is -1
    ELSE
      IF the head of TList is T, then value is 0
      ELSE
        Compute the result of IndexOf applied to TList's tail and T into a temporary value temp
        IF temp is -1, then value is -1
        ELSE value is 1 plus temp

    Usage:
    template< class TList, class T > struct IndexOf;
  //*/
  template< class TList, class T >
  struct IndexOf;

  template< class T >
  struct IndexOf< NullType, T >
  {
    enum { value = -1 };
  };

  template< class T, class Tail >
  struct IndexOf< Typelist< T, Tail >, T >
  {
    enum { value = 0 };
  };

  template< class Head, class Tail, class T >
  struct IndexOf< Typelist< Head, Tail >, T >
  {
  private:
    enum { temp = IndexOf< Tail, T >::value };

  public:
    enum { value = temp == -1 ? -1 : 1 + temp };
  };


  /*
    Appending to Typelists
    TODO apply!

    Algorithm:
    IF TList is NullType and T is NullType, then Result is NullType
    ELSE
      IF TList is NullType and T is a single (nontypelist) type,
        then Result is a typelist having T as its only element
      ELSE
        IF TList is NullType and T is a typelist, Result is T itself
        ELSE IF TList is non-null, then Result is a typelist having
          TList::Head as its head and the result of appending T to
          TList::Tail as its tail
  //*/
  template< class TList, class T >
  struct Append;

  template<>
  struct Append< NullType, NullType >
  {
    typedef NullType
      Result;
  };

  template< class T >
  struct Append< NullType, T >
  {
    /*
      old fashion delcaration - unsave due to macro usage
      TODO: replace by new style list
    //*/
      typedef TYPELIST_1(T)
        Result;
  };

  template< class Head, class Tail >
  struct Append< NullType, Typelist< Head, Tail > >
  {
    typedef Typelist< Head, Tail >
      Result;
  };

  template< class Head, class Tail, class T >
  struct Append< Typelist< Head, Tail >, T >
  {
    typedef Typelist< Head, typename Append< Tail, T >::Result >
      Result;
  };


  /*
    Erasing a Type from a Typelist
    TODO apply!

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      IF T is the same as TList::Head, then Result is TList::Tail
      ELSE Result is a typelist having TList::Head as its head
        and the result of applying Erase to TList::Tail and T as its tail

    Usage:
    typedef Erase< SignedTypes, float >::Result SomeSignedTypes;
  //*/
  template< class TList, class T >
  struct Erase;

  // Specialization 1
  template< class T >
  struct Erase< NullType, T >
  {
    typedef NullType
      Result;
  };

  // Specialization 2
  template< class T, class Tail >
  struct Erase< Typelist< T, Tail >, T >
  {
    typedef Tail
      Result;
  };

  // Specialization 3
  template< class Head, class Tail, class T >
  struct Erase< Typelist< Head, Tail > , T >
  {
    typedef Typelist< Head, typename Erase< Tail, T >::Result >
      Result;
  };


  /*
    Erase All
    TODO apply!
  //*/
  template< class TList, class T >
  struct EraseAll;

  template< class T >
  struct EraseAll< NullType, T >
  {
    typedef NullType
      Result;
  };

  template< class T, class Tail >
  struct EraseAll< Typelist< T, Tail >, T >
  {
    // Go all the way down the list removing the type
    typedef typename EraseAll< Tail, T >::Result
      Result;
  };

  template< class Head, class Tail, class T >
  struct EraseAll< Typelist< Head, Tail >, T >
  {
    // Go all the way down the list removing the type
    typedef Typelist< Head, typename EraseAll< Tail, T >::Result >
      Result;
  };


  /*
    Erasing Duplicates
    TODO apply!

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      Apply NoDuplicates to TList::Tail, obtaining a temporary typelist L1
      Apply Erase to L1 and TList:Head. Obtain L2 as the result
      Result is a typelist whose head is TList::Head and whose tail is L2
  //*/
  template< class TList >
  struct NoDuplicates;

  template<>
  struct NoDuplicates< NullType >
  {
    typedef NullType
      Result;
  };

  template< class Head, class Tail >
  struct NoDuplicates< Typelist< Head, Tail > >
  {
  private:
    typedef typename NoDuplicates< Tail >::Result
      L1;

    typedef typename Erase< L1, Head >::Result
      L2;

  public:
    typedef Typelist< Head, L2 >
      Result;
  };


  /*
    Replacing an Element in Typelist
    TODO apply!

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      IF the head of the typelist TList is T, then Result is a typelist
        with U as its head and TList::Tail as its tail
      ELSE Result is a typelist with TList::Head as its head and the
        result of applying Replace to TList, T, and U as its tail.
  //*/
  template< class TList, class T, class U >
  struct Replace;

  template< class T, class U >
  struct Replace< NullType, T, U >
  {
    typedef NullType
      Result;
  };

  template< class T, class Tail, class U >
  struct Replace< Typelist< T, Tail >, T, U >
  {
    typedef Typelist< U, Tail >
      Result;
  };

  template< class Head, class Tail, class T, class U >
  struct Replace< Typelist< Head, Tail >, T, U >
  {
    typedef Typelist< Head, typename Replace< Tail, T, U >::Result>
      Result;
  };


  /*
    Partially Ordering Typelists - algorithm 2:
    TODO applly!

    The MostDerived algorithm accepts a typelist and a type Base and returns
    the most derived type from Base in the typelist (or possibly Base itself,
    if no derived type is found). It looks like this:

    Algorithm II:
    IF TList is NullType, the result is T
    ELSE
      APPLY MostDerived to TList::Tail and T. Obtain Candidate.
      IF TList::Head is derived from Candidate, the result is TList::Head.
      ELSE, the result is Candidate.

  template< class TList, class T >
  struct MostDerived;
  //*/
  template< class TList, class T >
  struct MostDerived;

  template< class T >
  struct MostDerived< NullType, T >
  {
    typedef T
      Result;
  };

  template< class Head, class Tail, class T >
  struct MostDerived< Typelist< Head, Tail >, T >
  {
  private:
    typedef typename MostDerived< Tail, T >::Result
      Candidate;

  public:
    typedef typename Select< SUPERSUBCLASS(Candidate, Head), Head, Candidate>::Result
      Result;
  };


  /*
    Partially Ordering Typelists - algorithm 1
    TODO applly!

    Algorithm I:
    IF TList is NullType, then Result is NullType
    ELSE
      FIND the most derived type from TList::Head in TList::Tail. Save
        that type via a typedef to a type called TheMostDerived.
      REPLACE TheMostDerived in TList::Tail with TList::Head, obtaining
        L as the result
      BUILD the as a typelist having TheMostDerived as its head and
        DerivedToFront< L >::Result as its tail

    When this algorithm is applied to a typelist, derived types will
    migrate to the top of the typelist, and base types will be pushed
    to the bottom.
  //*/
  template< class TList >
  struct DerivedToFront;

  template<>
  struct DerivedToFront< NullType >
  {
    typedef NullType
      Result;
  };

  template< class Head, class Tail >
  struct DerivedToFront< Typelist< Head, Tail > >
  {
  private:
    typedef typename MostDerived< Tail, Head >::Result
      TheMostDerived;

    typedef typename Replace< Tail, TheMostDerived, Head >::Result
      L;

  public:
    typedef Typelist< TheMostDerived, L >
      Result;
  };
}


/*
  application: the scattered hierarchy

  TODO: diagram


                              +----------------+
                              | Holder< char > |
                              +----------------+
                                     /_\
                                      |
                                      |
  +---------------+  +-------------------------------------+  +-----------------------------------------+
  | Holder< int > |  | GenScatterHierarchy< char, Holder > |  | GenScatterHierarchy< NullType, Holder > |
  +---------------+  +-------------------------------------+  +-----------------------------------------+
    /_\                              /_\                                        /_\
     |                                |                                          |
     |                                +-----------------------------+------------+
     |           +------------------+                               |
     |           | Holder< string > |                               |
     |           +------------------+                               |
     |                   /_\                                        |
     |                    |                                         |
     |                    |                                         |
     |  +---------------------------------------+  +---------------------------------------------------+
     |  | GenScatterHierarchy< string, Holder > |  | GenScatterHierarchy< TYPELIST_1( char ), Holder > |
     |  +---------------------------------------+  +---------------------------------------------------+
     |                   /_\                                        /_\
     |                    |                                          |
     |                    +----------------------------------+-------+
     |                                                       |
  +------------------------------------+    +-----------------------------------------------------------+
  | GenScatterHierarchy< int, Holder > |    | GenScatterHierarchy< TYPELIST_2( string, char ), Holder > |
  +------------------------------------+    +-----------------------------------------------------------+
                 /_\                                                /_\
                  |                                                  |
                  +----------------------+---------------------------+
                                         |
                                 +----------------+
                                 | SomeInfoType_t |
                                 +----------------+

//*/

template< class TList, template< class > class Unit >
class GenScatterHierarchy;

// GenScatterHierarchy specialization: Typelist to Unit
template< class Head, class Tail, template< class > class Unit >
class GenScatterHierarchy< Typelist< Head, Tail >, Unit >
  : public GenScatterHierarchy< Head, Unit >
    , public GenScatterHierarchy< Tail, Unit >
{
public:
  typedef typename Typelist< Head, Tail >
    TList;

  typedef typename GenScatterHierarchy< Head, Unit >
    LeftBase;

  typedef typename GenScatterHierarchy< Tail, Unit >
    RightBase;
};

// Pass an atomic type (non-typelist) to Unit
template< class AtomicType, template< class > class Unit >
class GenScatterHierarchy : public Unit< AtomicType >
{
  typedef typename Unit< AtomicType >
    LeftBase;
// virtual ~GenScatterHierarchy(){} // TODO      
};

// Do nothing for NullType
template< template< class > class Unit >
class GenScatterHierarchy< NullType, Unit >
{};

/*
  Ultimately, an instantiation of GenScatterHierarchy ends up
  inheriting Unit instantiated with "every type in the typelist".

  For instance: the Holder
//*/
template< class T >
struct Holder
{
  T value_;
};

// the type definition
typedef GenScatterHierarchy< TYPELIST_3( int, std::string, char ), Holder >
  SomeInfoType_t;


/*
  main..
//*/
int main()
{
  using namespace std;

  // init a TYPELIST_4
  /*
    old fashion init - deprecated due to macro usage!
    TODO: replace by new style list

  typedef TYPELIST_4(unsigned char, unsigned short int, unsigned int, unsigned long int)
    UnsignedInts_t;
  //*/

  // TODO

  // calculate length
  // TODO

  // indexed access
  // TODO

  // search typelist
  // TODO

  // append to typelist
  // TODO

  // erase a type
  // TODO - var1
  // TODO - var2
  // TODO - var3

  // erase all
  // TODO

  // init again a TYPELIST_4 with duplicates, that works for ordering
  // TODO: replace by new style
  /*
  typedef TYPELIST_3(signed char, signed short int, signed long int)
    SignedInts_t;
  //*/

  // erase duplicates
  // TODO

  // replace elements
  // TODO - algo 1
  // TODO - algo 2

  // partially ordering
  // TODO

  cout << "READY.\n";
  return 0;
}
