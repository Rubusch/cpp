// facade.cpp
/*
  Provide a unified interace to a set of interfaces in a
  subsystem. Facade defines a higher-level interface that makes the
  subsystem easier to use. (GoF)


  Example here:

                        Facade Interface       Subsystem Interfaces

                        +----------------+
  Client--------------->| Facade       |
                        | (Facade class) |
                        |                |
                        +----------------+
                                 |
                                 |              +---------------+
                                 +------------->| Assistant_1   |
                                 |              +---------------+
                                 |
                                 |              +---------------+
                                 +------------->| Assistant_2   |
                                 |              +---------------+
                                 |
                                 |              +---------------+
                                 +------------->| Assistant_3   |
                                                +---------------+
*/


#include <iostream>


using namespace std;


/*
  Subsystem Classes

  - implement subsystem functionality
  - handle work assigned by the Facade object
  - have to knowledge of the facade; that is, they keep no references to it
*/
class Assistant_1
{
private:
  void doSomething() { cout << "\tAssistant_1 does something\n"; }

public:
  Assistant_1()
  {
    cout << "\tAssistant_1 awakes..\n";
    doSomething();
  }

  ~Assistant_1() { cout << "\tAssistant_1 continues sleeping..\n"; }

  void getSomething() { cout << "\tAssistant_1 serves something\n"; }
};


class Assistant_2
{
private:
  void doSomethingElse() { cout << "\tAssistant_2 does something else\n"; }


public:
  Assistant_2()
  {
    cout << "\tAssistant_2 awakes..\n";
    doSomethingElse();
  }

  ~Assistant_2() { cout << "\tAssistant_2 continues sleeping..\n"; }

  void getSomethingElse() { cout << "\tAssistant_2 serves something else\n"; }
};


class Assistant_3
{
public:
  Assistant_3() { cout << "\tAssistant_3 awakes..\n"; }

  ~Assistant_3() { cout << "\tAssistant_3 continues sleeping..\n"; }

  void fill() { cout << "\tAssistant_3 serves a coke with ice and lemon\n"; }
};


/*
  Facade

  - knows which subsystem classes are repsonsible for a request
  - delegates client requests to appropriate subsystem objects
*/
class Facade
{
public:
  Facade() = default;
  Facade(Facade const &ng) = default;

  Facade &operator=(const Facade &ng) = default;

  void startOrder()
  {
    cout << "client orders\n";
    Assistant_1 assistant1;
    Assistant_2 assistant2;
    Assistant_3 assistant3;
    cout << endl;

    cout << "client serves\n";
    assistant3.fill();
    assistant1.getSomething();
    assistant2.getSomethingElse();
    cout << endl;

    cout << "client waits on orders\n";
  }
};


/*
  client
*/
class Client
{
private:
  Facade *facade;

public:
  Client() : facade(nullptr)
  {
    facade = new Facade();
    facade->startOrder();
  }

  ~Client() { delete facade; }
};


/*
  ..main
*/
int main()
{
  cout << "init..\n";
  Client client;

  cout << "READY.\n";
  return 0;
}
