// structurepolicy.cpp
/*
  Structure policy, here some dummy example for a smart pointer storage type.

  Demonstrates the usage of a default policy.

  A policy shouldn't have a virtual destructor.
//*/


#include <iostream>


/*
  policy 
//*/
template< class T >
class DefaultStoragePolicy
{
public:
  typedef T*
    PointerType_t;

  typedef T& 
    ReferenceType_t;


private: 
  PointerType_t ptr_;

public:
  DefaultStoragePolicy()
  {
    std::cout << "\t\tDefaultStoragePolicy - default policy ctor\n";
  }

  ~DefaultStoragePolicy()
  {
    std::cout << "\t\tDefaultStoragePolicy - default policy dtor\n";
  }

protected:
  PointerType_t getPointer()
  {
    return ptr_;
  }

  void setPointer(PointerType_t ptr)
  {
    ptr_ = ptr;
  }
};


/*
  User..

  explaining the weird template name:

  template<                       // start
    template< class >             // template param type is a template class
                                  //   with (yet) unknown 
                                  // template type, 'typename' is equally
								  //   possible here as 'class'
      class Storage_t             // class name, no 'typename' possible
        =                         // set a default type
      DefaultStoragePolicy        // the default type is the policy
  >                               // ...
//*/
template< template< typename > class Storage_t = DefaultStoragePolicy >
class SmartPtr
{
private:
  Storage_t< char > storage;

public:
  SmartPtr()
  {
    std::cout << "\tSmartPtr - ctor, dummy implementation for a smart pointer"
	          << std::endl;
  }

  ~SmartPtr()
  {
    std::cout << "\tSmartPtr - dtor"
		      << std::endl;
  }
};


/*
  invokation
//*/
int main()
{
  using namespace std;

  typedef SmartPtr<>
    SmartPtr_t;

  SmartPtr_t sptr;

  cout << "READY.\n";
  return 0;
}

