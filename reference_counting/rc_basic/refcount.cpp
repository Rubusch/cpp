// refcount.cpp
/*
  Simple demonstration of reference counting   (More Effective C++ / 29 / Meyers)

  Referenece counting is often knwon as a garbage collection algorithm where each object 
  contains a count of the number of references to it held by other objects. If an object's 
  reference count reaches zero, the object has become inaccessible, and it is put on a 
  list of objects to e destroyed (e.g. when using a garbage collection mechanism or e.g. 
  a freelist).

  Referenc counting can increase the performance due to working with references being 
  quick.

  - Weighted Reference Counts are a good solution for garbage collecting a distributed 
  system.

  - Indirect Reference Counting (e.g. in the Dijkstra-Scholten algorithm), prevents an 
  object from being discarded prematurely.

  [en.wikipedia.org]
//*/

#include <iostream>
#include <string>


// forward declarations
template<class T>
class SomeClass;

template<class T>
std::ostream& operator<<(std::ostream& out, SomeClass<T>& obj);


/****************************************************************************/


template<class T>
class SomeClass
{
public:
  // ctor
  SomeClass(const T initValue = "");

  // cpy ctor
  SomeClass(const SomeClass<T>& shallowcopy);

  // dtor
  ~SomeClass();

  // operator=
  SomeClass<T>& operator=(const SomeClass<T>& deepcopy);

  // accessibility for output
  friend
  std::ostream& operator<< <T>(std::ostream& out, SomeClass<T>& obj);

private:
  struct SomeValue{

    // the referece couter
    int refCount;

    // some additional data
    T* data;

    // ctor - refcount
    SomeValue(const T initValue);

    // dtor - refcount
    ~SomeValue();
  };

  // ptr to the refCnt data
  SomeValue* value;
};


/****************************************************************************/


/*
  ctor
//*/
template<class T>
SomeClass<T>::SomeClass(const T initValue)
  : value(new SomeValue(initValue))
{}


/*
  cpy ctor
//*/
template<class T>
SomeClass<T>::SomeClass(const SomeClass<T>& shallowcopy)
  : value(shallowcopy.value)
{
  ++value->refCount;
}


/*
  dtor
//*/
template<class T>
SomeClass<T>::~SomeClass()
{
  std::cout << "~SomeClass()\n"; 

  if(--value->refCount == 0) delete value;
}


/*
  operator=
//*/
template<class T>
SomeClass<T>& SomeClass<T>::operator=(const SomeClass<T>& deepcopy)
{
  if(value == deepcopy.value){
    return *this;
  }

  if(--value->refCount == 0){
    delete value;
  }
  
  value = deepcopy.value;
  ++value->refCount;

  return *this;
}


/*
  output of class contents..
//*/
template<class T>
std::ostream& operator<<(std::ostream& out, SomeClass<T>& obj)
{
  return out << "data: " << *((obj.value)->data) << ", refCount: " << (obj.value)->refCount;
}


/****************************************************************************/


/*
  ref count - ctor

  ...or do alternatively:
  data = new T(initValue); 
//*/
template<class T>
SomeClass<T>::SomeValue::SomeValue(const T initValue)
  : refCount(1)
{
  data = new T; 
  *data = initValue;
}


/*
  ref count - dtor
//*/
template<class T>
SomeClass<T>::SomeValue::~SomeValue()
{
  std::cout << "~SomeValue()\n"; 

  delete data;
}


/****************************************************************************/


/*
  some main
//*/
int main()
{
  // init
  std::cout << "init obj_1\n";
  SomeClass<std::string> obj_1("Some reference counted class!");

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << std::endl;

  // operator= test
  std::cout << "deep copy to obj_2\n";
  SomeClass<std::string> obj_2 = obj_1;

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << "obj_2: " << obj_2 << std::endl;
  std::cout << std::endl;

  // cpy ctor test
  std::cout << "shallow copy to obj_3\n";
  SomeClass<std::string> obj_3(obj_1);

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << "obj_2: " << obj_2 << std::endl;
  std::cout << "obj_3: " << obj_3 << std::endl;
  std::cout << std::endl;

  // done
  std::cout << "READY.\n";
  return 0;
}
