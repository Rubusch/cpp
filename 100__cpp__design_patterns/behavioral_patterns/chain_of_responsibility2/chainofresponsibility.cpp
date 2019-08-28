// chainofresponsibility.cpp
/*
  Avoid coupling the sender of a request to its receiver by giving more than one object a
  chance to handle the request. Chain the receiving objects and pass the request along
  the chain until an object handles it.

  +--------+                       +---------------------+
  | Client |---------------------->| Handler             |<--+
  +--------+                       +=====================+   | pSuccessor_
                                   | pSuccessor_         |---+
                                   +---------------------+
                                   | handleRequest(      |
                                   |   Request*)         |
                                   +---------------------+
                                             /_\
                                              |
                                +-------------+--------------+
                                |                            |
                    +---------------------+       +---------------------+
                    | ConcreteHandler1    |       | ConcreteHandler2    |
                    +=====================+       +=====================+
                    |                     |       |                     |
                    +---------------------+       +---------------------+
                    | handleRequest(      |       | handleRequest(      |
                    |   Request*)         |       |   Request*)         |
                    +---------------------+       +---------------------+


  There are two possibile ways to implement the successor chain:
  a) define new links (usually in the handler, but ConcreteHandler could define them instead)
  b) use existing links

  Also known as "EventHandler", "BureauCat" or "Responder"

  (GoF, 1995)
//*/


#include <iostream>


/*
  Request
//*/
class Request
{
private:
  int kindOfRequest_;

public:
  Request(int kindOfRequest)
    : kindOfRequest_(kindOfRequest)
  {
    std::cout << "\tRequest(int) - ctor\n";
  }

  int getKindOfRequest()
  {
    return kindOfRequest_;
  }

  void drop()
  {
    std::cout << "-> Request \'" << getKindOfRequest()  << "\' dropped!!\n";
  }
};


/*
  Handler

  - defines an interface for handling requests
  - (optional) implements the successor link
//*/
class Handler
{
protected:
  Handler* pSuccessor_;

public:
  Handler(Handler* successor)
    : pSuccessor_(successor)
  {
    std::cout << "\tHandler::Handler( Handler*) - ctor\n";
  }

  virtual void handleRequest(Request* request) = 0;
};


/*
  ConcreteHandler (1)

  - handles request it is repsonsible for
  - can access its successor
  - if the ConcreteHandler can handle the request, it does so; otherwise it
  forwards the request to its successor
//*/
class ConcreteHandler1
  : public Handler
{
public:
  ConcreteHandler1( Handler* successor)
    : Handler(successor)
  {
    std::cout << "\tConcreteHandler1::ConcreteHandler1( Handler*) - ctor\n";
  }

  void handleRequest( Request* request)
  {
    std::cout << "\tConcreteHandler1::handleRequest( Request*)\n";
    if(!request) return;

    if(1 == request->getKindOfRequest()){
      std::cout << "-> Handler 1 will handle the request: \'" << request->getKindOfRequest() << "\'\n";
    }else if(pSuccessor_){
      pSuccessor_->handleRequest(request);
    }else{
      request->drop();
    }
  }
};


/*
  ConcreteHandler (2)
//*/
class ConcreteHandler2
  : public Handler
{
public:
  ConcreteHandler2( Handler* successor)
    : Handler( successor)
  {
    std::cout << "\tConcreteHandler2::ConcreteHandler2( Handler*) - ctor\n";
  }

  void handleRequest( Request* request)
  {
    std::cout << "\tConcreteHandler2::handleRequest( Request*)\n";
    if(!request) return;

    if(2 == request->getKindOfRequest()){
      std::cout << "-> Handler 2 handles request: \'" << request->getKindOfRequest() << "\'\n";
    }else if(pSuccessor_){
      pSuccessor_->handleRequest(request);
    }else{
      request->drop();
    }
  }
};


/*
  Client

  - initiates the request to a ConcreteHandler object on the chain
//*/
int main()
{
  using namespace std;


  cout << "init..\n";
  Request request1(1), request2(2), request3(3);
  cout << endl;


  cout << "set up chain of responsibility..\n";
  ConcreteHandler2 concHandler2(NULL);
  ConcreteHandler1 concHandler1(&concHandler2);
  // remember: these are hardcoded "types of handlers"
  // there could also be several concHandlers2 instances, that build the chain

  Handler* pHead = &concHandler1;
  // a "head" pointer for the list
  cout << endl;


  cout << "pass request 1..\n";
  pHead->handleRequest(&request1);
  cout << endl;


  cout << "pass request 2..\n";
  pHead->handleRequest(&request2);
  cout << endl;


  cout << "pass request 3 (no handler in list)..\n";
  pHead->handleRequest(&request3);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
