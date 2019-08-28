// protocol.cpp
/*
  A protocol class in C++ is similar to an "Interface" in Java.

  A protocol is an abstract class that contains the "protocol" of the members to implement,
  each "value" is abstracted by a function to gain some kind of type independence.

  A good explanation of a protocol class is contained in Effective C++ / Item 34 / Meyers.

  Further this class demonstrates exception handling
//*/

#include <iostream>
#include <string>
#include <exception>

using namespace std;

/*
  forwared declarations
//*/
template<class T>
class AnimalProtocol;

template<class T>
class RealAnimal;

template<class T>
ostream& operator<<(ostream& out, AnimalProtocol<T>& animal);


/*-------------------------------------------------------------------------------------------*/


/*
  some data types
//*/
template<class T>
class Size_type
{
private:
  T data;
public:
  Size_type(T size)
    : data(size)
  {}

  T getSize() const
  { return data; }
};


template<class T>
class Color_type
{
private:
  T data;
public:
  Color_type(T color)
    : data(color)
  {}

  T getColor() const
  { return data; }
};


template<class T>
class Species_type
{
private:
  T data;
public:
  Species_type(T species)
    : data(species)
  {}

  T getSpecies() const
  { return data; }
};


/*-------------------------------------------------------------------------------------------*/


/*
  protocol class / interface
//*/
template<class T>
class AnimalProtocol
{
public:
  virtual ~AnimalProtocol();

  virtual string getSpecies() const = 0;
  virtual string getSize() const = 0;
  virtual string getColor() const = 0;

  friend
  ostream& operator<< <T>(ostream& out, AnimalProtocol<T>& animal);

  class BadAnimalException : public exception
  {
  public:
    BadAnimalException() {};
    ~BadAnimalException() throw() {}
    const char* what() const throw()
    {
      return "Allocation Failed!";
    }
  };

  // a "factory method" for objects supporting the "Animal"-Protocol / Interface
  static AnimalProtocol<T>* animalFactoryMethod( const Species_type<T>& species
                                                , const Size_type<T>& size
                                                 , const Color_type<T>& color)
    throw(BadAnimalException);
};


template<class T>
AnimalProtocol<T>::~AnimalProtocol()
{
  cout << "Protocol base class dtor!\n";
}


template<class T>
inline
ostream& operator<<(ostream& out, AnimalProtocol<T>& animal)
{
  return out << "species\t: " << animal.getSpecies()
             << "\nsize\t: " << animal.getSize()
             << "\ncolor\t: " << animal.getColor()
             << endl;
}


/*-------------------------------------------------------------------------------------------*/


/*
  some real instance of the abstract interface
//*/
template<class T>
class RealAnimal: public AnimalProtocol<T>
{
private:
  Species_type<T> species_;
  Size_type<T> size_; // can have any type here
  Color_type<T> color_;

public:
  RealAnimal( const Species_type<T>& species, const Size_type<T>& size, const Color_type<T>& color);

  virtual ~RealAnimal();

  string getSpecies() const;
  string getSize() const;
  string getColor() const;
};


template<class T>
RealAnimal<T>::RealAnimal(const Species_type<T>& species, const Size_type<T>& size, const Color_type<T>& color)
  :species_(species), size_(size), color_(color)
{}


template<class T>
RealAnimal<T>::~RealAnimal()
{
  cout << "Deduced instance dtor!\n";
}


template<class T>
string RealAnimal<T>::getSpecies() const
{
  return species_.getSpecies();
}


template<class T>
string RealAnimal<T>::getSize() const
{
  return size_.getSize();
}


template<class T>
string RealAnimal<T>::getColor() const
{
  return color_.getColor();
}


/*-------------------------------------------------------------------------------------------*/


/*
  needs to be implement in the "real" instance of the deduced class
//*/
template<class T>
AnimalProtocol<T>* AnimalProtocol<T>::animalFactoryMethod( const Species_type<T>& species
                                                           , const Size_type<T>& size
                                                           , const Color_type<T>& color)
  throw(AnimalProtocol<T>::BadAnimalException)
{
  // allocate space for an animal object
  return new RealAnimal<T>(species, size, color);
  throw BadAnimalException();
}


/*-------------------------------------------------------------------------------------------*/


/*
  some main
//*/
int main()
{
  // create a pointer to the base class
  cout << "Init..\n" << endl;
  AnimalProtocol<string> *pAnimal = NULL;

  Species_type<string> species("foobarfant");
  Size_type<string> size("5,00m");
  Color_type<string> color("blue eyes");

  // will be assigned dynamicly
  try{
    pAnimal = AnimalProtocol<string>::animalFactoryMethod(species, size, color);
  }catch(AnimalProtocol<string>::BadAnimalException &ex){
    cerr << ex.what() << endl;
  }

  // print out the new animal
  cout << "We have a new animal created:\n" << *pAnimal << endl;

  // we need to delete the space again
  delete pAnimal; pAnimal = NULL;

  cout << "READY.\n";
  return 0;
}
