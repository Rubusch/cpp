// Main.cpp
/*
  Inheritance and abstract base class

  Only one pure virtual function is enough to make a class abstract.

  Use Virtual Functions for functions to be overwritten (dynamic binding).

  Without "virtual" you have static binding with some side effects at
  overwriting a method.
//*/

#include <iostream>
#include <string>
using namespace std;


class Bird;
class Pinguin;
class Vulture;
class Eagle;


class Bird
{
public:
    void name()
    {
        cout << "Bird";
    };
    virtual void sound()
    {
        cout << "nothing";
    };
    // pure virtual function - makes the class abstract
    virtual void fly()=0;
};


class Pinguin:public Bird
{
public:
    void name()
    {
        cout << "Pinguin";
    };
    void sound() // virtual in base
    {
        cout << "blob";
    };
    void fly() // pure virtual in base
    {
        cout << "swims";
    };
};


class Vulture
    :public Bird
{
public:
    void name()
    {
        cout << "Vulture";
    };
    void sound() // virtual in base
    {
        Bird::sound();
    };
    void fly() // pure virtual in base
    {
        cout << "flies";
    };
};


class Eagle
    :public Bird
{
public:
    void name()
    {
        cout << "Eagle";
    };
    void sound() // virtual in base
    {
        cout << "aaaaa";
    };
    void fly() // pure virtual in base
    {
        cout << "flies";
    };
};


int main()
{
    Pinguin *p = new Pinguin();
    cout << "The ";
    p->name();
    cout << ' ';
    p->fly();
    cout << " and says: ";
    p->sound();
    cout << '.' << endl;

    Vulture *v = new Vulture();
    cout << "The ";
    v->name();
    cout << ' ';
    v->fly();
    cout << " and says: ";
    v->sound();
    cout << '.' << endl;

    Eagle *e = new Eagle();
    cout << "The ";
    e->name();
    cout << ' ';
    e->fly();
    cout << " and says: ";
    e->sound();
    cout << '.' << endl;

    delete p;
    delete v;
    delete e;

    return 0;
};
