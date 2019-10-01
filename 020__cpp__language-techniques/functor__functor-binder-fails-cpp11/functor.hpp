// functor.hpp
/*
  functor implementation copied from Loki, reduced to 2 parameters ;)

  Extended with the missing stuff (select, traits, typelists, etc),
  namespace Loki is removed!

  Everything else is original.

  Binding fails with a "logical exception" on gcc 4.3.2 on execution, follows a SIGABRT / 6.
  This version demonstrates the called constructors..



  RESOURCES

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

   last update: June 20, 2001

   adjusted and modified: Lothar Rubusch, 2019
   note: ancient traits and binders using modernized variadic approach
// */


#ifndef FUNCTOR_INC_
#define FUNCTOR_INC_

#include <iostream>
#include <typeinfo>
#include <memory>
#include <type_traits>
#include <cassert>


/*****************************************************************************/


/*
  Null Type
//*/
class NIL{};


/*
  Empty Type
//*/
struct EmptyType{};


/*****************************************************************************/


/*
  select
//*/
template< bool flag, typename T, typename U >
struct Select
{ using Result = T; };

template< typename T, typename U >
struct Select< false, T, U >
{ using Result = U; };


/*****************************************************************************/


namespace TL
{
  /*
    TypeList

    NOTE: before a typelist needed always to contain at least one element,
    this made an empty element necessary, in this cpp11 implementation also an
    empty Typelist is possible

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
    TypeAt

    type at index

    usage:
      using type_at_4 = typename TypeAt< 4, MyList >::type;
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
    IndexOf

    indexed access

    NOTE: the int should be 'constexpr static' to let the compiler do all the work,
    leaving away 'constexpr static' is not an error, though

    usage:
      constexpr static auto idx = IndexOf< Type, MyList >::value;
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
    PushBack/PushFront

    appending to Typelists

    NOTE: since a typelist defines a compile time static type, every
    modification will result in a new typelist definition, thus 'MyList' becomes
    'MyNewList'

    Usage:
      using MyNewList = typename PushBack< Type, MyList >::type;
    or
      using MyNewList = typename PushFront< Type, MyList >::type;
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
    Erase

    erase a Type from a Typelist

    usage:
      using MyNewList = typename Erase< Type, MyList >::type;
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
}


/*****************************************************************************/


/*
  Type Traits - the loki Type Traits, here we use:

  - parameter type
  returns the optimal type to be used as a parameter for functions that take Ts

  [historic C++98 implementation, polished]
//*/
template<typename T>
class TypeTraits
{
private:
  // private block - the traits itself

  // kept as demo: for 'isReference()' and 'get referred type'
  template< typename U > struct ReferenceTraits
  {
    enum { result = false };
    using ReferredType = U;
  };

  template< typename U > struct ReferenceTraits< U& >
  {
    enum { result = true };
    using ReferredType = U;
  };

public:
  // typelists
  using UnsignedInts_t = TL::Typelist< unsigned char, unsigned short int, unsigned int, unsigned long int >;
  using SignedInts_t = TL::Typelist< signed char, short int, int, long int >;
  using OtherInts_t = TL::Typelist< bool, char >;
  using Floats_t = TL::Typelist< float, double >;

  // isStdArith, also C++11 offers std::is_unsigned< T >::value, std::is_signed< T >::value,...
  enum { isStdUnsignedInt = TL::IndexOf< T, UnsignedInts_t >::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf< T, SignedInts_t >::value >= 0 };
  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< T, OtherInts_t >::value >= 0 };
  enum { isStdFloat = TL::IndexOf< T, Floats_t >::value >= 0 };
  enum { isStdArith = isStdIntegral || isStdFloat };

  // isPointer
  enum { isPointer = std::is_pointer< T >::value };

  // isMemberPointer
  enum { isMemberPointer = std::is_member_pointer< T >::value };

  // ReferredType, alternative use 'std::is_reference< T >::value'
  enum { isReference = ReferenceTraits< T >::result }; // TODO rm

  // get referred type
  using ReferredType = typename ReferenceTraits< T >::ReferredType;

  // -> ParameterType
  using ParameterType = typename Select< isStdArith || isPointer || isMemberPointer, T, ReferredType& >::Result;
};


