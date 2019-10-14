// functor.hpp
/*
  Loki's implementation doesn't work with the "modern access" of typelist
avoiding macros (described in an article of Alexandrescu). I didn't work on it
either, thus the macros ;)

  (in parts taken from Alexandrescu's loki, 2001)
//*/


#ifndef FUNCTOR_H
#define FUNCTOR_H


#include <memory>


/*************************** Dummy types *************************************/

/*
  Null Type
//*/
class NIL
{
};


/*
  Empty Type
//*/
struct EmptyType {
};


/*************************** Select ******************************************/


/*
  select
//*/
template < bool flag, typename T, typename U >
struct Select {
  typedef T Result;
};

template < typename T, typename U >
struct Select< false, T, U > {
  typedef U Result;
};


/*************************** Typelists ***************************************/


/*
  typelist, maximum 2 different types..
//*/
template < typename T, typename U >
struct Typelist_ {
  typedef T Head;

  typedef U Tail;
};

/*
  Linearizing Typelist Creation

  The "old fashion" implementation uses macros - this functor implementation
  doesn't take the "newer" linearization which would avoid macros.
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
    Searching Typelists

    Algorithm:
    IF TList is NIL, then value is -1
    ELSE
      IF the head of TList is T, then value is 0
      ELSE
        Compute the result of IndexOf applied to TList's tail and T into a
  temporary value temp IF temp is -1, then value is -1 ELSE value is 1 plus temp

    Usage:
    int idx = IndexOf< MyTypelist, TypeToLookUp >::value;
  //*/
  template < class TList, class T >
  struct IndexOf;

  template < class T >
  struct IndexOf< NIL, T > {
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
  template < class TList, class T >
  struct Erase;

  // Specialization 1
  template < class T >
  struct Erase< NIL, T > {
    typedef NIL Result;
  };

  // Specialization 2
  template < class T, class Tail >
  struct Erase< Typelist_< T, Tail >, T > {
    typedef Tail Result;
  };

  // Specialization 3
  template < class Head, class Tail, class T >
  struct Erase< Typelist_< Head, Tail >, T > {
    typedef Typelist_< Head, typename Erase< Tail, T >::Result > Result;
  };
} // namespace TL


/*************************** Traits ******************************************/


/*
  Type Traits - the loki Type Traits, here we use:

  - parameter type
  returns the optimal type to be used as a parameter for functions that take Ts
//*/
template < typename T >
class TypeTraits
{
private:
  // private block - the traits itself
  template < typename U >
  struct PointerTraits {
    enum { result = false };
    typedef NIL PointeeType;
  };

  template < typename U >
  struct PointerTraits< U * > {
    enum { result = true };
    typedef U PointeeType;
  };

  template < typename U >
  struct ReferenceTraits {
    enum { result = false };
    typedef U ReferredType;
  };

  template < typename U >
  struct ReferenceTraits< U & > {
    enum { result = true };
    typedef U ReferredType;
  };

  template < typename U >
  struct PToMTraits {
    enum { result = false };
  };

  template < typename U, typename V >
  struct PToMTraits< U V::* > {
    enum { result = true };
  };

public:
  typedef TYPELIST_4(unsigned char, unsigned short int, unsigned int,
                     unsigned long int) UnsignedInts_t;

  typedef TYPELIST_4(signed char, short int, int, long int) SignedInts_t;

  typedef TYPELIST_2(bool, char) OtherInts_t;

  typedef TYPELIST_2(float, double) Floats_t;

  // isStdArith
  enum { isStdUnsignedInt = TL::IndexOf< UnsignedInts_t, T >::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf< SignedInts_t, T >::value >= 0 };
  enum {
    isStdIntegral = isStdUnsignedInt || isStdSignedInt ||
                    TL::IndexOf< OtherInts_t, T >::value >= 0
  };
  enum { isStdFloat = TL::IndexOf< Floats_t, T >::value >= 0 };
  enum { isStdArith = isStdIntegral || isStdFloat };

  // isPointer
  enum { isPointer = PointerTraits< T >::result };

