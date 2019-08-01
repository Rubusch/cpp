// functor.hpp
/*
  Loki's implementation doesn't work with the "modern access" of typelist avoiding
  macros (described in an article of Alexandrescu). I didn't work on it either, thus
  the macros ;)

  (in parts taken from Alexandrescu's loki, 2001)
//*/


#ifndef FUNCTOR_H
#define FUNCTOR_H


#include <type_traits> /* integral_constant */
#include <memory>


/*************************** Dummy types *************************************/

/*
  Null Type
//*/
class NIL{};


/*
  Empty Type
//*/
struct EmptyType{};


/*************************** Select ******************************************/


/*
  select
//*/
// TODO                  
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


/*************************** Typelists ***************************************/


/*
  typelist, maximum 2 different types..
#define TYPELIST_1(T1) Typelist_< T1, NIL > // TODO rm
#define TYPELIST_2(T1, T2) Typelist_< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist_< T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist_< T1, TYPELIST_3(T2, T3, T4) >


  Linearizing Typelist Creation

  The "old fashion" implementation uses macros - this functor implementation
  doesn't take the "newer" linearization which would avoid macros.

template< typename T, typename U >
struct Typelist_
{
  typedef T Head;
  typedef U Tail;
};
// */


/* cpp11 upgrade
resource:
https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp

// cpp11: using instead of typedef
// cpp11: 'typename ...Ts' declaration of variadic template, 'Ts...' declaration of Tail Type
template< typename T, typename ...Ts>
struct Typelist
{
  using Head = T;
  using Tail = Typelist< Ts... >;
};

still, in cpp0x an empty element was needed, since the list could
not have been empty, thus Alexandrescu needed Head and Tail

cpp11: now NullType is still needed, but empty lists are possible
// */

/*
  cpp11: Typelist

  usage: TODO
//*/
template< typename ...Ts >
struct Typelist
{
  using type = Typelist;

  // cpp11: number of elements is 'sizeof...(Ts)'
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

using Typelist_empty = Typelist<>;




/*
  typelist operations
//*/
namespace TL
{
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
// */

/*
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


  /*
    Searching Typelists

    Algorithm:
    IF TList is NIL, then value is -1
    ELSE
      IF the head of TList is T, then value is 0
      ELSE
        Compute the result of IndexOf applied to TList's tail and T into a temporary value temp
        IF temp is -1, then value is -1
        ELSE value is 1 plus temp

    Usage:
    int idx = IndexOf< MyTypelist, TypeToLookUp >::value;

  template< class TList, class T >
  struct IndexOf;

  template< class T >
  struct IndexOf< NIL, T >
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
// */

/*
  cpp11: version of IndexOf

  usage: TODO ???
  using idx = IndexOf< Type, MyList>::type;                
// */
  template< size_t idx, typename T, class List >
  struct IndexOf_impl; // has index as template parameter

  template< size_t idx, typename T > // type T not in list
  struct IndexOf_impl< idx, T, Typelist<> >
  {
    using type = std::integral_constant<int, -1>;
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


  /*
    Erasing a Type from a Typelist

    Algorithm:
    IF TList is NIL, then Result is NIL
    ELSE
      IF T is the same as TList::Head, then Result is TList::Tail
      ELSE Result is a typelist having TList::Head as its head
        and the result of applying Erase to TList::Tail and T as its tail

    Usage:
    typedef Erase< MyTypelist, TypeToErase >::Result MyNewTypelist;

  template< class TList, class T >
  struct Erase;

  // Specialization 1
  template< class T >
  struct Erase< NIL, T >
  {
    typedef NIL
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
// */
}



  /*
    cpp11: push front/back

    usage:
    using MyList = PushFront< Type, MyList >::type;
    or
    using MyList = PushBack< Type, MyList >::type;
  // 
  template< typename T, class List >
  struct PushFront;

  template< typename T, typename... Ts >
  struct PushFront< T, Typelist< Ts... > >
  {
    using type = Typelist< T, Ts... >;
  };

  template< typename T, class List >
  struct PushBack;

  template< typename T, typename... Ts>
  struct PushBack< T, Typelist< Ts... > >
  {
    using type = Typelist< Ts..., T >;
  };
// */

