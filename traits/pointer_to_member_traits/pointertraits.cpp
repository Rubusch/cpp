// pointertraits.cpp
/*
  "Traits are a generic programming technique that allows compile-time
  decisions to be made based on types, much as you would make runtime
  decisions based on values.

  This makes the resulting code cleaner, more readable, and easier to
  maintain."

  "Detection of pointers to members is a bit different [than detection
  of a pointer type]. The specialization needed is as follows."

  Taken from "Modern C++ Design", Alexandrescu


  The following definitions should explain the algorithm a little:
    class SomeClass
    {
      ...
    public:
      int data;
    };

  &SomeClass.data   - a pointer to an instance of a member
  &SomeClass::data  - a pointer-to-member, CAUTION: data is a concrete instance!

  The type of data would be something like:
  int SomeClass::*
  
  Therefore the trait uses "U V::*" in its declaration:
    template< class U, class V > struct Ptr2MemTraits< U V::* >
    {
    ...

  Thus we here need a conversion function to test a pure type declaration for
  being a pointer-to-member type via the trait.
//*/


#include <iostream>


/*
  Type Traits

  Returns (at compile time) true if T is a pointer to member type.

  Usage:
  bool isMemPtr = TypeTraits< TypeToCheck >::isMemberPointer;
//*/
template< typename T >
class TypeTraits
{
private:
  // Pointer to Member: returns at compile time true if T is a pointer to member type
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
  enum { isPointer2Member = Ptr2MemTraits< T >::result };
};


/*
  some stupid demo class
//*/
class SomeClass
{
private:
  // inner class / struct 
  typedef struct { int value; } Member_t;
  Member_t memberField;

public:
  // 1. possibility of a "pointer-to-member-type" declaration: &SomeClass::memberData
  int memberData;

  // 2. possibility of a "poitner-to-member-type" declaration: &SomeClass::pMemberField
  Member_t *pMemberField;
  
  SomeClass(){}
};


/*
  conversion function
//*/
template< typename TestType >
bool memberPointerTest( TestType memPtr)
{
  return TypeTraits< TestType >::isPointer2Member;
}


/*
  output automization
//*/
template< typename T >
void output( T t, std::string expected)
{
  std::cout << " points to a member?\n" 
            << (memberPointerTest( t) ? "\"true\"" : "\"false\"")
            << "\t(expected: " << expected << ")"
            << std::endl;
}


/*
  main

  "You can now gain some insight into the std::vector::iterator
  implementation - is it a plain pointer or an elaborate type?"
//*/
int main()
{
  using namespace std;

  // init
  cout << "init class\n";
  cout << endl;


  cout << "&SomeClass::memberData";
  output( &SomeClass::memberData, "true");
  cout << endl;


  cout << "&SomeClass::pMemberField";
  output( &SomeClass::pMemberField, "true");
  cout << endl;

  
  int noMember;
  cout << "&noMember";
  output( &noMember, "false");
  cout << endl;


  cout << "also no member: '12'";
  output( 12, "false");
  cout << endl;


  cout << "READY.\n";
  return 0;
}
