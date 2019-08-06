// type2type.cpp
/*
What's going on here?

By a call of one and the same function "createSomething()" with an argument of
type pointer to "GuineaPig", will be created two different instances. The
"GuineaPig" will be passed only as argument, no function of GuineaPig will be
called.


Problem statement:

"How can you specialize createSomething so that it treats GuineaPig differently
from all other types? An obvious solution is to make a separate
createSomething() function that copes with the particular case. Unfortunately,
now you don't have a uniform interface for creating GuineaPigs and objects
derived from GuineaPig. This renders createSomething unusable in any generic
code."

  template< class T, class U >
  T* createSomething(const U& arg)
  {
    return new T(arg);
  };

resources: Modern C++ Design, Alexandrescu

THIS IMPLEMENTATION WORKS OUT, BUT DOESN'T USE THE CODE - EXPLANATION MISSING
//*/


#include <iostream>


using namespace std;


// forward declaration
class GuineaPig;
class CommonMonster;
class FancyMonster;



/*
  The Type2Type Trick
//*/
template< typename T >
struct Type2Type
{
  // FIXME: SEEMS A BIT SENSELESS AND CAN ALSO BE COMMENTED OUT!
  typedef T OriginalType;
};



/*
fancy class in case of "FancyMonster"

FIXME:
THE IMPLEMENTATION HAVING AN ADDITIONAL PARAMETER, '-1', IN THE CONSTRUCTOR OF
'FANCYMONSTER' DOESN'T COMPILE. THE FOLLOWING IMPLEMENTATION DOESN'T USE THE
FUNCTION BELOW. IT WORKS OUT THOUGH, BUT THIS FUNCTION CAN BE COMMENTED OUT!


description of mapping function

Fancy case, it takes an instance of U as argument for the creation of specified
type object and returns that.
//*/
template< class U >
FancyMonster* createSomething(const U& arg, Type2Type<GuineaPig>)
{
  return new FancyMonster(arg);
}
//*/



/*
generalized implementation

"The second parameter of createSomething serves only to select the appropriate
overload. Now you can specialize createSomething for various instantiations of
Type2Type, which you map to various types in your application."


description of mapping function

Generalized case take one (or more) instance(s) of U as parameter for the
creation of an instance of type T and return that.
//*/
template<class T, class U>
T* createSomething(const U& arg, Type2Type<T>)
{
  return new T(arg);
}



/*
  the GuineaPig class
//*/
class GuineaPig
{
private:
  std::string str;

public:
  GuineaPig(const std::string& initStr);
  std::string queeek() const;
};

GuineaPig::GuineaPig(const std::string& initStr)
  : str(initStr){}

std::string GuineaPig::queeek() const
{
  return str;
}



/*
  common algorithm
//*/
class CommonMonster
{
private:
  const GuineaPig* gp;

public:
  CommonMonster( const GuineaPig* initGP);
  void askGuineaPigCommonly();
};

CommonMonster::CommonMonster( const GuineaPig* initGP)
  : gp(initGP){}

void CommonMonster::askGuineaPigCommonly()
{
  std::cout << "\tMapped to \'CommonMonster\'\n"
            << "\tAsk the Guinea Pig: \""
            << gp->queeek()
            << "\"\n";
}



/*
  fancy algorithm
//*/
class FancyMonster
{
private:
  const GuineaPig* gp;

public:
  FancyMonster( const GuineaPig* initGP);
  void askGuineaPigFancy();
};

FancyMonster::FancyMonster( const GuineaPig* initGP)
  : gp(initGP){}

void FancyMonster::askGuineaPigFancy()
{
  std::cout << "\tMapped to \'FancyMonster\'\n"
            << "\tAsk again: Oups.. the monster ate up the Guinea Pig!\n";
}


/*
  main..
//*/
int main()
{
  GuineaPig *gp = new GuineaPig("Queeeeeeeeeeek!");

  // algorithm 1:
  cout << "general case:" << endl;
  CommonMonster *pSm = createSomething(gp, Type2Type<CommonMonster>());
  pSm->askGuineaPigCommonly();
  cout << endl;

  // algorithm 2:
  cout << "special case:" << endl;
  FancyMonster *pAm = createSomething(gp, Type2Type<FancyMonster>());
  pAm->askGuineaPigFancy();
  std::cout << endl;

  cout << "READY.\n";
  delete pSm; pSm = NULL;
  delete pAm; pAm = NULL;
  delete gp; gp = NULL;

  return 0;

}