  /*
    cpp11: erase

    usage:
    using MyList = Erase< Type, MyList >;

  template< typename T, class List>
  struct Erase;

  template< typename T >
  struct Erase< T, Typelist<> >
  {
    using type = Typelist<>;
  };

  template< typename T, typename... Ts >
  struct Erase< T, Typelist< T, Ts... > >
  {
    using type = Typelist< Ts... >;
  };

  template< typename T, typename H, typename... Ts >
  struct Erase< T, Typelist< H, Ts... > >
  {
    using type = typename PushFront< H, typename Erase< T, Typelist< Ts... > >::type>::type;
  };
// */


/*************************** Traits ******************************************/


/*
  Type Traits - the loki Type Traits, here we use:

  - parameter type
  returns the optimal type to be used as a parameter for functions that take Ts
//*/
template< typename T >
class TypeTraits
{
private:
  // private block - the traits itself
  template< typename U > struct PointerTraits
  {
//    enum { result = false };
    static constexpr auto result = false;
    typedef NIL PointeeType;
  };

  template< typename U > struct PointerTraits< U* >
  {
//    enum { result = true };
    static constexpr auto result = true;
    typedef U PointeeType;
  };

  template< typename U > struct ReferenceTraits
  {
//    enum { result = false };
    static constexpr auto result = false;
    typedef U ReferredType;
  };

  template< typename U > struct ReferenceTraits< U& >
  {
//    enum { result = true };
    static constexpr auto result = true;
    typedef U ReferredType;
  };

  template< typename U > struct PToMTraits
  {
//    enum { result = false };
    static constexpr auto result = false;
  };

  template< typename U, typename V > struct PToMTraits< U V::*>
  {
//    enum { result = true };
    static constexpr auto result = false;
  };

public:
//  typedef TYPELIST_4( unsigned char, unsigned short int, unsigned int, unsigned long int )    UnsignedInts_t;
//  typedef TYPELIST_4( signed char, short int, int, long int )    SignedInts_t;
//  typedef TYPELIST_2( bool, char )    OtherInts_t;
//  typedef TYPELIST_2( float, double )    Floats_t;

  using UnsignedInts_t = Typelist< unsigned char, unsigned short int, unsigned int, unsigned long int >;
  using SignedInts_t = Typelist< signed char, short int, int, long int >;
  using OtherInts_t = Typelist< bool, char >;
  using Floats_t = Typelist< float, double >;

  // isStdArith
//  enum { isStdUnsignedInt = TL::IndexOf< UnsignedInts_t, T >::value >= 0 };
//  enum { isStdUnsignedInt = TL::IndexOf< T, UnsignedInts_t >::value >= 0 };
  static constexpr auto isStdUnsignedInt = TL::IndexOf< T, UnsignedInts_t >::value >= 0;

//  enum { isStdSignedInt = TL::IndexOf< SignedInts_t, T >::value >= 0 };
//  enum { isStdSignedInt = TL::IndexOf< T, SignedInts_t >::value >= 0 };
  static constexpr auto isStdSignedInt = TL::IndexOf< T, SignedInts_t >::value >= 0;

//  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< OtherInts_t, T >::value >= 0 };
//  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< T, OtherInts_t >::value >= 0 };
  static constexpr auto isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< T, OtherInts_t >::value >= 0;

//  enum { isStdFloat = TL::IndexOf< Floats_t, T >::value >= 0 };
//  enum { isStdFloat = TL::IndexOf< T, Floats_t >::value >= 0 };
  static constexpr auto isStdFloat = TL::IndexOf< T, Floats_t >::value >= 0;

//  enum { isStdArith = isStdIntegral || isStdFloat };
  static constexpr auto isStdArith = isStdIntegral || isStdFloat;

  // isPointer
//  enum { isPointer = PointerTraits< T >::result };
  static constexpr auto isPointer = PointerTraits< T >::result;

  // isMemberPointer
//  enum { isMemberPointer = PToMTraits< T >::result };
  static constexpr auto isMemberPointer = PToMTraits< T >::result;

  // ReferredType
//  enum { isReference = ReferenceTraits< T >::result };
  static constexpr auto isReference = ReferenceTraits< T >::result;
  typedef typename ReferenceTraits< T >::ReferredType ReferredType;

