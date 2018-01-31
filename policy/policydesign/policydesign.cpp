// policydesign.cpp
/*
  Demonstrates a basic policy design (source www.en.wikipedia.org)

  "It has been described as a compile-time variant of the strategy pattern,
  and has connections with C++ template metaprogramming."

  Here are two types of policies demonstrated, a type that _does_ something
  and another type that defines _how_ to do it

  A policy shouldn't have a virtual destructor.
//*/


#include <iostream>
#include <string>


/*
  user class

  the class will be instantiated with diferent "behaviours" conforme
  to the passed policies
//*/
template< typename outputPolicy_t, typename languagePolicy_t >
class HelloWorld : public outputPolicy_t, public languagePolicy_t
{
  using outputPolicy_t::print;
  using languagePolicy_t::message;

public:
  // the function to be called
  void doSomething()
  {
    /*
      the "behaviour" depends on the - as template - passed policies
    //*/
    print( message() );
  }
};


/******************************************************************************/


/*
  policy A:

  defines _what_ to do, uses policy B
//*/
class OutputPolicy_PrintMe
{
protected:
  template< typename message_type >
  void print( message_type message)
  {
    std::cout << message << std::endl;
  }

  // dtor
  ~OutputPolicy_PrintMe()
  {}
};


/******************************************************************************/


/*
  policy B:

  defines what to be print out e.g. by policy A
//*/
class LanguagePolicy_English
{
protected:
  std::string message()
  {
    return "Hello World!";
  }

  // dtor
  ~LanguagePolicy_English()
  {}
};


/*
  policy B:

  defines what to be print out e.g. by policy A,
  another variante of policy B
//*/
class LanguagePolicy_French
{
protected:
  std::string message()
  {
    return "Bonjour Le Monde!";
  }

  // dtor
  ~LanguagePolicy_French()
  {}
};


/******************************************************************************/


/*
  main..
//*/
int main()
{
  using namespace std;
  cout << "instance \"flavor A\"..\n";

  /*
    define the type to work and instantiate
  //*/
  typedef HelloWorld<
    OutputPolicy_PrintMe
    , LanguagePolicy_English
    >
    helloWorld_t;

  helloWorld_t helloWorld_1;
  helloWorld_1.doSomething();
  cout << endl;


  cout << "instance \"flavor B\"..\n";
  /*
    now define another type to work using diferent policies
    and instantiate
  //*/
  typedef HelloWorld<
    OutputPolicy_PrintMe
    , LanguagePolicy_French
    >
    other_helloWorld_t;

  other_helloWorld_t helloWorld_2;
  helloWorld_2.doSomething();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