/*****************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl (internal)
////////////////////////////////////////////////////////////////////////////////

namespace Private
{
  //  template <typename R, template <class> class ThreadingModel>
  //  struct FunctorImplBase : public SmallObject<ThreadingModel>
  template < typename R >
  struct FunctorImplBase
  {
    virtual ~FunctorImplBase(){}

    using ResultType = R;
    using Parm1 = EmptyType;
    using Parm2 = EmptyType;

    virtual FunctorImplBase* DoClone() const = 0;

    template <class U>
    static U* Clone(U* pObj)
    {
      if (!pObj) return nullptr;
//      U* pClone = static_cast< U* >(pObj->DoClone()); // TODO rm
      auto pClone = static_cast< U* >(pObj->DoClone());
      assert(typeid(*pClone) == typeid(*pObj));
      return pClone;
    }
  };
}

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// The base class for a hierarchy of functors. The FunctorImpl class is not used
//     directly; rather, the Functor class manages and forwards to a pointer to
//     FunctorImpl
// You may want to derive your own functors from FunctorImpl.
// Specializations of FunctorImpl for up to 15 parameters follow
////////////////////////////////////////////////////////////////////////////////

template < typename R, class TList >
class FunctorImpl;

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 0 (zero) parameters
////////////////////////////////////////////////////////////////////////////////

template< typename R >
class FunctorImpl< R, NIL >
  : public Private::FunctorImplBase< R >
{
public:
  using ResultType = R;

  virtual R operator()() = 0;
};

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 1 parameter
////////////////////////////////////////////////////////////////////////////////

// totally abstract!!!
template< typename R, typename P1 >
class FunctorImpl< R, TL::Typelist< P1 > >
  : public Private::FunctorImplBase< R >
{
 public:
  using ResultType = R;
  using Parm1 = typename TypeTraits< P1 >::ParameterType;

  virtual R operator()(Parm1) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 2 parameters
////////////////////////////////////////////////////////////////////////////////

// totally abstract!!!
template< typename R, typename P1, typename P2 >
class FunctorImpl< R, TL::Typelist< P1, P2 > >
  : public Private::FunctorImplBase< R >
{
public:
  using ResultType = R;
  using Parm1 = typename TypeTraits< P1 >::ParameterType;
  using Parm2 = typename TypeTraits< P2 >::ParameterType;

  virtual R operator()(Parm1, Parm2) = 0;
};


////////////////////////////////////////////////////////////////////////////////
// class template FunctorHandler
// Wraps functors and pointers to functions
////////////////////////////////////////////////////////////////////////////////

template <class ParentFunctor, typename Fun>
class FunctorHandler
  : public ParentFunctor::Impl
{
  using Base = typename ParentFunctor::Impl;

public:
  using ResultType = typename Base::ResultType;
  using Parm1 = typename Base::Parm1;
  using Parm2 = typename Base::Parm2;

  // functor handler function
  //
  // the private 'f_()' will be initialized with *this, this has op(), op(p1), op(p1, p2) overloaded,
  // thus the passed object of template Fun via '*this' can be called as a function via ops()
  FunctorHandler(const Fun& fun) : f_(fun)
  {}

  virtual FunctorHandler* DoClone() const
  { return new FunctorHandler(*this); }

  // operator() implementations
  ResultType operator()()
  { return f_(); }

  ResultType operator()(Parm1 p1)
  { return f_(p1); }

  ResultType operator()(Parm1 p1, Parm2 p2)
  { return f_(p1, p2); }

private:
  Fun f_;
};

////////////////////////////////////////////////////////////////////////////////
// class template FunctorHandler
// Wraps pointers to member functions
////////////////////////////////////////////////////////////////////////////////

template <class ParentFunctor, typename PointerToObj, typename PointerToMemFn>
class MemFunHandler : public ParentFunctor::Impl
{
  using Base = typename ParentFunctor::Impl;

public:
  using ResultType = typename Base::ResultType;
  using Parm1 = typename Base::Parm1;
  using Parm2 = typename Base::Parm2;

  MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn) : pObj_(pObj), pMemFn_(pMemFn)
  {}

  virtual MemFunHandler* DoClone() const
  { return new MemFunHandler(*this); }

    ResultType operator()()
  { return ((*pObj_).*pMemFn_)(); }

  ResultType operator()(Parm1 p1)
  { return ((*pObj_).*pMemFn_)(p1); }

  ResultType operator()(Parm1 p1, Parm2 p2)
  { return ((*pObj_).*pMemFn_)(p1, p2); }

private:
  PointerToObj pObj_;
  PointerToMemFn pMemFn_;
};

////////////////////////////////////////////////////////////////////////////////
// class template Functor
// A generalized functor implementation with value semantics
////////////////////////////////////////////////////////////////////////////////

template< typename R, class TList = NIL >
class Functor
{
public:
  // Handy type definitions for the body type
  using Impl = FunctorImpl< R, TList >;
  using ResultType = R;
  using ParmList = TList;
  using Parm1 = typename Impl::Parm1;
  using Parm2 = typename Impl::Parm2;

  // Member functions

  Functor() : spImpl_(0)
  {
    std::cout << "Functor()\n";
  }

  Functor(const Functor& rhs) : spImpl_(Impl::Clone(rhs.spImpl_.get()))
  {
    std::cout << "Functor(const Functor& rhs)\n";
  }

  Functor(std::shared_ptr<Impl> spImpl) : spImpl_(spImpl)
  {
    std::cout << "Functor(std::shared_ptr<Impl> spImpl)\n";
  }

  template <typename Fun>
  Functor(Fun fun)
    : spImpl_(new FunctorHandler<Functor, Fun>(fun))
  {
    std::cout << "template <typename Fun>\n\tFunctor(Fun fun)\n";
  }

  template <class PtrObj, typename MemFn>
  Functor(const PtrObj& p, MemFn memFn)
    : spImpl_(new MemFunHandler<Functor, PtrObj, MemFn>(p, memFn))
  {
    std::cout << "template <class PtrObj, typename MemFn>\n\tFunctor(const PtrObj& p, MemFn memFn)\n";
  }

  Functor& operator=(const Functor& rhs)
  {
    Functor copy(rhs);

    // swap smart ptrs by hand
    auto *pImpl = spImpl_.release();
    spImpl_.reset(copy.spImpl_.release());
    copy.spImpl_.reset(pImpl);

    return *this;
  }

  ResultType operator()()
  { return (*spImpl_)(); }

  ResultType operator()(Parm1 p1)
  { return (*spImpl_)(p1); }

  ResultType operator()(Parm1 p1, Parm2 p2)
  { return (*spImpl_)(p1, p2); }

private:
  std::shared_ptr< Impl > spImpl_;
};

namespace Private
{
  template< class Fctor > struct BinderFirstTraits;

  template< typename R, class TList >
  struct BinderFirstTraits< Functor< R, TList > >
  {
    using ParmList = typename TL::Erase< typename TL::TypeAt< 0, TList >::type, TList >::type;
    using BoundFunctorType = Functor< R, ParmList >;
    using Impl = typename BoundFunctorType::Impl;
  };
}

////////////////////////////////////////////////////////////////////////////////
// class template BinderFirst
// Binds the first parameter of a Functor object to a specific value
////////////////////////////////////////////////////////////////////////////////

template< class OriginalFunctor >
class BinderFirst
  : public Private::BinderFirstTraits<OriginalFunctor>::Impl
{
  using Base = typename Private::BinderFirstTraits< OriginalFunctor >::Impl;
  using ResultType = typename OriginalFunctor::ResultType;
  using BoundType = typename OriginalFunctor::Parm1;
  using Parm1 = typename OriginalFunctor::Parm2;
  using Param2 = EmptyType;

public:
  BinderFirst(const OriginalFunctor& fun, BoundType bound)
    : f_(fun), b_(bound)
  {}

  virtual BinderFirst* DoClone() const { return new BinderFirst(*this); }

  ResultType operator()()
  { return f_(b_); }

  ResultType operator()(Parm1 p1)
  { return f_(b_, p1); }

private:
  OriginalFunctor f_;
  BoundType b_;
};

////////////////////////////////////////////////////////////////////////////////
// function template BindFirst
// Binds the first parameter of a Functor object to a specific value
////////////////////////////////////////////////////////////////////////////////

template <class Fctor>
typename Private::BinderFirstTraits<Fctor>::BoundFunctorType
BindFirst(const Fctor& fun, typename Fctor::Parm1 bound)
{
  using Outgoing = typename Private::BinderFirstTraits< Fctor >::BoundFunctorType;

  return Outgoing(std::shared_ptr<typename Outgoing::Impl>( new BinderFirst<Fctor>(fun, bound)));
}

////////////////////////////////////////////////////////////////////////////////
// class template Chainer
// Chains two functor calls one after another
////////////////////////////////////////////////////////////////////////////////

template <typename Fun1, typename Fun2>
class Chainer : public Fun2::Impl
{
  using Base = Fun2;

public:
  using ResultType = typename Base::ResultType;
  using Parm1 = typename Base::Parm1;
  using Parm2 = typename Base::Parm2;

  Chainer(const Fun1& fun1, const Fun2& fun2) : f1_(fun1), f2_(fun2) {}

  virtual Chainer* DoClone() const { return new Chainer(*this); }

  // operator() implementations for up to 15 arguments

  ResultType operator()()
  { return f1_(), f2_(); }

  ResultType operator()(Parm1 p1)
  { return f1_(p1), f2_(p1); }

  ResultType operator()(Parm1 p1, Parm2 p2)
  { return f1_(p1, p2), f2_(p1, p2); }

private:
  Fun1 f1_;
  Fun2 f2_;
};

////////////////////////////////////////////////////////////////////////////////
// function template Chain
// Chains two functor calls one after another
////////////////////////////////////////////////////////////////////////////////


template <class Fun1, class Fun2>
Fun2 Chain(const Fun1& fun1, const Fun2& fun2)
{
  return Fun2(std::shared_ptr<typename Fun2::Impl>(new Chainer<Fun1, Fun2>(fun1, fun2)));
}


////////////////////////////////////////////////////////////////////////////////
// Change log:
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
////////////////////////////////////////////////////////////////////////////////

#endif  // FUNCTOR_INC_
