// state.cpp
/*
  Allow an object to alter its behavior when its internal state changes.
  The object will appear to change its class.


  +---------------------+                     +---------------------+    
  | Context             |<>------------------>| State               |
  +=====================+                     +=====================+
  | request()           |                     | handleRequest()     |
  +---|-----------------+                     +---------------------+
                                                  /_\         /_\
      |                                            |           |
                                           +-------+           +-------+
      |                                    |                           |
  +-----------------------+\   +---------------------+     +---------------------+ 
  | state.handleRequest() +-+  | StateA              |     | StateB      |
  |                         |  +=====================+     +=====================+
  +-------------------------+  | handleRequest()     |     | handleRequest()     |
                               +---------------------+     +---------------------+
               
 (GoF, 1995)

 The 'State' pattern can be used to replace 'switch' (extendibility!) and
 'if' statements which can be difficult to maintain and are less type-safe.
//*/


#include <iostream>
#include <cstdlib>


// trick to get it compiled
class State;


/*
  context

  - defines the interface of interest to clients.  
  - maintains an instance of a ConcreteState subclass that defines the 
  current state.
//*/
class Context
{
private:
  friend class State;
  void changeState( State* state);

private:
  State* state_;

public:
  Context();  
  ~Context();

  // can have several requests, just one example here
  void request();

  // implementation below... (linker)
};


/*
  State
  
  - defines an interface for encapsulating the behavior associated with a 
  particular state of the Context.
//*/
class State
{
public:
  // can implement several request handlers
  virtual void handleRequest( Context*) = 0;
  ~State()
  {
    std::cout << "\tState::~State() - dtor\n";
  }

protected:
  // this is possible because of the "friend" declaration
  void changeState( Context* pContext, State* pState)
  {
    std::cout << "\tState::changeState( Context*, State*)\n";
    pContext->changeState(pState);
  }
};


/*
  StateA

  - each subclass implements a behavior associated with a state of the Context.
//*/
class StateA
  : public State
{
private:
  // should be private
  StateA()
  {
    std::cout << "\tStateA::StateA() - ctor\n";
  }

public:
  static StateA* instance()
  {
    std::cout << "\tStateA::instance()\n";
    try{
      return new StateA();
    }catch(std::bad_alloc){
      std::cerr << "\tAllocation of StateA failed!\n";
      exit(-1);
    }
  }

  void handleRequest( Context* pContext)
  {
    std::cout << "\tStateA::handleRequest()\n";
    std::cout << ">> open device and get ready\n";
    // and anything else to be done here...
  }
};


/*
  StateB

  - each subclass implements a behavior associated with a state of the Context.
//*/
class StateB
  : public State
{
private:
  // should be private
  StateB()
  {
    std::cout << "\tStateB::StateB() - ctor\n";
  }

public:
  static StateB* instance()
  {
    std::cout << "\tStateB::instance()\n";
    try{
      return new StateB();
    }catch(std::bad_alloc){
      std::cerr << "\tAllocation of StateB failed!\n";
      exit(-2);
    }
  }

  void handleRequest( Context* pContext)
  {
    std::cout << "\tStateB::handleRequest()\n";
    std::cout << "<< close device and go standby\n";

    // state transition from StateB to StateA
    changeState( pContext, StateA::instance()); 
  }
};


/*
  Context.. implementation
//*/

Context::Context()
{
  std::cout << "\tContext::Context() - ctor\n";
  state_ = StateB::instance();  // init with StateB
}
  
Context::~Context()
{
  std::cout << "\tContext::~Context() - dtor\n";
  delete state_; state_ = NULL;
}

void Context::request()
{
  std::cout << "\tContext::request()\n";
  state_->handleRequest(this);
}

void Context::changeState( State* state)
{
  std::cout << "\tContext::changeState( State*)\n"; 
  if(state_ != NULL){
    delete state_; state_ = NULL;
  }
  state_ = state;
}


/*
  main()
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Context context;
  cout << endl;

  cout << "1. request..\n";
  context.request();
  cout << endl;

  cout << "2. request..\n";
  context.request();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
