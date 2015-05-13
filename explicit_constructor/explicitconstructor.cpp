// explicitconstructor.cpp
/*
  Constructors can be declared explicit, and if they are, compilers are prohibited from invoking 
  them for purposes of implicit type conversion. Explicit conversions are still legal, however.

  further demonstrates a simple checked input conversion from string to int
//*/


#include <iostream>


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

ContainerType::ContainerType(int val)
{
  value = val;
}

int ContainerType::getVal() const
{
  return value;
}



/*
  some user
//*/
void useContainer(const ContainerType& ct)
{
  std::cout << "\tthe stored value is: " << ct.getVal() << std::endl;
}



/*
  some main
//*/
int main()
{
  // error, implicit type conversion
  std::cout << "1. implicit type conversion - doesn't work anymore due to \"explicit\" declaration of ctor" << std::endl;
  // this compiles without the "explicit" declaration - implicit type conversion:
  //useContainer(123); 

  std::cout << "FAILED - (but OK!)" << std::endl;
  std::cout << std::endl;


  // ok, explicit type conversion
  std::cout << "2. explicit type conversion works with \"explicit\" declaration" << std::endl;
  useContainer(ContainerType(123));
  std::cout << std::endl;

  
  // bad! syntax ok, but wrong logic
  /*
    Caution: in case using a cast on a template, e.g. static_cast< Foobar<int>>( ... ) - will be 
    read as operator >> !!!
  //*/ 
  std::cout << "3. explicit type conversion - static cast (bad, wrong logic)" << std::endl;
  useContainer( static_cast<ContainerType>(123)) ;
  std::cout << std::endl;


  // bad! syntax ok, but C cast
  std::cout << "4. explicit type conversion - C cast (bad, too)" << std::endl;
  useContainer( (ContainerType) 123);
  std::cout << std::endl;


  std::cout << "READY.\n";
  return 0;
}

