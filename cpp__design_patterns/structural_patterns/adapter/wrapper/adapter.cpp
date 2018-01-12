// adapter.cpp
/*
  Convert the interface of a class into another intarface clients expect.
  Adapter lets classes work together that couldn't otherwise because of
  incompatible interfaces.

  Adapter - Type 1: wrapper, Target == Adapter, Adaptee is stored as member

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


struct Adaptee
{
  void specificRequest(std::string str1, std::string str2)
  {
    std::cout << "> first parameter: \'" << str1 << "\', second parameter: \'" << str2 << "\'\n";
  }
};


class Target
{
public:
  virtual void request(std::string) = 0;
};


struct Adapter
  : public Target
{
  void request(std::string str1)
  {
    std::string str2 = "bar";
    adaptee.specificRequest(str1, str2);
  }

private:
  Adaptee adaptee;
};


/*
  main..
//*/
int main()
{
  Adapter adapter;
  adapter.request("foo");

  return 0;
}