  // -> ParameterType
  typedef typename Select< isStdArith || isPointer || isMemberPointer, T, ReferredType& >::Result ParameterType;
};


/*************************** Functor *****************************************/


/*
  Functor implementation base class (as struct)

  Base class for a hierarchy of functors. The FunctorImpl class is not used directly;
  rather, the Functor class manages and forwards to a pointer to FunctorImpl

  You may want to derive your own funcotrs from FunctorImpl. Specializations of
  FunctorImpl for up to 2 template parameter types.
//*/
namespace Private
{
  template< typename ResultType >
  struct FunctorImpl_Base
  {
    typedef ResultType ResultType_t;
    typedef EmptyType Arg1_t;
    typedef EmptyType Arg2_t;
  };
}


/*
  FunctorImpl

  The base class for a hierarchy of funcotrs. The FunctorImpl class is not used
  directly; rather, the Functor class manages and forwards to a pointer to
  FunctorImpl
//*/
template< typename ResultType, typename TList >
class FunctorImpl;


/*
  implementation, 0 args
//*/
template< typename ResultType >
class FunctorImpl< ResultType, NIL >
  : public Private::FunctorImpl_Base< ResultType >
{
public:
  typedef ResultType ResultType_t;

  virtual ResultType operator()() = 0;
};


/*
  implementation, 1 arg
//class FunctorImpl< ResultType, TYPELIST_1( Arg1 ) >
//*/
template< typename ResultType, typename Arg1 >
class FunctorImpl< ResultType, Typelist< Arg1 > >      
  : public Private::FunctorImpl_Base< ResultType >
{
public:
  typedef ResultType ResultType_t;
  typedef typename TypeTraits< Arg1 >::ParameterType Arg1_t;

  virtual ResultType operator()(Arg1) = 0;
};


/*
  implementation, 2 args
//class FunctorImpl< ResultType, TYPELIST_2( Arg1, Arg2 ) >
//*/
template< typename ResultType, typename Arg1, typename Arg2 >
class FunctorImpl< ResultType, Typelist< Arg1, Arg2 > >
  : public Private::FunctorImpl_Base< ResultType >
{
public:
  typedef ResultType ResultType_t;
  typedef typename TypeTraits< Arg1 >::ParameterType Arg1_t;
  typedef typename TypeTraits< Arg2 >::ParameterType Arg2_t;

  virtual ResultType operator()(Arg1, Arg2) = 0;
};


/*
  Functor handler

  Wraps functors and pointers to functions.
//*/
template< class ParentFunctor, typename Fun >
class FunctorHandler
  : public ParentFunctor::Impl_t
{
private:
  typedef typename ParentFunctor::Impl_t Base_t;

public:
  typedef typename Base_t::ResultType_t ResultType_t;
  typedef typename Base_t::Arg1_t Arg1_t;
  typedef typename Base_t::Arg2_t Arg2_t;

  FunctorHandler( const Fun& fun) : f_(fun)
  {}

  // operator()
  ResultType_t operator()()
  {
    return f_();
  }

  ResultType_t operator()(Arg1_t arg1)
  {
    return f_(arg1);
  }

  ResultType_t operator()(Arg1_t arg1, Arg2_t arg2)
  {
    return f_(arg1, arg2);
  }

private:
  Fun f_;
};


/*
  Functor

  A generalized Functor implementation with value semantics.
//*/
template< typename ResultType, typename TList = NIL >
class Functor
{
public:
  typedef FunctorImpl< ResultType, TList > Impl_t;
  typedef ResultType ResultType_t;
  typedef TList ArgList_t;
  typedef typename Impl_t::Arg1_t Arg1_t;
  typedef typename Impl_t::Arg2_t Arg2_t;

  // Member functions
  Functor()
    : spImpl_(0)
  {}

  // ctor for the 'ctor method with static_cast<>()'
  template< typename Fun >
  Functor(Fun fun)
  : spImpl_(new FunctorHandler< Functor, Fun >(fun))
  {}

  ResultType_t operator()()
  {
    return (*spImpl_)();
  }

  ResultType_t operator()(Arg1_t arg1)
  {
    return (*spImpl_)(arg1);
  }

  ResultType_t operator()(Arg1_t arg1, Arg2_t arg2)
  {
    return (*spImpl_)(arg1, arg2);
  }
private:
  std::unique_ptr< Impl_t > spImpl_;
};


#endif
