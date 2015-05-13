// someclass.cpp
/*
//*/


#include "someclass.hpp"


/*
  data value - init function, called by the ctor
//*/
void SomeClass::SomeClassValue::init(const char *initValue)
{
  using namespace std;
  
  int initValueSize = strlen(initValue) + 1; // unsafe! 
  data = new char[initValueSize];
  strncpy(data, initValue, initValueSize);
}


/*
  data value - ctor
//*/
SomeClass::SomeClassValue::SomeClassValue(const char *initValue)
{ 
  init(initValue);
}


/*
  data value - copy ctor
//*/
SomeClass::SomeClassValue::SomeClassValue(const SomeClassValue& rhs)
{
  init(rhs.data);
}


/*
  data value - dtor
//*/
SomeClass::SomeClassValue::~SomeClassValue()
{
  delete [] data;
}


/*
  ctor
//*/
SomeClass::SomeClass(const char *initValue)
  : value(new SomeClassValue(initValue)) 
{}


/*
  COW - copy on write for objects
//*/
char SomeClass::operator[](int index) const
{
  return value->data[index];
}


/*
  COW - copy on write for const objects
//*/
char& SomeClass::operator[](int index)
{ 
  if(value->isShared()){      
    value = new SomeClassValue(value->data);
  }
  
  value->markUnshareable();
  
  return value->data[index];
}


/************************************************************************************/


/*
  friend function - output function to get some accessibility
//*/
std::ostream& operator<<(std::ostream& out, const SomeClass & sc)
{
  return out << sc.value->data;
}

