// adapter.cpp
/*
  Convert the interface of a class into another intarface clients expect.
  Adapter lets classes work together that couldn't otherwise because of
  incompatible interfaces.

  Adapter - Type 2: using inheritance, connecting the Target with the Adaptee

                 +---------------------+       +---------------------+ 
                 | Target              |       | Adaptee             |
                 +=====================+       +=====================+
                 |                     |       |                     |
                 +---------------------+       +---------------------+
                 | virtual request()   |       | specificRequest()   |
                 +---------------------+       +---------------------+
                           /_\                           /_\ 
                            |                             |
                            +--------------+--------------+
                                           |
                                           |
  +--------+                    +---------------------+
  | Client |------------------->| Adapter             |
  +--------+                    +=====================+  
                                |                     |
                                +---------------------+
                                | request()           |
                                +---|-----------------+
                                
                                    |
                                    
                                    |
                                +-------------------+\
                                | ...               +-+
                                | specificRequest()   |
                                | ...                 |
                                +---------------------+

  (GoF, 1995)
//*/


#include <iostream>


/*
  Adaptee

  - defines an existing interface that needs adapting
//*/
class Adaptee
{
public:
  void specificRequest(std::string str1, std::string str2)
  {
    std::cout << "\tAdaptee::specificRequest(std::string, std::string)\n";
    std::cout << "> first parameter: \'" << str1 << "\', second parameter: \'" << str2 << "\'\n";
  }
};


/*
  Target

  - defines the domain-specific interface that Client uses
//*/
class Target
{
public:
  virtual void request(std::string){}
};


/*
  Adapter

  - adapts the interface of Adaptee to the Target interface
//*/
class Adapter
  : public Adaptee, public Target
{
public:
  void request(std::string str1)
  {
    std::cout << "\t\tAdapter::request(std::string)\n";
    std::string str2 = "bar";
    specificRequest(str1, str2);
  }
};


/*
  Client

  - collaborates with objects conforming to the Target interface
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Target *pTarget = new Adapter();
  cout << endl;

  cout << "call..\n";
  pTarget->request("foo");
  cout << endl;

  cout << "free..\n";
  delete pTarget;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
