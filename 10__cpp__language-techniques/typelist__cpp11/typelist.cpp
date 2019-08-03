// typelist.cpp
/*
  "Everything related to typelist, except the definition of typelist itself,
  lives in the TL namespace."

  the linearization works like the following:
  1. definition of a typelist with the full amount of template arguments and
  setting Default template arguments

  2. usage of the typelist with less than the full amount of template arguments
  uses the default template arguments instead (see 1.)

  3. defining template specialization classes for cases using the default
  template arguments (3. is template specialization)

  taken from "Modern C++ Design", Alexandrescu

  cpp11: reworked for cpp11 & cpp14
  resources: https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp

//*/


#include <iostream>
#include <typeinfo>
#include <type_traits> /* integral_constant */

#include "conversion.hpp"


namespace TL
{


  /*
    The typelist itself

    cpp11: before a typelist needed always to contain at least one element,
    this made an empty element necessary

    in cpp11 also an empty Typelist is possible


    usage:
    using MyList = Typelist< Type1, Type2, Type3 >;
  //*/
  template< typename ...Ts >
  struct Typelist
  {
    using type = Typelist;

    // cpp11: number of elements is 'sizeof...(Ts)'
    static constexpr size_t size() noexcept { return sizeof...(Ts); }
  };

  using Typelist_empty = Typelist<>;


  // is list empty? member definition: type, value_type and value
  template< class List >
  struct isEmpty
  {
    using type = std::false_type; // integral_constant< bool, false >;
    using value_type = typename type::value_type;
    static constexpr value_type value = type::value;
  };

  // empty list
  template<>
  struct isEmpty< Typelist<> >
  {
    using type = std::true_type; // integral_constant< bool, true >;
    using value_type = type::value_type;
    static constexpr value_type value = type::value;
  };


  /*
    type at index

    cpp11: TypeAt

    usage:
      using type_at_4 = TypeAt<4, MyList>::type;
  // */
  template< size_t idx, class List >
  struct TypeAt_impl;

  template< typename T, typename... Ts >
  struct TypeAt_impl< 0, Typelist< T, Ts... > > // end of search, type was found
  {
    using type = T;
  };

  template< size_t idx, typename T, typename... Ts >
  struct TypeAt_impl< idx, Typelist< T, Ts... > > // recursion
  {
    using type = typename TypeAt_impl< idx - 1, Typelist< Ts... > >::type;
  };

  // wrapper
  template< size_t idx, class List >
  struct TypeAt;

  template< size_t idx, typename... Ts >
  struct TypeAt< idx, Typelist< Ts... > >
  {
    private:
      static_assert(sizeof...(Ts) > idx, "TypeAt: index out of bounds or called on empty type");
    public:
      using type = typename TypeAt_impl< idx, Typelist< Ts... > >::type;
  };
  // */


  /*
    indexed access


    cpp11: version of IndexOf

    usage:
      constexpr static auto idx = IndexOf< Type, MyList>::value;
  // */
  template< size_t idx, typename T, class List >
  struct IndexOf_impl; // has index as template parameter

  template< size_t idx, typename T > // type T not in list
  struct IndexOf_impl< idx, T, Typelist<> >
  {
    using type = std::integral_constant< int, -1 >;
  };

  template< size_t idx, typename T, typename... Ts >
  struct IndexOf_impl< idx, T, Typelist< T, Ts... > > // type is found
  {
    using type = std::integral_constant< int, idx >;
  };

  template< size_t idx, typename T, typename H, typename... Ts >
  struct IndexOf_impl< idx, T, Typelist< H, Ts... > > // recursion
  {
    using type = typename IndexOf_impl< idx + 1, T, Typelist< Ts... > >::type;
  };

  // support of Head for index 0
  template< typename T, class List >
  struct IndexOf;

  template< typename T, typename... Ts >
  struct IndexOf< T, Typelist< Ts... > >
  {
    using type = typename IndexOf_impl< 0, T, Typelist< Ts... > >::type;
    using value_type = typename type::value_type;
    static constexpr value_type value = type::value;
  };
  // */


  /*
    Appending to Typelists


    cpp11: PushBack/PushFront

    Usage:
      using MyList = typename PushBack< Type, MyList >::type;
    or
      using MyList = typename PushFront< Type, MyList >::type;
  // */
  template< typename T, class List >
  struct PushFront;

  template< typename T, typename... Ts >
  struct PushFront< T, Typelist< Ts... > >
  {
    using type = Typelist< T, Ts... >;
  };

  template< typename T, class List >
  struct PushBack;

  template< typename T, typename... Ts >
  struct PushBack< T, Typelist< Ts... > >
  {
    using type = Typelist< Ts..., T >;
  };
  // */


  /*
    Erasing a Type from a Typelist

    cpp11: TODO

    usage:
      using MyList = typename Erase< Type, MyList >::type;
  // */
  template< typename T, class List >
  struct Erase;

  template< typename T >
  struct Erase< T, Typelist<> >
  {
    using type = Typelist<>;
  };

