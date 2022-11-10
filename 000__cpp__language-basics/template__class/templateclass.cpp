// Main.cpp
/*
  Template works for the entire class

  1. Other class wide declared class variables should be defined in a
     initialisation list (or be passed).

  2. So far it's not possible to separate a template class into .cpp
     and .h file with the same template.

     The declaration put all in one .h file, or write an .impl file
     https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file



     A typical pattern is

     - Abstract class uses templates and template implementations all
       in .h

     - Derrived concrete class is NOT a template class, but sets the
       parent template, separated into .cpp and .h

     - The user of the derrived concrete class instanciates directly,
       separation of the user class into .cpp and .h
*/

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
