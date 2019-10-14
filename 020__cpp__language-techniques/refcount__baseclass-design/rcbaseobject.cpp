// rcbaseobject.cpp
/*
//*/


#include "rcbaseobject.hpp"


/*
  ctor
//*/
RCBaseObject::RCBaseObject() : refCount(0), shareable(true) {}


/*
  copy constructor
//*/
RCBaseObject::RCBaseObject(const RCBaseObject &) : refCount(0), shareable(true)
{
}


/*
  operator=

  No deep copy needed here, just return this.
  In case there were individual values for each instance, they
  would need to be copied here!
//*/
RCBaseObject &RCBaseObject::operator=(const RCBaseObject &) { return *this; }


/*
  dtor
//*/
RCBaseObject::~RCBaseObject() { std::cout << "RCBaseObject::DTOR\n"; }


/************************************************************************************/


void RCBaseObject::addReference() { ++refCount; }


void RCBaseObject::removeReference()
{
  if (--refCount == 0)
    delete this;
}


void RCBaseObject::markUnshareable() { shareable = false; }


bool RCBaseObject::isShareable() const { return shareable; }


bool RCBaseObject::isShared() const { return refCount > 1; }
