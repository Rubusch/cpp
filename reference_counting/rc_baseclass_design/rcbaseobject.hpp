// rcbaseobject.hpp
/*
  Base class for reference counted objects
//*/

#ifndef RC_BASE_OBJECT
#define RC_BASE_OBJECT

#include <iostream>

class RCBaseObject 
{
public:
  void addReference();
  void removeReference();
  void markUnshareable();
  bool isShareable() const;
  bool isShared() const;

protected:
  // ctor
  RCBaseObject();

  // copy ctor
  RCBaseObject(const RCBaseObject& rhs);

  // op=
  RCBaseObject& operator=(const RCBaseObject& rhs);

  // dtor
  virtual ~RCBaseObject() = 0;

private:
  int refCount;
  bool shareable;
};

#endif

