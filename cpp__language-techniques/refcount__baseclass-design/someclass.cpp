// someclass.cpp
/*
//*/


#include "someclass.hpp"

/*
  init function
//*/
void SomeClass::SomeClassValue::init(const char *initValue)
{
  int initValueSize = strlen(initValue) + 1;
  data = new char[initValueSize];
  strncpy(data, initValue, initValueSize);
}


/*
  ref count ctor
//*/
SomeClass::SomeClassValue::SomeClassValue(const char *initValue)
{
  init(initValue);
}


/*
  ref count copy ctor
//*/
SomeClass::SomeClassValue::SomeClassValue(const SomeClassValue& rhs)
{
  init(rhs.data);
}


/*
  refc count dtor
//*/
SomeClass::SomeClassValue::~SomeClassValue()
{
  std::cout << "SomeClass::SomeClassValue::DTOR\n";

  delete [] data;
}


/************************************************************************************/


/*
  ctor
//*/
SomeClass::SomeClass(const char *initValue)
  : value(new SomeClassValue(initValue))
{}


/*
  dtor
//*/
SomeClass::~SomeClass()
{
  std::cout << "SomeClass::DTOR\n";
}


/*
  const operator[] - copy on write for constant objects
//*/
const char& SomeClass::operator[](int index) const
{
  return value->data[index];
}


/*
  operator[] - copy on write for constant objects
//*/
char& SomeClass::operator[](int index)
{
  if(value->isShared()){
    value = new SomeClassValue(value->data);
  }
  value->markUnshareable();

  return value->data[index];
}


/*
  operator<< - output of class content..
//*/
std::ostream& operator<<(std::ostream& out, SomeClass& obj)
{
  //return out << "\tdata: " << str << std::endl;
  return out << "\tdata: " << (obj.value)->data << std::endl;
}

