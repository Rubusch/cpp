// norefonlocals.cpp
/*
  don't return references on local elements
//*/

#include <iostream>
#include <string>

using namespace std;


template<class T>
class Foobar
{
private:
  T localdata;

public:
  Foobar(T data);

  T getLocalData();
  T& getRefOnLocalData();
  const T& getConstRefOnLocalData() const;
};

template<class T>
Foobar<T>::Foobar(T data)
  : localdata(data)
{}

template<class T>
T Foobar<T>::getLocalData()
{
  return localdata;
}

template<class T>
T& Foobar<T>::getRefOnLocalData()
{
  return localdata;
}

template<class T>
const T& Foobar<T>::getConstRefOnLocalData() const
{
  return localdata;
}


void state(const Foobar<string>& fb, const string& local, const string& tempLocal, const string& refOnLocal)
{
  /*
    4/4

    therefore when it is necessary to pass a reference to a local memeber of an object,
    this shall happen only as "const reference"!!
  //*/
  cout << "fb"
       << "\t::localdata\t= \"" << fb.getConstRefOnLocalData() << "\"\n\n"
       << "\tmy local\t= \"" << local << "\"\n\n"
       << "\ttemp local\t= \"" << tempLocal << "\"\n\n"
       << "\trefOnLocal\t= \"" << refOnLocal << "\"\n";
}

int main()
{
  // init
  cout << "init\n";
  Foobar<string> fb("Hello World!");

  /*
    1/4

    only pLocal needs memory allocation
  //*/
  string *pLocal = new string;
  *pLocal = fb.getLocalData();

  /*
    2/4

    here the by-value passed temporary variable is used to set the pointer
    this usually should throw a WARNING, since this is usually not what we
    want (an internal temporary variable)
  //*/
  string *pTempLocal;
  pTempLocal = &(fb.getLocalData()); // THIS SHOULD GIVE A WARNING!!!

  /*
    3/4

    to avoid the above warning we can init the pointer with a reference on
    the internal member variable of the object - this doesn't emit a warning
    but it is very bad programming. The class mechanisms, inclusive destructors,
    etc can behave strangely on the now possible changes from outside!
  //*/
  string *pRefOnLocal;
  pRefOnLocal = &(fb.getRefOnLocalData());

  state(fb, *pLocal, *pTempLocal, *pRefOnLocal);
  cout << endl;

  /* ------------------------------------------------------------------------- */

  /*
    reinit "local"

    this is the way to do it in most cases - only the local pointer will change the
    content of its own allocated memory
  //*/
  cout << "reinit of locally received data from object\n";
  *pLocal = "reset my local";
  state(fb, *pLocal, *pTempLocal, *pRefOnLocal);
  cout << endl;


  /*
    reinit "tempLocal"

    a WARNING was already thrown at compile time, the here changed variable is a
    temporary reference to the internal object's member variable. This is
    dangerous as will be visible in the next step.
  //*/
  cout << "reinit a temp value of localdata\n";
  *pTempLocal = "reset local";
  state(fb, *pLocal, *pTempLocal, *pRefOnLocal);
  cout << endl;


  /*
    reinit "refOnLocal"

    changing the reference directly - when the internal class'es member changes
    its value the temporary reference looses validity!!

    changing internal members directly via references from outside is dangerous,
    though, there is no mechanism to to necessary adaptions for the class.

    -> try to access class members via getters / setters
    -> try to avoid references to local member variables / pointers
    -> if you need to pass references to local members, pass them as const!
  //*/
  cout << "reinit of reference on local\n";
  *pRefOnLocal = "reset on reference on local";
  state(fb, *pLocal, *pTempLocal, *pRefOnLocal);
  cout << endl;


  cout << "READY.\n";
  delete pLocal;
  return 0;
}
