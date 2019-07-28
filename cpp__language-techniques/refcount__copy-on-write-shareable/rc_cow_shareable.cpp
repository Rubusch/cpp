// rc_cow_shareable.cpp
/*
  Copy-on-write mechanism using a shareable flag, following the example of Scott Meyers.

  To show the effect compile with shared flag turned on (comment the define out) or turned off.

  (More Effective C++ / 29 / Meyers)
//*/

#include <iostream>
#include <cstring> // strlen(), strncpy()
#include <string>

/*
  -> ACTIVATE OR DEACTIVATE THE SHAREABLE FLAG!!!

  THIS TURNS REFERENCE COUNTING ON OR OFF, OR GIVES
  ACCESS TO THE SHARED DATA OR NOT, RESPECTIVELY.
//*/
#define DON_T_SHARE


// forward declarations
class SomeClass;

std::ostream& operator<<(std::ostream& out, SomeClass& obj);


/****************************************************************************/


class SomeClass
{
public:
  // ctor/dtor
  SomeClass(const char* initValue = "", const std::string initPrivatedata = "*** pending private data ***");
  SomeClass(const SomeClass& shallowcopy);
  ~SomeClass();
  SomeClass& operator=(const SomeClass& deepcopy);

  // copy-on-write stuff
  const char& operator[](int index) const;
  char& operator[](int index);

  // accessibility for output
  void copyonwrite(const char* newcontent, const unsigned int newcontent_siz);
  void setshareable(bool isShareable);

  friend
  std::ostream& operator<<(std::ostream& out, SomeClass& obj);

private:
  std::string privatedata;

  struct SomeValue{
    int refCount;
    char* data;

    bool shareable; // new shareable flag

    // ctor, dtor - refcount
    SomeValue(const char* initValue);
    ~SomeValue();
  };

  // ptr to the value struct
  SomeValue* value;
};


/****************************************************************************/


/*
  ctor
//*/
SomeClass::SomeClass(const char* initValue, const std::string initPrivatedata)
  : privatedata(initPrivatedata)
    , value(new SomeValue(initValue))
{}


/*
  cpy ctor
//*/
SomeClass::SomeClass(const SomeClass& shallowcopy)
{
  if(shallowcopy.value->shareable){
    value = shallowcopy.value;
    privatedata = "copy constructor object - name pending"; // just for debugging
    ++value->refCount;

  }else{
    value = new SomeValue(shallowcopy.value->data);
  }
}


/*
  dtor
//*/
SomeClass::~SomeClass()
{
  std::cout << "DTOR\t~SomeClass()\n";

  if(--value->refCount == 0) delete value;
}


/*
  operator=
//*/
SomeClass& SomeClass::operator=(const SomeClass& deepcopy)
{
  if(value == deepcopy.value){
    return *this;
  }

  if(--value->refCount == 0){
    delete value;
  }

  value = deepcopy.value;
  ++value->refCount;

  privatedata = "operator= object - name pending"; // just for debugging

  return *this;
}


/****************************************************************************/


/*
  operator[] - copy-on-write, for const objects
//*/
const char& SomeClass::operator[](int index) const
{
  return value->data[index];
}


/*
  operator[] - copy-on-write for non-const objects
//*/
char& SomeClass::operator[](int index)
{
  // if we're sharing a value with other SomeClass objects,
  // break off a separate copy of the value for ourselves
  if(value->refCount > 1){
    --value->refCount;
    // decrement current value's refCount, because we won't be
    // using that value any more

    value = new SomeValue(value->data);
    // make a copy of the value for ourselves
  }

  // new shareable support
  value->shareable = false;

  // return a referene to a character inside our unshared SomeClass object
  return value->data[index];
}


/****************************************************************************/


/*
  acessibility
//*/
void SomeClass::copyonwrite(const char* newcontent, const unsigned int newcontent_siz)
{
  // in case free old one
  if(!value->data) delete [] value->data;

  // allocate new one
  value->data = new char[newcontent_siz];

  // copy on write (in case might be better to show this working with the op[] from outside
  for(unsigned int idx=0; idx < newcontent_siz; ++idx){
    value->data[idx] = newcontent[idx];
  }
}


/*
  set the shareable flag
//*/
void SomeClass::setshareable(bool isShareable)
{
  value->shareable = isShareable;
}


/*
  output of class contents..
//*/
std::ostream& operator<<(std::ostream& out, SomeClass& obj)
{
  return out << "\tname: \"" << obj.privatedata << "\"" << "\n\tdata: " << (obj.value)->data << "\n\trefCount: " << (obj.value)->refCount << std::endl;
}


/****************************************************************************/


/*
  ref count - ctor

  ...or do alternatively:
  data = new T(initValue);
//*/
SomeClass::SomeValue::SomeValue(const char* initValue)
  : refCount(1)
    , shareable(true) // init of the new shareable flag
{
  int initValueSize = strlen(initValue) + 1;
  data = new char[initValueSize]; // strlen returns length, without '\0'
  strncpy(data, initValue, initValueSize);
}


/*
  ref count - dtor
//*/
SomeClass::SomeValue::~SomeValue()
{
  std::cout << "DTOR\tSomeClass::~SomeValue()\n";

  delete [] data;
}


/****************************************************************************/


/*
  some main
//*/
int main()
{
  std::string initstring = "reference counter data";

  // init
  std::cout << "init obj_1\n";
  SomeClass obj_1(initstring.c_str(), "obj_1");

#ifdef DON_T_SHARE
  obj_1.setshareable(false); // comment out or compile with this line
#endif

  // output
  std::cout << obj_1 << std::endl;
  std::cout << std::endl;

  // operator= test
  std::cout << "deep copy to obj_2\n";
  SomeClass obj_2; // DON'T call obj_2() - that might be a declaration of a (new) function, not the ctor!
  obj_2 = obj_1;

  // output
  std::cout << obj_1 << std::endl;
  std::cout << obj_2 << std::endl;
  std::cout << std::endl;

  // cpy ctor test
  std::cout << "shallow copy to obj_3\n";
  SomeClass obj_3(obj_1);

  // output
  std::cout << obj_1 << std::endl;
  std::cout << obj_2 << std::endl;
  std::cout << obj_3 << std::endl;
  std::cout << std::endl;

  // change of obj_3
  /*
    we take a static array here to prove that the content will be copied,
    a delete value->data would fails, if *data would point on a static array
  //*/
  std::cout << "copy on write - rewrite the common data\n";
  char newarr[] = "*** new common data ***";
  obj_3.copyonwrite(newarr, strlen(newarr));

  // output
  std::cout << obj_1 << std::endl;
  std::cout << obj_2 << std::endl;
  std::cout << obj_3 << std::endl;
  std::cout << std::endl;

  // output by index
  std::cout << "output on indexes (copy on write - out):\n";
  for(unsigned int idx=0; idx <= initstring.length(); ++idx){
    std::cout << "obj_1[" << idx << "] \t= " << obj_1[idx] << "\n";
  }
  std::cout << std::endl;

  // done
  std::cout << "READY.\n";
  return 0;
}
