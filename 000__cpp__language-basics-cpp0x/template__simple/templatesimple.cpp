// templates.cpp
/*
//*/

#include <iostream>

using namespace std;


template<class T>
class MyClass
{
private:
  T variable;

public:
  // ctor
  MyClass<T>();

  void setVariable(T var);
  T getVariable();
};


template<class T>
MyClass<T>::MyClass()
{}

template<class T>
void MyClass<T>::setVariable(T var)
{
  variable = var;
}

template<class T>
T MyClass<T>::getVariable()
{
  return variable;
}


/*
  some main
//*/
int main()
{
  MyClass<int> c;

  // input
  cout << "set value" << endl;
  c.setVariable(77);

  // output
  cout << "get value: " << c.getVariable() << endl;

  cout << "READY.\n";
  return 0;
}

