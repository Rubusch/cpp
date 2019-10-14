// factorymethod.cpp
/*
  demonstrates the factory method pattern

  Define an interface for creating an object, but let the subclasses decide
  which class to instantiate. The factory method lets a class defer
  instantiation to its subclasses.

  In C++ this is realized through a protocol class (in java this would be an
  "Interface") and a static function, as also virtual functions to the content,
  to be implemented in the derived "real" instances.


                                               +---------------------+
                                               | Creator             |
                                               +=====================+
                                               |                     |
                                               +---------------------+
                                               | factoryMethod()     |
                                               |  : Product          |
                                               +---------------------+
                                                         /_\
                                                          |
                                                          |
                                                          |
  +---------------------+                      +---------------------+
  | Product             |                      | ConcreteCreator     |
  +=====================+                      +=====================+
  |                     |<- - - - - - - - - - -|                     |
  +---------------------+                      +---------------------+
  |                     |                      | facotryMethod()     |
  +---------------------+                      |  : Product          |
                                               +---------------------+
  (GoF, 1995)

//*/

#include <exception>
#include <iostream>
#include <string>

using namespace std;

/*
  forward delcalartions
//*/

template < class T >
class MonsterProtocol;

template < class T >
class RealMonster;

template < class T >
ostream &operator<<(ostream &out, MonsterProtocol< T > &rhs);

/*------------------------------------------------------------------------------*/

/*
  qualities - here these clases have to provide at least one mechanism that
  returns a string variable (since T already will be string we're on the safe
  side already ;-)
//*/
template < class T >
class Size_type
{
private:
  T size;

public:
  Size_type(T initSize) : size(initSize) {}

  T getSize() const { return size; }
};


template < class T >
class Color_type
{
private:
  T color;

public:
  Color_type(T initColor) : color(initColor) {}

  T getColor() const { return color; }
};


/*------------------------------------------------------------------------------*/


/*
  protocol class
//*/
template < class T >
class MonsterProtocol
{
private:
  // nothing

public:
  // dtor
  virtual ~MonsterProtocol(){};

  // content
  virtual string getName() const = 0;
  virtual string getSize() const = 0;
  virtual string getColor() const = 0;

  // exception class
  class BadMonsterException : public exception
  {
  private:
    string message;

  public:
    BadMonsterException(const string &msg) : message(msg) {}

    ~BadMonsterException() throw() {}

    const char *getMessage() const throw() { return message.c_str(); }
  };

  static MonsterProtocol< T > *factory(const T &name,
                                       const Size_type< T > &size,
                                       const Color_type< T > &color);

  friend ostream &operator<<< T >(ostream &out, MonsterProtocol< T > &rhs);
};


template < class T >
inline ostream &operator<<(ostream &out, MonsterProtocol< T > &rhs)
{
  return out << "name\t= " << rhs.getName() << "\nsize\t= " << rhs.getSize()
             << "\ncolor\t= " << rhs.getColor();
}


/*------------------------------------------------------------------------------*/


/*
  the actual factory method, implemented as "static" function in the protocol
class
//*/
template < class T >
MonsterProtocol< T > *
MonsterProtocol< T >::factory(const T &name, const Size_type< T > &size,
                              const Color_type< T > &color)
{
  return new RealMonster< T >(name, size, color);
  throw BadMonsterException("Allocation failed!");
}


/*------------------------------------------------------------------------------*/

template < class T >
class RealMonster : public MonsterProtocol< T >
{
private:
  T name_;
  Size_type< T > size_;
  Color_type< T > color_;

public:
  // ctor
  RealMonster(const T &name, const Size_type< T > &size,
              const Color_type< T > &color);

  // dtor
  virtual ~RealMonster() {}

  // content
  string getName() const;
  string getSize() const;
  string getColor() const;
};


template < class T >
RealMonster< T >::RealMonster(const T &name, const Size_type< T > &size,
                              const Color_type< T > &color)
    : name_(name), size_(size), color_(color)
{
}


template < class T >
string RealMonster< T >::getName() const
{
  return static_cast< string >(name_); // brute force ;)
}


template < class T >
string RealMonster< T >::getSize() const
{
  return size_.getSize();
}


template < class T >
string RealMonster< T >::getColor() const
{
  return color_.getColor();
}


/*------------------------------------------------------------------------------*/

/*
  some main
//*/
int main()
{
  cout << "1. Get a pointer to MonsterProtocol - the base..\n";
  MonsterProtocol< string > *pMonster = NULL;
  cout << endl;

  Size_type< string > size("7m");
  Color_type< string > color("blue");

  cout << "2. Init with the factory method - static in base, but it invokes\n"
       << "a deduced object. Due to the \"virtual\" declaration, the pointer\n"
       << "to base, handles the deduced object without any problems.\n";
  try {
    pMonster =
        MonsterProtocol< string >::factory("Super Furry Animal", size, color);
  } catch (MonsterProtocol< string >::BadMonsterException &exp) {
    exp.getMessage();
  }
  cout << endl;

  cout << "3. Do something with the monster - e.g. print it out:\n"
       << *pMonster << endl;
  cout << endl;

  cout << "4. Delete the objects space again\n";
  delete pMonster;
  pMonster = NULL;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
