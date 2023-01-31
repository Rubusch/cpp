// singleton.cpp
/*
  Ensure a class only has one instance, and provide a global point of
  access to it.

  +-----------------------+
  | Singleton             |
  +-----------------------+
  | private:              |<----+
  | Singleton()           |     |
  |                       |     |
  | public:               |     |
  | static getInstance()  |-----+
  +-----------------------+

  Destruction of the Singelton

  The Singleton should not be destroyed by the user! The only correct
  way to avoid resource leaks is to delete the Singleton object during
  the application's shutdown.

  This is mainly using the static quality of the pattern to provide a
  centralized server for events, such as exceptions.

  (GoF, 1995)
*/


/*
  main..
*/

#include <iostream>
#include <exception>

#include "async_exception_server.h"
#include "observer.h"

using namespace std;

void do_something()
{
  throw std::runtime_error("Hurra!");
}

int main()
{
  ExceptionObserver eo; // derrived from IExceptionObserver

  cout << "create Singleton:\n";
  AsyncExceptionServer __attribute__(( unused )) &eh = AsyncExceptionServer::getInstance(eo);
  cout << endl;

  cout << "now do something...\n";
  try {
    do_something();
  } catch (std::exception& e) {
    auto &aExSer = AsyncExceptionServer::getInstance();
//    AsyncExceptionServer& aExSer = AsyncExceptionServer::getInstance();
    aExSer.Throw(e);
  }


  cout << "READY.\n";
  return 0;
}
