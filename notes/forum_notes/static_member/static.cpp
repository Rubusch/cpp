// static.cpp
/*
  linker error at linking of this situation and how this can be resolved
//*/


#include <iostream>


#define ARGUMENT 777


// class BaseGroove;
// class BattleField;


class BaseGroove
{
public:
  BaseGroove(int arg)
  {
    std::cout << "\t\t\tBaseGroove::BaseGroove( " << arg << " ) - ctor\n";
  }

  void doGroove() { std::cout << "\t\t\tBaseGroove::doGroove()\n"; }
};


class BattleField
{
private:
  // struct
  struct MyGroove : public BaseGroove {
    MyGroove() : BaseGroove(ARGUMENT)
    {
      std::cout << "\t\tMyGroove::MyGroove()\n";
    }
  };

  // typedef
  typedef struct MyGroove Groovy_t;

  // static member
  static Groovy_t groovy;


public:
  static void getStatic()
  {
    std::cout << "\tBattleField::getStatic()\n";

    groovy.doGroove();
  }
};


// definition of static member
BattleField::Groovy_t BattleField::groovy;


/*
  main func..
//*/
int main()
{
  using namespace std;

  cout << "main()\n";

  BattleField::getStatic();

  cout << "READY.\n";
  return 0;
}
