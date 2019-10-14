// noduplicates.cpp
/*
  demonstrates the implementation of NoDuplicates in a typelist
//*/


#include <iostream>
#include <typeinfo>


/*
  The null type
//*/
class NullType
{
};


/*
  The typelist itself
//*/
template < class T, class U >
struct Typelist_ {
  typedef T Head;

  typedef U Tail;
};


/*
  Linearizing Typelist Creation

  ...a better alternative would use templates
//*/

// declaration for 4 elements
template < class T1, class T2 = NullType, class T3 = NullType,
           class T4 = NullType >
struct Typelist {
  typedef Typelist_<
      T1, Typelist_< T2, Typelist_< T3, Typelist_< T4, NullType > > > >
      type_t;
};

// definitions..
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
  Typelist algorithms live in the TL namespace
//*/
namespace TL
{
  /*
    Calculating Length

    Using Length you can write things like:
      std::type_info* intsRtti[Length< SignedIntegrals >::value];

    Usage:
    int iLength = TL::Length< MyTypelist >::value;
  //*/
  template < class TList >
  struct Length;

  template <>
  struct Length< NullType > {
    enum { value = 0 };
  };

  template < class T, class U >
  struct Length< Typelist_< T, U > > {
    enum { value = 1 + Length< U >::value };
  };


  /*
    Indexed Access

    The declaration of a template for an indexed operation would look like this:
      template< class TList, unsigned int index > struct TypeAt;

    Algorithm:
    IF TList is non-null and i is zero, then Result is the head of TList
    ELSE
      IF TList is non-null and index i is nonzero, then Result is obtained by
  applying TypeAt to the tail of TList and i-1 ELSE there is an out-of-bound
  access that translates into a compile-time error

    Usage:
    TL::TypeAt< MyTypelist, idx >::Result variable;
  //*/

  // basic template form
  template < class TList, unsigned int index >
  struct TypeAt;

  // head
  template < class Head, class Tail >
  struct TypeAt< Typelist_< Head, Tail >, 0 > {
    typedef Head Result;
  };

  // any element
  template < class Head, class Tail, unsigned int i >
  struct TypeAt< Typelist_< Head, Tail >, i > {
    typedef typename TypeAt< Tail, i - 1 >::Result Result;
  };


  /*
    Erasing a Type from a Typelist

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      IF T is the same as TList::Head, then Result is TList::Tail
      ELSE Result is a typelist having TList::Head as its head
        and the result of applying Erase to TList::Tail and T as its tail

    Usage:
    typedef Erase< MyTypelist, TypeToErase >::Result MyNewTypelist;
  //*/
  template < class TList, class T >
  struct Erase;

  template < class T >
  struct Erase< NullType, T > {
    typedef NullType Result;
  };

  template < class T, class Tail >
  struct Erase< Typelist_< T, Tail >, T > {
    typedef Tail Result;
  };

  template < class Head, class Tail, class T >
  struct Erase< Typelist_< Head, Tail >, T > {
    typedef Typelist_< Head, typename Erase< Tail, T >::Result > Result;
  };


  /*
    No Duplicates

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      Apply NoDuplicates to TList::Tail, obtaining a temporary typelist L1
      Apply Erase to L1 and TList:Head. Obtain L2 as the result
      Result is a typelist whose head is TList::Head and whose tail is L2

    Usage:
    typedef TL::NoDuplicates< MyTypelist >::Result MyTypelistWithoutDuplicates;
  //*/
  template < class TList >
  struct NoDuplicates;

  template <>
  struct NoDuplicates< NullType > {
    typedef NullType Result;
  };

  template < class Head, class Tail >
  struct NoDuplicates< Typelist_< Head, Tail > > {
  private:
    typedef typename NoDuplicates< Tail >::Result L1;

    typedef typename Erase< L1, Head >::Result L2;

  public:
    typedef Typelist_< Head, L2 > Result;
  };


  /*
    Replacing an Element in Typelist

    Algorithm:
    IF TList is NullType, then Result is NullType
    ELSE
      IF the head of the typelist TList is T, then Result is a typelist
        with U as its head and TList::Tail as its tail
      ELSE Result is a typelist with TList::Head as its head and the
        result of applying Replace to TList, T, and U as its tail.

    Usage:
    typedef TL::Replace< MyTypelist, TypeToRemove, TypeToReplace >::Result
  MyReplacedTypelist;
  //*/
  template < class TList, class T, class U >
  struct Replace;

  template < class T, class U >
  struct Replace< NullType, T, U > {
    typedef NullType Result;
  };

  template < class T, class Tail, class U >
  struct Replace< Typelist_< T, Tail >, T, U > {
    typedef Typelist_< U, Tail > Result;
  };

  template < class Head, class Tail, class T, class U >
  struct Replace< Typelist_< Head, Tail >, T, U > {
    typedef Typelist_< Head, typename Replace< Tail, T, U >::Result > Result;
  };
} // namespace TL


/*
  main..
//*/
int main()
{
  using namespace std;


  // init a TYPELIST_3 - old style: avoid MACROs!
  cout << "init a typelist...";
  typedef Typelist< unsigned char, unsigned short int, unsigned int >::type_t
      MyTypelist_t;
  cout << "done.\n";
  cout << "length\t\t: " << TL::Length< MyTypelist_t >::value << endl;
  cout << endl;


  // replace elements
  cout << "REPLACE ELEMENTS\n";
  cout << "second element is \"unsigned int\"?\t: "
       << ((typeid(unsigned int) ==
            typeid(TL::TypeAt< MyTypelist_t, 2 >::Result))
               ? "true"
               : "false")
       << endl;
  cout << "replacing elmenet \"unsigned int\" with \"unsigned char\"...";
  typedef TL::Replace< MyTypelist_t, unsigned int, unsigned char >::Result
      MyReplacedTypelist_t;
  cout << "done.\n";
  cout << "now second element is \"unsigned char\"?\t: "
       << ((typeid(unsigned char) ==
            typeid(TL::TypeAt< MyReplacedTypelist_t, 2 >::Result))
               ? "true"
               : "false")
       << endl;
  cout << endl;


  // erase duplicates
  cout << "ERASE DUPLICATES\n";
  cout << "length before\t: " << TL::Length< MyReplacedTypelist_t >::value
       << endl;
  cout << "do NoDuplicates...";
  typedef TL::NoDuplicates< MyReplacedTypelist_t >::Result
      MyTypelistWithoutDuplicates_t;
  cout << "done.\n";
  cout << "length after\t: "
       << TL::Length< MyTypelistWithoutDuplicates_t >::value << endl;


  cout << "READY.\n";
  return 0;
}
