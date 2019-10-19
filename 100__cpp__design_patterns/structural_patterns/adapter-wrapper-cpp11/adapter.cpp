// adapter.cpp
/*
  Convert the interface of a class into another intarface clients expect.
  Adapter lets classes work together that couldn't otherwise because of
  incompatible interfaces.

  Adapter - Type 1: Target == Adapter, Adaptee is stored as member

                    +---------------------+
                    | Target              |
                    +=====================+
                    |                     |
                    +---------------------+
                    | virtual request()   |
                    +---------------------+
                              /_\
                               |
  +---------+       +---------------------+       +---------------------+
  | Client  |------>| Adapter             |<>-----| Adaptee             |
  +---------+       +=====================+       +=====================+
                    | adaptee: Adaptee    |       |                     |
                    +---------------------+       +---------------------+
                    | request()           |       | specificRequest()   |
                    +---|-----------------+       +---------------------+

                        |

                        |
                +-------------------------+\
                | ...                     +-+
                | adaptee.specificRequest() |
                | ...                       |
                +---------------------------+

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
    std::cout << "> first parameter: \'" << str1 << "\', second parameter: \'"
              << str2 << "\'\n";
  }
};


/*
  Target

  - defines the domain-specific interface that Client uses
//*/
class Target
{
public:
  virtual ~Target() = default;
  virtual void request(std::string) = 0;
};


/*
  Adapter

  - adapts the interface of Adaptee to the Target interface
  - uses delegation to connect the Adaptee
//*/
class Adapter : public Target
{
private:
  Adaptee adaptee;

public:
  void request(std::string str1)
  {
    std::cout << "\tAdapter::request(std::string)\n";
    std::string str2 = "bar";
    adaptee.specificRequest(str1, str2);
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
  Adapter adapter;
  cout << endl;

  cout << "call..\n";
  adapter.request("foo");
  cout << endl;

  cout << "READY.\n";
  return 0;
}
