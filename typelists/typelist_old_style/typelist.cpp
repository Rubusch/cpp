// typelist.cpp
/*
  "Everything related to Typelist, except the definition 
  of Typelist itself, lives in the TL namespace."

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>
#include <typeinfo>

#include "conversion.hpp"


/*
  The typelist itself
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
  Linearizing Typelist Creation

  The "old fashion" implementation uses macros
//*/
#define TYPELIST_1(T1) Typelist_< T1, NullType >
#define TYPELIST_2(T1, T2) Typelist_< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist_< T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist_< T1, TYPELIST_3(T2, T3, T4) >
// can be extended here...



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
  template< class TList > 
  struct Length;
 
  template<> struct Length< NullType >
  {
    enum { value = 0 };
  };

  template< class T, class U > 
  struct Length< Typelist_< T, U > >
  {
    enum { value = 1 + Length< U >::value };
  };


  /*
    Indexed Access
    
    The declaration of a template for an indexed operation would look like this:
      template< class TList, unsigned int index > struct TypeAt;

    Algorithm:
    IF TList is non-null and i is zero, then Result is the head of TList
    ELSE
      IF TList is non-null and index i is nonzero, then Result is obtained by applying
        TypeAt to the tail of TList and i-1
      ELSE there is an out-of-bound access that translates into a compile-time error

    Usage:
    TL::TypeAt< MyTypelist, idx >::Result variable;
  //*/

  // basic template form
  template< class TList, unsigned int index > 
  struct TypeAt;

  // head
  template< class Head, class Tail > 
  struct TypeAt< Typelist_< Head, Tail >, 0 >
  {
    typedef Head 
      Result;
  };

  // any element
  template< class Head, class Tail, unsigned int i >
  struct TypeAt< Typelist_< Head, Tail >, i>
  {
    typedef typename TypeAt< Tail, i-1 >::Result 
      Result;
  };


  /*
    Searching Typelists

    Algorithm:
    IF TList is NullType, then value is -1
    ELSE
      IF the head of TList is T, then value is 0
      ELSE
        Compute the result of IndexOf applied to TList's tail and T into a temporary value temp
        IF temp is -1, then value is -1
        ELSE value is 1 plus temp

    Usage:
    int idx = IndexOf< MyTypelist, TypeToLookUp >::value;
  //*/
  template< class TList, class T > 
  struct IndexOf;

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
    enum { value = temp == -1 ? -1 : 1 + temp };
  };


  /*
    Appending to Typelists

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

    Usage:     
    typedef TL::Append< MyTypelist, NewType >::Result MyNewTypelist;
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
    //*/
      typedef TYPELIST_1(T) 
        Result;
  };

  template< class Head, class Tail >
  struct Append< NullType, Typelist_< Head, Tail > > 
  {
    typedef Typelist_< Head, Tail > 
      Result;
  };

  template< class Head, class Tail, class T >
  struct Append< Typelist_< Head, Tail >, T >
  {
    typedef Typelist_< Head, typename Append< Tail, T >::Result > 
      Result;
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
  struct Erase< Typelist_< T, Tail >, T >
  {
    typedef Tail 
      Result;
  };

  // Specialization 3
  template< class Head, class Tail, class T >
  struct Erase< Typelist_< Head, Tail > , T >
  {
    typedef Typelist_< Head, typename Erase< Tail, T >::Result >
      Result;
  };

  
  /*
    Erase All
    Returns a typelist that is MyTypelist without any occurence of T

    Usage:
    typedef TL::EraseAll< MyTypelist, LastType >::Result MyNewTypelist;
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
  struct EraseAll< Typelist_< T, Tail >, T >
  {
    // Go all the way down the list removing the type
    typedef typename EraseAll< Tail, T >::Result 
      Result;
  };

  template< class Head, class Tail, class T >
  struct EraseAll< Typelist_< Head, Tail >, T >
  {
    // Go all the way down the list removing the type
    typedef Typelist_< Head, typename EraseAll< Tail, T >::Result >
      Result;
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
  template< class TList > 
  struct NoDuplicates;
  
  template<>
  struct NoDuplicates< NullType >
  {
    typedef NullType 
      Result;
  };

  template< class Head, class Tail >
  struct NoDuplicates< Typelist_< Head, Tail > >
  {
  private:
    typedef typename NoDuplicates< Tail >::Result 
      L1;

    typedef typename EraseAll< L1, Head >::Result 
      L2;

  public:
    typedef Typelist_< Head, L2 > 
      Result;
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
    typedef TL::Replace< MyTypelist, TypeToRemove, TypeToReplace >::Result MyReplacedTypelist;
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
  struct Replace< Typelist_< T, Tail >, T, U >
  {
    typedef Typelist_< U, Tail > 
      Result;
  };

  template< class Head, class Tail, class T, class U >
  struct Replace< Typelist_< Head, Tail >, T, U >
  {
    typedef Typelist_< Head, typename Replace< Tail, T, U >::Result> 
      Result;
  };
};


/*
  main..
//*/
int main()
{
  using namespace std;


  // init a TYPELIST_3 - old style: avoid MACROs!
  cout << "init a typelist\n";
  typedef TYPELIST_3(unsigned char, unsigned short int, unsigned int) 
    MyTypelist_t;
  cout << endl;


  // calculating length
  cout << "calculating length\n";
  int iLength = TL::Length< MyTypelist_t >::value;
  cout << "length of the typelist: " << iLength << endl;
  cout << endl;


  // indexed access
  cout << "indexed access\n";
  cout << "e.g. define a variable of the second type in the list...";
  TL::TypeAt< MyTypelist_t, 2 >::Result variable = 0;
  cout << "done.\n";
  cout << "type is \"unsigned int\": " 
       << ((typeid(variable) == typeid(unsigned int)) ? "true" : "false") 
       << endl;
  cout << endl;


  // search typelist
  cout << "search typelist\n";
  cout << "index of the type \"unsigned char\": ";
  int idxUChar = TL::IndexOf< MyTypelist_t, unsigned char >::value;
  cout << idxUChar << endl;
  cout << endl;

  cout << "now check the type \"unsigned long int\" (not in the list)\n";
  int idxNotInList = TL::IndexOf< MyTypelist_t, unsigned long int >::value;
  cout << "the index was: " << idxNotInList << endl;
  cout << endl;


  // append to typelist
  cout << "append to typelist\n";
  cout << "append new type \"unsigned long int\"...";
  typedef TL::Append< MyTypelist_t, unsigned long int >::Result MyNewTypelist_t;
  cout << "done.\n";
  cout << "index of \"unsigned long int\" is now: " 
       << TL::IndexOf< MyNewTypelist_t, unsigned long int >::value
       << endl;
  cout << endl;

  
  // erase a type 
  cout << "erase a type\n";
  cout << "delete \"unsigned char\" from list\n";
  cout << "length before\t: " << TL::Length< MyNewTypelist_t >::value << endl;
  cout << "erase a type of the typelist...";
  typedef TL::Erase< MyNewTypelist_t, unsigned char >::Result MyNewSmallerTypelist_t;  
  cout << "done.\n";
  cout << "length after\t: " << TL::Length< MyNewSmallerTypelist_t >::value << endl;
  cout << endl;


  // erase all of one type
  cout << "erase all of one type (we take the 2. type in the list).\n";
  cout << "length before\t: " << TL::Length< MyNewTypelist_t >::value << endl;
  cout << "get the type at index 2...";
  typedef TL::TypeAt< MyNewTypelist_t, 2 >::Result 
    ExclusiveType_t;
  cout << "done.\n";
  cout << "now erase the sublist until the type of index 2...";
  typedef TL::EraseAll< MyNewTypelist_t, ExclusiveType_t >::Result 
    MyReducedTypelist_t; 
  cout << "done.\n";
  cout << "length after\t: " << TL::Length< MyReducedTypelist_t >::value << endl;
  cout << endl;


  // replace elements
  cout << "replace elements\n";
  cout << "second element is \"unsigned int\"?\t: " 
       << ((typeid(unsigned int) == typeid(TL::TypeAt< MyTypelist_t, 2 >::Result)) ? "true" : "false") 
       << endl;
  cout << "replacing elmenet \"unsigned int\" with \"unsigned char\"...";
  typedef TL::Replace< MyTypelist_t, unsigned int, unsigned char >::Result MyReplacedTypelist_t;  
  cout << "done.\n";
  cout << "now second element is \"unsigned char\"?\t: " 
       << ((typeid(unsigned char) == typeid(TL::TypeAt< MyReplacedTypelist_t, 2 >::Result)) ? "true" : "false") 
       << endl;  
  cout << endl;


  // erase duplicates 
  cout << "erase duplicates\n";
  cout << "length before: " << TL::Length< MyReplacedTypelist_t >::value
       << endl;
  cout << "do no duplicates...";
  typedef TL::NoDuplicates< MyReplacedTypelist_t >::Result 
    MyTypelistWithoutDuplicates_t;
  cout << "done.\n";
  cout << "length after: " << TL::Length< MyTypelistWithoutDuplicates_t >::value
       << endl;

  cout << endl;


  cout << "READY.\n";
  return 0;
}
