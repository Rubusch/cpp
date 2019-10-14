// rcobject.cpp
/*
//*/


#include "rcobject.hpp"


/*
  ctor
//*/
RCObject::RCObject() : refCount(0), shareable(true) {}


/*
  copy ctor
//*/
RCObject::RCObject(const RCObject &) : refCount(0), shareable(true) {}


/*
  op=
//*/
RCObject &RCObject::operator=(const RCObject &) { return *this; }


/*
  dtor
//*/
RCObject::~RCObject() {}


/*
  rc - increment reference counter
//*/
void RCObject::addReference() { ++refCount; }


/*
  rc - decrement reference counter
//*/
void RCObject::removeReference()
{
  if (--refCount == 0)
    delete this;
}


/*
  shareable flag - set to false
//*/
void RCObject::markUnshareable() { shareable = false; }


/*
  shareable flag - set true
//*/
bool RCObject::isShareable() const { return shareable; }


/*
  shareable flag - ask
//*/
bool RCObject::isShared() const { return refCount > 1; }