  // isMemberPointer
  enum { isMemberPointer = PToMTraits< T >::result };

  // ReferredType
  enum { isReference = ReferenceTraits< T >::result };
  typedef typename ReferenceTraits< T >::ReferredType ReferredType;

  // -> ParameterType
  typedef typename Select< isStdArith || isPointer || isMemberPointer, T,
                           ReferredType & >::Result ParameterType;
};


/*************************** Functor *****************************************/


/*
  Functor implementation base class (as struct)

  Base class for a hierarchy of functors. The FunctorImpl class is not used
directly; rather, the Functor class manages and forwards to a pointer to
FunctorImpl

  You may want to derive your own funcotrs from FunctorImpl. Specializations of
  FunctorImpl for up to 2 template parameter types.
//*/
namespace Private
{
  template < typename ResultType >
  struct FunctorImpl_Base {
    typedef ResultType ResultType_t;

    typedef EmptyType Arg1_t;

    typedef EmptyType Arg2_t;
  };
} // namespace Private


/*
  FunctorImpl

  The base class for a hierarchy of funcotrs. The FunctorImpl class is not used
  directly; rather, the Functor class manages and forwards to a pointer to
  FunctorImpl
//*/
template < typename ResultType, typename TList >
class FunctorImpl;


/*
  implementation, 0 args
//*/
template < typename ResultType >
class FunctorImpl< ResultType, NIL >
    : public Private::FunctorImpl_Base< ResultType >
{
public:
  typedef ResultType ResultType_t;

  virtual ResultType operator()() = 0;
};


/*
  implementation, 1 arg
//*/
template < typename ResultType, typename Arg1 >
class FunctorImpl< ResultType, TYPELIST_1(Arg1) >
    : public Private::FunctorImpl_Base< ResultType >
{
public:
  typedef ResultType ResultType_t;

  typedef typename TypeTraits< Arg1 >::ParameterType Arg1_t;

  virtual ResultType operator()(Arg1) = 0;
};


/*
  implementation, 2 args
//*/
template < typename ResultType, typename Arg1, typename Arg2 >
class FunctorImpl< ResultType, TYPELIST_2(Arg1, Arg2) >
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
template < class ParentFunctor, typename Fun >
class FunctorHandler : public ParentFunctor::Impl_t
{
private:
  typedef typename ParentFunctor::Impl_t Base_t;

public:
  typedef typename Base_t::ResultType_t ResultType_t;

  typedef typename Base_t::Arg1_t Arg1_t;

  typedef typename Base_t::Arg2_t Arg2_t;

  FunctorHandler(const Fun &fun) : f_(fun) {}

  // operator()
  ResultType_t operator()() { return f_(); }

  ResultType_t operator()(Arg1_t arg1) { return f_(arg1); }

  ResultType_t operator()(Arg1_t arg1, Arg2_t arg2) { return f_(arg1, arg2); }

private:
  Fun f_;
};


/*
  Functor

  A generalized Functor implementation with value semantics.
//*/
template < typename ResultType, typename TList = NIL >
class Functor
{
public:
  typedef FunctorImpl< ResultType, TList > Impl_t;

  typedef ResultType ResultType_t;

  typedef TList ArgList_t;

  typedef typename Impl_t::Arg1_t Arg1_t;

  typedef typename Impl_t::Arg2_t Arg2_t;

  // Member functions
  Functor() : spImpl_(0) {}

  // ctor for the 'ctor method with static_cast<>()'
  template < typename Fun >
  Functor(Fun fun) : spImpl_(new FunctorHandler< Functor, Fun >(fun))
  {
  }

  ResultType_t operator()() { return (*spImpl_)(); }

  ResultType_t operator()(Arg1_t arg1) { return (*spImpl_)(arg1); }

  ResultType_t operator()(Arg1_t arg1, Arg2_t arg2)
  {
    return (*spImpl_)(arg1, arg2);
  }

private:
  std::auto_ptr< Impl_t > spImpl_;
};


#endif
