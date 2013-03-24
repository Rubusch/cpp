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
  {}

  int getKindOfRequest()
  {
    return kindOfRequest_;
  }

  void drop()
  {
    std::cout << "-> Request \'" << getKindOfRequest()  << "\' dropped!!\n";
  }
};


class Handler
{
protected:
  Handler* pSuccessor_;

public:
  Handler(Handler* successor)
    : pSuccessor_(successor)
  {}

  virtual void handleRequest(Request* request) = 0;
};


struct ConcreteHandler1
  : public Handler
{
  ConcreteHandler1( Handler* successor)
    : Handler(successor)
  {}

  void handleRequest( Request* request)
  {
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


struct ConcreteHandler2
  : public Handler
{
  ConcreteHandler2( Handler* successor)
    : Handler( successor)
  {}

  void handleRequest( Request* request)
  {
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
//*/
int main()
{
  using namespace std;


  cout << "init..\n";
  Request request1(1), request2(2), request3(3);
  ConcreteHandler2 concHandler2(NULL); 
  ConcreteHandler1 concHandler1(&concHandler2);
  Handler* pHead = &concHandler1;
  cout << endl;

  
  pHead->handleRequest(&request1);
  cout << endl;


  pHead->handleRequest(&request2);
  cout << endl;

  
  pHead->handleRequest(&request3);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
