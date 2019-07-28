// lazyfetching.cpp
/*
  The lazy approach to this problem is to read no data from disk when a
  HugeMonster object is created. Instead, only the "shell" of an object
  is created, and data is retrieved from the database only when that
  particular data is needed inside the object.
  (More Effective C++ / 17 / Meyers)

  Huge initialization lists and huge overhead with many pointers makes it
  difficult for larger classes. The better alternative is the usage of a
  smartpointer that keeps track of that directly!
//*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template<class T>
class HugeMonster;

template<class T>
ostream& operator<<(ostream& out, HugeMonster<T>& hm);

/*
  values that are difficult to fetch ;)
//*/
// monster 1
string someMonsterString = "some monster string!";

// monster 2
int someMonsterInt = 111;

/*
  some class def for monster 3 and 4
//*/
template<class T>
class HugeMonster
{
private:
  T var;

public:
  HugeMonster();
  HugeMonster(const T initVar);

  T getVariable() const;
  HugeMonster& operator=(const HugeMonster<T>& d_cpy);

  //  friend ostream& operator<< <T>(ostream& out, HugeMonster<T>& hm);
};

template<class T>
HugeMonster<T>::HugeMonster()
{}

template<class T>
HugeMonster<T>::HugeMonster(const T initVar)
{
  var = initVar;
}

template<class T>
T HugeMonster<T>::getVariable() const
{
  return var;
}

template<class T>
HugeMonster<T>& HugeMonster<T>::operator=(const HugeMonster<T>& d_cpy)
{
  if(this == &d_cpy) return *this;
  this->var = d_cpy.getVariable();
  return *this;
}

// friend function operator<<()
template<class T>
ostream& operator<<(ostream& out, HugeMonster<T>& hm)
{
  return out << hm.getVariable();
}

// monster 3
HugeMonster<string> stringMonster("the string monster!");

// monster 4
HugeMonster<int> intMonster(222);



/*
  the class - a cage of huuuuuge monsters, hence the elemens will be allocated and
  initialized only when requested!
//*/
template<class U, class V>
class MonsterCage
{
private:
  mutable string *field1value;
  mutable int *field2value;
  mutable U *field3value;
  mutable V *field4value;
  // ...

public:
  MonsterCage();
  ~MonsterCage();

  /*
    the initialization can be done automagically by the class
    when it's necessary!
  //*/

  const string& field1() const;
  int field2() const;
  U field3() const;
  const V& field4() const;
  // ...
};

/*
  trick: lazy fetching - initialize everything here with NULL
//*/
template<class U, class V>
MonsterCage<U, V>::MonsterCage()
  :field1value(NULL), field2value(NULL), field3value(NULL), field4value(NULL)
{}

template<class U, class V>
MonsterCage<U, V>::~MonsterCage()
{
  delete field1value; field1value = NULL;
  delete field2value; field2value = NULL;
  delete field3value; field3value = NULL;
  delete field4value; field4value = NULL;
}

template<class U, class V>
const string& MonsterCage<U, V>::field1() const
{
  if(0 == field1value){
    // allocate space for the value
    try{
      field1value = new string;
    }catch(...){
      cerr << "allocation 1 failed\n";
      exit(-1);
    }

    // read out correct value and init the attribute
    // (here only init with some global value)
    *field1value = someMonsterString;
  }

  // return the value (here a const reference)
  return *field1value;
}


template<class U, class V>
int MonsterCage<U, V>::field2() const
{
  if(0 == field2value){
    try{
      field2value = new int;
    }catch(...){
      cerr << "allocation 2 failed\n";
      exit(-1);
    }

    *field2value = someMonsterInt;
  }

  return *field2value;
}


template<class U, class V>
U MonsterCage<U, V>::field3() const
{
  if(NULL == field3value){
    try{
      field3value = new U;
    }catch(...){
      cerr << "allocation 3 failed\n";
      exit(-1);
    }

    *field3value = stringMonster;
  }

  return *field3value;
}


template<class U, class V>
const V& MonsterCage<U, V>::field4() const
{
  if(NULL == field4value){
    try{
      field4value = new V;
    }catch(...){
      cerr << "allocation 4 failed\n";
      exit(-1);
    }

    *field4value = intMonster;
  }

  return *field4value;
}



/*
  some main to test
//*/
int main()
{
  // init
  cout << "init the cage of huge objects\n";
  MonsterCage< HugeMonster<string>, HugeMonster<int> > cage;

  // ...
  cout << "...\n";

  // get the values
  cout << "now request the values:\n";
  cout << "1. value:\t\"" << cage.field1() << "\"\n";

  cout << "2. value:\t\"" << cage.field2() << "\"\n";

  HugeMonster<string> tmp_str = cage.field3();
  cout << "3. value:\t\"" << tmp_str << "\"\n";

  HugeMonster<int> tmp_int = cage.field4();
  cout << "4. value:\t\"" << tmp_int << "\"\n";

  // done
  cout << "READY.\n";
  return 0;
}
