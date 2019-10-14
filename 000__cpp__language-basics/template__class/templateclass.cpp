// Main.cpp
/*
  Template works for the whole class.

  1. other class wide declared class variables should be
  defined in a initialisation list (or be passed).

  2. so far it's not possible to separate .cpp and .h file
  with the same template.
  declaration (put all in one .h file, or write an .impl file).
//*/

#include <iostream>
#include <string>

using namespace std;


class Anotherclass
{
public:
  Anotherclass(string sz) { cout << sz << endl; };
};


class Anextclass
{
public:
  Anextclass(string sz) { cout << sz << endl; };
};


template < class T >
class Someclass
{
private:
  T var1;
  int var2;
  Anotherclass A;
  Anextclass B;

public:
  Someclass(T variable1, int variable2) : A("another class"), B("a next class")
  {
    var1 = variable1;
    var2 = variable2;
  };

  void output()
  {
    cout << "var1 = " << var1 << endl;
    cout << "var2 = " << var2 << endl;
  };
};


int main()
{
  int *pointer = new int(15);
  Someclass< int > s(5, 10);
  s.output();

  return 0;
};
