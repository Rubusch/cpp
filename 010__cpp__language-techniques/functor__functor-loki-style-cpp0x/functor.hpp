// functor.hpp
/*
  functor implementation copied from Loki, reduced to 2 parameters ;)

  Extended with the missing stuff (select, traits, typelists, etc),
  namespace Loki is removed!

  Everything else is original.
//*/


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

// Last update: June 20, 2001

#ifndef FUNCTOR_INC_
#define FUNCTOR_INC_


#include <typeinfo>
#include <memory>
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
{
  typedef T Result;
};

template< typename T, typename U >
struct Select< false, T, U >
{
  typedef U Result;
};


/*****************************************************************************/


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
#define TYPELIST_1(T1) Typelist_< T1, NIL >
#define TYPELIST_2(T1, T2) Typelist_< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist_< T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist_< T1, TYPELIST_3(T2, T3, T4) >


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
    IF TList is NIL, then value is -1
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
  //*/
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
}


/*****************************************************************************/


/*
  Type Traits - the loki Type Traits, here we use:

  - parameter type
  returns the optimal type to be used as a parameter for functions that take Ts
//*/
template<typename T>
class TypeTraits
{
private:
  // private block - the traits itself
  template< typename U > struct PointerTraits
  {
    enum { result = false };
    typedef NIL
      PointeeType;
  };

  template< typename U > struct PointerTraits< U* >
  {
    enum { result = true };
    typedef U
      PointeeType;
  };

  template< typename U > struct ReferenceTraits
  {
    enum { result = false };
    typedef U ReferredType;
  };

  template< typename U > struct ReferenceTraits< U& >
  {
    enum { result = true };
    typedef U ReferredType;
  };

  template< typename U > struct PToMTraits
  {
    enum { result = false };
  };

  template< typename U, typename V > struct PToMTraits< U V::*>
  {
    enum { result = true };
  };

public:
  // typelists
  typedef TYPELIST_4( unsigned char, unsigned short int, unsigned int, unsigned long int )
    UnsignedInts_t;

  typedef TYPELIST_4( signed char, short int, int, long int )
    SignedInts_t;

  typedef TYPELIST_2( bool, char )
    OtherInts_t;

  typedef TYPELIST_2( float, double )
    Floats_t;

  // isStdArith
  enum { isStdUnsignedInt = TL::IndexOf< UnsignedInts_t, T >::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf< SignedInts_t, T >::value >= 0 };
  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf< OtherInts_t, T >::value >= 0 };
  enum { isStdFloat = TL::IndexOf< Floats_t, T >::value >= 0 };
  enum { isStdArith = isStdIntegral || isStdFloat };

  // isPointer
  enum { isPointer = PointerTraits< T >::result };

  // isMemberPointer
  enum { isMemberPointer = PToMTraits< T >::result };

  // ReferredType
  enum { isReference = ReferenceTraits< T >::result };
  typedef typename ReferenceTraits< T >::ReferredType
    ReferredType;

  // -> ParameterType
  typedef typename Select< isStdArith || isPointer || isMemberPointer, T, ReferredType& >::Result
    ParameterType;
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
    typedef R ResultType;

    typedef EmptyType Parm1;
    typedef EmptyType Parm2;

    virtual FunctorImplBase* DoClone() const = 0;
    template <class U>
    static U* Clone(U* pObj)
    {
      if (!pObj) return 0;
      U* pClone = static_cast<U*>(pObj->DoClone());
      assert(typeid(*pClone) == typeid(*pObj));
      return pClone;
    }
  };
}

////////////////////////////////////////////////////////////////////////////////
// macro DEFINE_CLONE_FUNCTORIMPL
// Implements the DoClone function for a functor implementation
////////////////////////////////////////////////////////////////////////////////

#define DEFINE_CLONE_FUNCTORIMPL(Cls) \
    virtual Cls* DoClone() const { return new Cls(*this); }

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// The base class for a hierarchy of functors. The FunctorImpl class is not used
//     directly; rather, the Functor class manages and forwards to a pointer to
//     FunctorImpl
// You may want to derive your own functors from FunctorImpl.
// Specializations of FunctorImpl for up to 15 parameters follow
////////////////////////////////////////////////////////////////////////////////

/*
template <typename R, class TList,
          template <class> class ThreadingModel = DEFAULT_THREADING>
class FunctorImpl;
//*/
template < typename R, class TList >
class FunctorImpl;

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 0 (zero) parameters
////////////////////////////////////////////////////////////////////////////////

/*
template <typename R, template <class> class ThreadingModel>
class FunctorImpl<R, NullType, ThreadingModel>
  : public Private::FunctorImplBase<R, ThreadingModel>
//*/
template< typename R >
class FunctorImpl< R, NIL >
  : public Private::FunctorImplBase< R >
{
public:
  typedef R ResultType;
  virtual R operator()() = 0;
};

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 1 parameter
////////////////////////////////////////////////////////////////////////////////