  template< typename T, typename... Ts >
  struct Erase< T, Typelist< T, Ts...> >
  {
    using type = Typelist< Ts... >;
  };

  template< typename T, typename H, typename... Ts >
  struct Erase< T, Typelist< H, Ts... > >
  {
    using type = typename PushFront< H, typename Erase< T, Typelist< Ts... > >::type >::type;
  };
  // */


  /*
    Erase All

    Returns a typelist that is MyTypelist without any occurence of T

    cpp11: TODO

    Usage:
    using MyList = EraseAll< MyList >
  //*/
  template< typename T, class List >
  struct EraseAll;

  template< typename T >
  struct EraseAll< T, Typelist<> >
  {
    using type = Typelist<>;
  };

  template< typename T, typename... Ts >
  struct EraseAll< T, Typelist< T, Ts... > >
  {
    using type = typename EraseAll< T, Typelist< Ts... > >::type;
  };

  template< typename T, typename H, typename... Ts >
  struct EraseAll< T, Typelist< H, Ts... > >
  {
    using type = typename PushFront< H, typename EraseAll< T, Typelist< Ts... > >::type >::type;
  };
  // */


  /*
    Erase Duplicates

    cpp11: TODO

    usage:
      using MyList = EraseDuplicates< MyList >;
  // */
  template< class List >
  struct EraseDuplicates;

  template<>
  struct EraseDuplicates< Typelist<> >
  {
    using type = Typelist<>;
  };

  template< typename H, typename... Ts >
  struct EraseDuplicates< Typelist< H, Ts... > >
  {
  private:
    using unique_t = typename EraseDuplicates< Typelist< Ts... > >::type;
    using new_t = typename Erase< H, unique_t >::type;
  public:
    using type = typename PushFront< H , new_t >::type;
  };


  /*
    Replacing an Element in Typelist

    cpp11: TODO

    Usage:
    TODO
  //*/
  template< typename R, typename T, class List >
  struct ReplaceAll;

  template< typename R, typename T >
  struct ReplaceAll< R, T, Typelist<> >
  {
    using type = Typelist<>;
  };

  template< typename R, typename T, typename... Ts >
  struct ReplaceAll< R, T, Typelist< T, Ts... > >
  {
    using type = typename PushFront< R, typename ReplaceAll< R, T, Typelist< Ts... > >::type >::type;
  };

  template< typename R, typename T, typename H, typename... Ts >
  struct ReplaceAll< R, T, Typelist< H, Ts... > >
  {
    using type = typename PushFront< H, typename ReplaceAll< H, T, Typelist< Ts... > >::type >::type;
  };
  // */
};



/*
  main..
//*/
int main()
{
  using namespace std;


  // init a TYPELIST_3 - old style: avoid MACROs!
  cout << "init a typelist\n";
  using MyTypelist_t = TL::Typelist< unsigned char, unsigned short int, unsigned int >;
  cout << endl;


  // calculating length
  cout << "calculating length\n";
  constexpr static auto iLength = MyTypelist_t::size();
  cout << iLength << endl;
  cout << endl;



  cout << "now check the type \"unsigned long int\" (not in the list)\n";
  static constexpr auto idxNotInList = TL::IndexOf< unsigned long int, MyTypelist_t >::value;
  cout << "the index was: " << idxNotInList << endl;
  cout << endl;


  // append to typelist
  cout << "append to typelist\n";
  cout << "append new type \"unsigned long int\"...";
  using MyNewTypelist_t = typename TL::PushBack< unsigned long int, MyTypelist_t >::type;
  cout << "done.\n";
  cout << "index of \"unsigned long int\" is now: "
       << TL::IndexOf< unsigned long int, MyNewTypelist_t >::value
       << endl;
  cout << endl;


  // erase a type
  cout << "erase a type\n";
  cout << "delete \"unsigned char\" from list\n";
  cout << "length before\t: " << MyNewTypelist_t::size() << endl;
  cout << "erase a type of the typelist...";
  using MyNewSmallerTypelist_t = typename TL::Erase< unsigned char, MyNewTypelist_t >::type;
  cout << "done.\n";
  cout << "length after\t: " << MyNewSmallerTypelist_t::size() << endl;
  cout << endl;

/*
  // erase all of one type
  cout << "erase all of one type (we take the 2. type in the list).\n";
  cout << "length before\t: " << TL::Length< MyNewTypelist_t >::value << endl;   
  cout << "get the type at index 2...";
  typedef TL::TypeAt< MyNewTypelist_t, 2 >::Result ExclusiveType_t;    
  cout << "done.\n";
  cout << "now erase the sublist until the type of index 2...";
  typedef TL::EraseAll< MyNewTypelist_t, ExclusiveType_t >::Result MyReducedTypelist_t;     
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
  typedef TL::NoDuplicates< MyReplacedTypelist_t >::Result MyTypelistWithoutDuplicates_t;   
  cout << "done.\n";
  cout << "length after: " << TL::Length< MyTypelistWithoutDuplicates_t >::value   
       << endl;

  // */

  cout << endl;
  cout << "READY.\n";
  return 0;
}
