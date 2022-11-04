// adapter.cpp
/*
  Convert the interface of a class into another intarface clients expect.
  Adapter lets classes work together that couldn't otherwise because of
  incompatible interfaces.

  Adapter - Type 2: using inheritance, connecting the Target with the Adaptee

  +--------+     +---------------------+       +---------------------+
  | Client |---->| Target              |       | Adaptee             |
  +--------+     +=====================+       +=====================+
                 |                     |       |                     |
                 +---------------------+       +---------------------+
                 | virtual request()   |       | specificRequest()   |
                 +---------------------+       +---------------------+
                           /_\                           /_\
                            |                             |
                            +--------------+--------------+
                                           |
                                           |
                                +---------------------+
                                | Adapter             |
                                +=====================+
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
*/


#include <iostream>


struct Adaptee {
  virtual ~Adaptee() {}
  void specificRequest(std::string str1, std::string str2)
  {
    std::cout << "> first parameter: \'" << str1 << "\', second parameter: \'"
              << str2 << "\'\n";
  }
};


struct Target {
  virtual ~Target() {}
  virtual void request(std::string) {}
};


struct Adapter : public Adaptee, public Target {
  void request(std::string str1)
  {
    std::string str2 = "bar";
    specificRequest(str1, str2);
  }
};


/*
  main..
*/
int main()
{
  Target *pTarget = new Adapter();
  pTarget->request("foo");
  delete pTarget;
  return 0;
}