/*
template <typename R, typename P1, template <class> class ThreadingModel>
class FunctorImpl<R, TYPELIST_1(P1), ThreadingModel>
  : public Private::FunctorImplBase<R, ThreadingModel>
//*/
template< typename R, typename P1 >
class FunctorImpl< R, TYPELIST_1( P1 ) >
  : public Private::FunctorImplBase< R >
{
 public:
  typedef R ResultType;
  typedef typename TypeTraits<P1>::ParameterType Parm1;
  virtual R operator()(Parm1) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 2 parameters
////////////////////////////////////////////////////////////////////////////////

/*
template <typename R, typename P1, typename P2,
          template <class> class ThreadingModel>
class FunctorImpl<R, TYPELIST_2(P1, P2), ThreadingModel>
  : public Private::FunctorImplBase<R, ThreadingModel>
//*/
template< typename R, typename P1, typename P2 >
class FunctorImpl< R, TYPELIST_2(P1, P2) >
  : public Private::FunctorImplBase< R >
{
public:
  typedef R ResultType;
  typedef typename TypeTraits< P1 >::ParameterType Parm1;
  typedef typename TypeTraits< P2 >::ParameterType Parm2;
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
  typedef typename ParentFunctor::Impl Base;

public:
  typedef typename Base::ResultType ResultType;
  typedef typename Base::Parm1 Parm1;
  typedef typename Base::Parm2 Parm2;

  FunctorHandler(const Fun& fun) : f_(fun) {}

  DEFINE_CLONE_FUNCTORIMPL(FunctorHandler)

    // operator() implementations for up to 15 arguments

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

/*
template <class ParentFunctor, typename PointerToObj,
          typename PointerToMemFn>
class MemFunHandler : public ParentFunctor::Impl
//*/
template <class ParentFunctor, typename PointerToObj, typename PointerToMemFn>
class MemFunHandler : public ParentFunctor::Impl
{
  typedef typename ParentFunctor::Impl Base;

public:
  typedef typename Base::ResultType ResultType;
  typedef typename Base::Parm1 Parm1;
  typedef typename Base::Parm2 Parm2;

  MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn)
    : pObj_(pObj), pMemFn_(pMemFn)
  {}

  DEFINE_CLONE_FUNCTORIMPL(MemFunHandler)

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

/*
template <typename R, class TList = NullType,
          template<class> class ThreadingModel = DEFAULT_THREADING>
class Functor
//*/
template< typename R, class TList = NIL >
class Functor
{
public:
  // Handy type definitions for the body type
  typedef FunctorImpl<R, TList> Impl;
  typedef R ResultType;
  typedef TList ParmList;
  typedef typename Impl::Parm1 Parm1;
  typedef typename Impl::Parm2 Parm2;

  // Member functions

  Functor() : spImpl_(0)
  {}

  Functor(const Functor& rhs) : spImpl_(Impl::Clone(rhs.spImpl_.get()))
  {}

  Functor(std::auto_ptr<Impl> spImpl) : spImpl_(spImpl)
  {}

  template <typename Fun>
  Functor(Fun fun)
    : spImpl_(new FunctorHandler<Functor, Fun>(fun))
  {}

  template <class PtrObj, typename MemFn>
  Functor(const PtrObj& p, MemFn memFn)
    : spImpl_(new MemFunHandler<Functor, PtrObj, MemFn>(p, memFn))
  {}

  Functor& operator=(const Functor& rhs)
  {
    Functor copy(rhs);
    // swap auto_ptrs by hand
    Impl* p = spImpl_.release();
    spImpl_.reset(copy.spImpl_.release());
    copy.spImpl_.reset(p);
    return *this;
  }

  ResultType operator()()
  { return (*spImpl_)(); }

  ResultType operator()(Parm1 p1)
  { return (*spImpl_)(p1); }

  ResultType operator()(Parm1 p1, Parm2 p2)
  { return (*spImpl_)(p1, p2); }

private:
  std::auto_ptr<Impl> spImpl_;
};

namespace Private
{
  template< class Fctor > struct BinderFirstTraits;

  template< typename R, class TList >
  struct BinderFirstTraits< Functor< R, TList > >
  {
    typedef typename TL::Erase< TList, typename TL::TypeAt< TList, 0 >::Result >::Result ParmList;
    typedef Functor< R, ParmList > BoundFunctorType;
    typedef typename BoundFunctorType::Impl Impl;
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
  typedef typename Private::BinderFirstTraits<OriginalFunctor>::Impl Base;
  typedef typename OriginalFunctor::ResultType ResultType;

  typedef typename OriginalFunctor::Parm1 BoundType;

  typedef typename OriginalFunctor::Parm2 Parm1;

  typedef EmptyType Param2;

public:
  BinderFirst(const OriginalFunctor& fun, BoundType bound)
    : f_(fun), b_(bound)
  {}

  DEFINE_CLONE_FUNCTORIMPL(BinderFirst)

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

/*
template <class Fctor>
typename Private::BinderFirstTraits<Fctor>::BoundFunctorType
BindFirst(const Fctor& fun, typename Fctor::Parm1 bound)
//*/
template <class Fctor>
typename Private::BinderFirstTraits<Fctor>::BoundFunctorType
BindFirst(const Fctor& fun, typename Fctor::Parm1 bound)
{
  typedef typename Private::BinderFirstTraits<Fctor>::BoundFunctorType
    Outgoing;

  return Outgoing(std::auto_ptr<typename Outgoing::Impl>( new BinderFirst<Fctor>(fun, bound)));
}

////////////////////////////////////////////////////////////////////////////////
// class template Chainer
// Chains two functor calls one after another
////////////////////////////////////////////////////////////////////////////////

template <typename Fun1, typename Fun2>
class Chainer : public Fun2::Impl
{
  typedef Fun2 Base;

public:
  typedef typename Base::ResultType ResultType;
  typedef typename Base::Parm1 Parm1;
  typedef typename Base::Parm2 Parm2;

  Chainer(const Fun1& fun1, const Fun2& fun2) : f1_(fun1), f2_(fun2) {}

  DEFINE_CLONE_FUNCTORIMPL(Chainer)

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
  return Fun2(std::auto_ptr<typename Fun2::Impl>(new Chainer<Fun1, Fun2>(fun1, fun2)));
}


////////////////////////////////////////////////////////////////////////////////
// Change log:
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
////////////////////////////////////////////////////////////////////////////////

#endif  // FUNCTOR_INC_
