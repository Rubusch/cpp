// Main.cpp
/*
  Demonstrates the use of a templatemethod in a template class.
  
  Default template arguments
  
  Don't ever do ">>" when "> >" is meant!
//*/

#include <iostream>
#include <string>
using namespace std;

template< class X >
class Templateclass
{
private:
    X x;

public:
    Templateclass(X var)
    {
        x = var;
    };

    void output()
    {
        cout << "Templateclass::" << x;
    };
};


// needs not to be another templateclass
template< class T, class C=Templateclass<string> >
class Someclass
{
public:
    Someclass()
    {
        cout << "Someclass::ctor()" << endl;
    };
    
    void output(T t, C c)
    {
        cout << "t = ";
        t.output();
        cout << endl;
        cout << "c = ";
        c.output();
        cout << endl;
        /*
          If I'd like to do something like:
          cout << t.output() << endl;
          I'll have to overload the operator<<()
          [and to modify the output() method].
        //*/  
    };
};


int main()
{
    Templateclass<string> t("Object");
    Someclass< Templateclass<string> > s1;
    s1.output(t, t);
    cout << endl;
    
    Someclass< Templateclass<string>, Templateclass<string> > s2;
    s2.output(t, t);    

    return 0;
};
