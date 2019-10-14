// explicitconstructor.cpp
/*
  Constructors can be declared explicit

  if they are, compilers are prohibited from invoking them for purposes of
  implicit type conversion. Explicit conversions are still legal, however.

  further demonstrates a simple checked input conversion from string to int
//*/


#include <iostream>

using namespace std;


/*
  some element type
//*/
class ContainerType
{
protected:
  int value;

public:
  // ctor
  explicit ContainerType(int val);

  // function
  int getVal() const;
};

ContainerType::ContainerType(int val) { value = val; }

int ContainerType::getVal() const { return value; }


/*
  some user
//*/
void useContainer(const ContainerType &ct)
{
  cout << "\tthe stored value is: " << ct.getVal() << endl;
}


/*
  some main
//*/
int main()
{
  // error, implicit type conversion
  cout << "1. implicit type conversion - doesn't work anymore due to "
          "\"explicit\" declaration of ctor"
       << endl;
  // this compiles without the "explicit" declaration - implicit type
  // conversion:
  // useContainer(123); // uncomment: FAILS to compile!

  cout << "FAILED - (but OK!)" << endl;
  cout << endl;


  // ok, explicit type conversion
  cout << "2. explicit type conversion works with \"explicit\" declaration"
       << endl;
  useContainer(ContainerType(123));
  cout << endl;


  // bad! syntax ok, but wrong logic
  /*
    Caution: in case using a cast on a template, e.g. static_cast< Foobar<int>>(
  ... ) - will be read as operator >> !!!
  //*/
  cout << "3. explicit type conversion - static cast (bad, wrong logic)"
       << endl;
  useContainer(static_cast< ContainerType >(123));
  cout << endl;


  // bad! syntax ok, but C cast
  cout << "4. explicit type conversion - C cast (bad, too)" << endl;
  useContainer(( ContainerType )123);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
