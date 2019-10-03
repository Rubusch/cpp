// policydesign.cpp
/*
  Demonstrates a basic policy design (source www.en.wikipedia.org)

  "It has been described as a compile-time variant of the strategy pattern,
  and has connections with C++ template metaprogramming."

  Here are two types of policies demonstrated, a type that _does_ something
  and another type that defines _how_ to do it

  A policy shouldn't have a virtual destructor!


  RESOURCE

  Modern C++, Alexandrescu, 1997
//*/


#include <iostream>
#include <string>


/*
  user class

  the class will be instantiated with diferent "behaviours" conforme
  to the passed policies

  policy: uses template type as publicly inherited base class
//*/
template< typename outputPolicy_t, typename languagePolicy_t >
class HelloWorld
  : public outputPolicy_t
  , public languagePolicy_t
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

  policy: passed as template, used as publicly inherited base class
//*/
class OutputPolicy_PrintMe
{
protected:
  template< typename message_type >
  void print( message_type message)
  {
    std::cout << message << std::endl;
  }

  // A policy shouldn't have a virtual destructor!
  ~OutputPolicy_PrintMe(){}
};


/******************************************************************************/


/*
  policy B:

  defines what to be print out e.g. by policy A

  policy: passed as template, used as publicly inherited base class
//*/
class LanguagePolicy_English
{
protected:
  std::string message()
  {
    return "Hello World!";
  }

  // A policy shouldn't have a virtual destructor!
  ~LanguagePolicy_English(){}
};


/*
  policy B:

  defines what to be print out e.g. by policy A,
  another variante of policy B

  policy: passed as template, used as publicly inherited base class
//*/
class LanguagePolicy_French
{
protected:
  std::string message()
  {
    return "Bonjour Le Monde!";
  }

  // A policy shouldn't have a virtual destructor!
  ~LanguagePolicy_French(){}
};


/******************************************************************************/


/*
  main..
//*/
int main()
{
  using namespace std;
  cout << "instance \"flavor A\".." << endl;

  /*
    define the type to work and instantiate
  //*/
  using helloWorld_t = HelloWorld< OutputPolicy_PrintMe, LanguagePolicy_English >;
  auto helloWorld_1 = helloWorld_t();
  helloWorld_1.doSomething();
  cout << endl;

  cout << "instance \"flavor B\".." << endl;
  /*
    now define another type to work using diferent policies
    and instantiate
  //*/
  using other_helloWorld_t = HelloWorld< OutputPolicy_PrintMe, LanguagePolicy_French >;
  auto helloWorld_2 = other_helloWorld_t();
  helloWorld_2.doSomething();
  cout << endl;

  cout << "READY." << endl;
  return 0;
}
