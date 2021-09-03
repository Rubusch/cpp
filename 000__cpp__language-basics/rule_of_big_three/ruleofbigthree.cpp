// ruleofthree.cpp
/*
  rule of three

  1. copy constructor - shallow copy (or deep copy)
  2. destructor
  3. operator= - deep copy (or shally copy)

  Important: doing a shallow copy on ALLOCATED pointers on members is
  dangerous!

  since the destructor should do a delete on all members, the
  destructor of the "shallow copy object" will fail, since the "first"
  member already deleted the memory and set its (the original
  object's) pointer to NULL. The pointer of the "shallow copy object"
  still points on somewhere, but there is no allocated memory anymore.

  The problem is:
  - the allocated memory will be deleted
  - the pointer will be set to NULL

  -> the pointer of the "shallow copy object" is NOT set to NULL, a
     delete sigsegv's

  A strategy is to check a pointer to the original.
//*/

#include <cstdlib> // exit()
#include <iostream>
#include <string>

using namespace std;


template < class T >
class Foobar
{
private:
  // to help the dtor with freeing memory in a shallow copy
  Foobar< T > *pShallowCpy;

  T *ptr; // NO const here!
  T data;


public:
  // normal ctor
  Foobar();

  // 1. copy ctor
  Foobar(Foobar const &shallowcopy);

  // 2. dtor
  ~Foobar();

  // 3. operator=
  Foobar &operator=(const Foobar &deepcopy);

  // some getters
  void setPointer(const T &pointer);
  const T &getPointer() const;
  void setData(const T &newData);
  T getData() const;
  void initPointerToShallowCopy(
      Foobar< T > *copy) const; // needs to be const on object!
};


template < class T >
Foobar< T >::Foobar() : pShallowCpy(NULL), ptr(NULL)
{
  try {
    ptr = new T();
  } catch (...) {
    cerr << "ERROR: allocation failed!";
    delete ptr;
    ptr = NULL;
    exit(-1);
  }

  // ptr is allocated but uninitialized!
}


/*
  copy ctor - shallow copy (pointer still point to the same pointee)
//*/
template < class T >
Foobar< T >::Foobar(Foobar< T > const &shallowcopy)
    : ptr(NULL), data(shallowcopy.getData()) // copy of fix data
{
  // not needed to check self in the ctor, 'shallowcopy' cannot be passed to
  // it's own ctor - Exceptional C++, Herb Sutter, 2000
  // if(this == &shallowcopy) return;

  // copy of pointer(s) - shallow copy -> no allocation!
  ptr = shallowcopy.ptr;

  // set pShallowCpy of "original object" to this
  shallowcopy.initPointerToShallowCopy(this);
}


/*
  dtor
//*/
template < class T >
Foobar< T >::~Foobar()
{
  if (NULL != pShallowCpy) {
    /*
      if there exist a shallow copy don't delete the pointer here, the
    destructor of the shallowcopy will do that, this serves to avoid a
    double-delete situation
    //*/
    return;
  }

  delete ptr;
  ptr = NULL;
}


/*
  operator= - deep copy new space has been allocated
//*/
template < class T >
Foobar< T > &Foobar< T >::operator=(const Foobar< T > &deepcopy)
{
  // check self
  if (this == &deepcopy)
    return *this;

  // deepcopy.data
  data = deepcopy.data;

  // deepcopy.ptr - can be checked for NULL, in case!
  T *tmp = NULL;
  if (NULL != deepcopy.ptr) {
    try {
      tmp = new T();
    } catch (...) {
      cerr << "allocation failed\n";
      delete tmp;
      tmp = NULL;
      exit(-1);
    }
    *tmp = deepcopy.getPointer();
  }
  delete ptr;
  ptr = tmp;

  return *this;
}

template < class T >
void Foobar< T >::setPointer(const T &content)
{
  *ptr = content;
}

template < class T >
const T &Foobar< T >::getPointer() const
{
  return *ptr;
}

template < class T >
void Foobar< T >::setData(const T &newData)
{
  data = newData;
}

template < class T >
T Foobar< T >::getData() const
{
  return data;
}

template < class T >
void Foobar< T >::initPointerToShallowCopy(Foobar< T > *copy) const
{
  /*
    Because this function is called by the copy ctor's parameter and this needs
  to be passed as "const" object:
    1. this function needs to be "const"
    2. since we still need to change a contained data, we discard constness for
    this operation by a const_cast<>()
  //*/
  (const_cast< Foobar< T > * >(this))->pShallowCpy = copy;
}


/*
  some main
//*/
int main()
{
  Foobar< string > fb_orig;


  // init
  cout << "1. init original\n";

  string s1 = "data";
  fb_orig.setData(s1);

  string s2 = "pointer";
  fb_orig.setPointer(s2);

  cout << "fb_orig\n"
       << "\t::data\t\t=\t\"" << fb_orig.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_orig.getPointer() << "\"\n";
  cout << endl;
  cout << endl;
  cout << endl;


  // shallow copy
  cout << "2. shallow copy\n";
  Foobar< string > fb_shallow_copy(fb_orig);
  // this also shows why it makes more sense to use operator=() for the deep
  // copy!
  cout << "fb_orig\n"
       << "\t::data\t\t=\t\"" << fb_orig.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_orig.getPointer() << "\"\n";
  cout << endl;

  cout << "fb_shallow_copy\n"
       << "\t::data\t\t=\t\"" << fb_shallow_copy.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_shallow_copy.getPointer() << "\"\n";
  cout << endl;
  cout << endl;
  cout << endl;


  // deep copy
  cout << "3. deep copy\n";
  Foobar< string > fb_deep_copy;
  fb_deep_copy = fb_orig;

  cout << "fb_orig\n"
       << "\t::data\t\t=\t\"" << fb_orig.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_orig.getPointer() << "\"\n";
  cout << endl;

  cout << "fb_deep_copy\n"
       << "\t::data\t\t=\t\"" << fb_deep_copy.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_deep_copy.getPointer() << "\"\n";
  cout << endl;
  cout << endl;
  cout << endl;


  // change original
  cout << "4. now changing the fb_orig and checking the output of the copies\n";

  fb_orig.setData("new data");
  string s4 = "new pointer";
  fb_orig.setPointer(s4);

  cout << "fb_orig\n"
       << "\t::data\t\t=\t\"" << fb_orig.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_orig.getPointer() << "\"\n";
  cout << endl;

  cout << "fb_shallow_copy\t\t\t// common values have changed!\n"
       << "\t::data\t\t=\t\"" << fb_shallow_copy.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_shallow_copy.getPointer() << "\"\n";
  cout << endl;

  cout << "fb_deep_copy\t\t\t// should be the same: autonomous copy!\n"
       << "\t::data\t\t=\t\"" << fb_deep_copy.getData() << "\"\n"
       << "\t::pointer\t=\t\"" << fb_deep_copy.getPointer() << "\"\n";
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
