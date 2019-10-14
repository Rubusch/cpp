// rcobject.hpp
/*******************************************************************************
 *                       Class RCObject (from pp. 204-205)                     *
 *******************************************************************************

annotations:

  base class for reference counted objects - this class contains the reference
  counter and the shareable flag!
*/


#ifndef RC_OBJECT
#define RC_OBJECT


class RCObject
{
public:
  // reference counter
  void addReference();
  void removeReference();

  // shareable flag
  void markUnshareable();
  bool isShareable() const;
  bool isShared() const;

protected:
  // ctor
  RCObject();

  // copy ctor
  RCObject(const RCObject &rhs);

  // ob=
  RCObject &operator=(const RCObject &rhs);

  // dtor
  virtual ~RCObject() = 0;

private:
  // the reference counting variable!
  int refCount;

  // shareable flag - common data in rc structure is shared?
  bool shareable;
};

#endif
