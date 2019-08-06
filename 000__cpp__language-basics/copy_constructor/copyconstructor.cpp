// copy_constructor.cpp
/*
  demonstrates a copy constructor - cpy ctor

  Use the copy constructor especially for classes with dynamically allocated memory!

  (11/Meyers)
//*/

#include <iostream>

using namespace std;


class Base
{
private:
  string data_;

public:
  Base() : data_("") {}

  Base( Base const& cpy)
  {
    data_ = cpy.data_;
  }

  void setData(string data)
  {
    data_ = data;
  }

  string getData()
  {
    return data_;
  }
};


template<class T>
class MyClass
  : public Base
{
private:
  T value;
  const T *pointer;

public:
  // constructor
  MyClass();


  // copy constructor
  MyClass(const MyClass<T>& shallowcopy);


  // destructor
  // - if the class would have a virtual function, the destructor should be virtual, too
  // - a class that has member pointers, should have an self implemented destructor
  // - delete should happen where the allocation has happened -> no allocation, no delete!
  ~MyClass();


  void setValue(const T val);
  T getValue() const;
  void setPointer(const T* ptr);
  const T* getPointer() const;
};


template<class T>
MyClass<T>::MyClass()
  :value(0), pointer(NULL) // init
{}


/*
  copy constructor - shallow copy

  The copy constructor is a special function:
  Doesn't matter if these were declared "private" or "protected" - the access within
  the copy constructor works like a friend declared function!! Everything's "public"
  here!
//*/
template<class T>
MyClass<T>::MyClass(MyClass<T> const& shallowcopy)
  : Base(shallowcopy), value(shallowcopy.value)
{
  // check self?
  if(this == &shallowcopy) return;

  // pointer
  setPointer(shallowcopy.pointer);
}


template<class T>
MyClass<T>::~MyClass()
{}


template<class T>
void MyClass<T>::setValue(const T val)
{
  value = val;
}


template<class T>
T MyClass<T>::getValue() const
{
  return value;
}


template<class T>
void MyClass<T>::setPointer(const T* ptr)
{
  pointer = ptr;
}


template<class T>
const T* MyClass<T>::getPointer() const
{
  return pointer;
}




/*
  some main
//*/
int main()
{
  MyClass<int> a;

  int value = 123;
  int *pointer = &value;

  // init
  a.setValue(value);
  a.setPointer(pointer);
  a.setData("base data");

  // output
  cout << "content in a: " << a.getValue() << ", \'" << *(a.getPointer()) << "\' and \'" << a.getData() << "\'" << endl;

  // copy
  MyClass<int> b(a);

  // output
  cout << "content in b: " << b.getValue() << ", \'" << *(b.getPointer()) << "\' and \'" << b.getData() << "\'" << endl;
  //*/

  cout << "READY.\n";
  return 0;
}
