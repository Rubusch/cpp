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
#include <memory> /* unique_ptr */


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
  cpp11: Typelist

  usage:
  Typelist< Type1, Type2, Type3 >
//*/
template< typename ...Ts >
struct Typelist
{
  using type = Typelist;
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


  cpp11: version of IndexOf

  usage:
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
}


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
    static constexpr auto result = false;
    typedef NIL PointeeType;
  };

  template< typename U > struct PointerTraits< U* >
  {
    static constexpr auto result = true;
    typedef U PointeeType;
  };

  template< typename U > struct ReferenceTraits
  {
    static constexpr auto result = false;
    typedef U ReferredType;
  };

  template< typename U > struct ReferenceTraits< U& >
  {
    static constexpr auto result = true;
    typedef U ReferredType;
  };

  template< typename U > struct PToMTraits
  {
    static constexpr auto result = false;
  };

  template< typename U, typename V > struct PToMTraits< U V::*>
  {
    static constexpr auto result = false;
  };

public:
  using UnsignedInts_t = Typelist< unsigned char, unsigned short int, unsigned int, unsigned long int >;
  using SignedInts_t = Typelist< signed char, short int, int, long int >;
  using OtherInts_t = Typelist< bool, char >;
  using Floats_t = Typelist< float, double >;

  // isStdArith
// *
  static constexpr auto isStdUnsignedInt = TL::IndexOf< T, UnsignedInts_t >::value >= 0;
  static constexpr auto isStdSignedInt = TL::IndexOf< T, SignedInts_t >::value >= 0;
  static constexpr auto isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< T, OtherInts_t >::value >= 0;
  static constexpr auto isStdFloat = TL::IndexOf< T, Floats_t >::value >= 0;
  static constexpr auto isStdArith = isStdIntegral || isStdFloat;
/*/
// TODO: check if not actually the second should be correct?
  static constexpr auto isStdUnsignedInt = TL::IndexOf< UnsignedInts_t, T >::value >= 0;
  static constexpr auto isStdSignedInt = TL::IndexOf< SignedInts_t, T >::value >= 0;
  static constexpr auto isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< OtherInts_t, T >::value >= 0;
  static constexpr auto isStdFloat = TL::IndexOf< Floats_t, T >::value >= 0;
  static constexpr auto isStdArith = isStdIntegral || isStdFloat;
// */
  // isPointer
  static constexpr auto isPointer = PointerTraits< T >::result;

  // isMemberPointer
  static constexpr auto isMemberPointer = PToMTraits< T >::result;

  // ReferredType
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
