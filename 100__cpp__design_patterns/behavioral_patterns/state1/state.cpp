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
  +-----------------------+\   +---------------------+ +---------------------+
  | state.handleRequest() +-+  | StateA              |     | StateB | | |
+=====================+     +=====================+
  +-------------------------+  | handleRequest()     |     | handleRequest() |
                               +---------------------+ +---------------------+

 (GoF, 1995)

 The 'State' pattern can be used to replace 'switch' (extendibility!) and
 'if' statements which can be difficult to maintain and are less type-safe.
//*/


#include <cstdlib>
#include <iostream>


class State;


class Context
{
private:
  friend class State;
  void changeState(State *state);

private:
  State *state_;

public:
  Context();
  ~Context();


  void request();
};


class State
{
public:
  virtual ~State() {}
  virtual void handleRequest(Context *) = 0;

protected:
  void changeState(Context *pContext, State *pState)
  {
    pContext->changeState(pState);
  }
};


class StateA : public State
{
private:
  StateA() {}

public:
  static StateA *instance()
  {
    try {
      return new StateA();
    } catch (std::bad_alloc &e) {
      std::cerr << "\tAllocation of StateA failed!\n";
      exit(-1);
    }
  }

  void handleRequest(Context *pContext)
  {
    std::cout << ">> open device and get ready\n";
    // and anything else to be done here...
  }
};


class StateB : public State
{
private:
  StateB() {}

public:
  static StateB *instance()
  {
    try {
      return new StateB();
    } catch (std::bad_alloc &e) {
      std::cerr << "\tAllocation of StateB failed!\n";
      exit(-2);
    }
  }

  void handleRequest(Context *pContext)
  {
    std::cout << "<< close device and go standby\n";

    // state transition from StateB to StateA
    changeState(pContext, StateA::instance());
  }
};


Context::Context()
{
  state_ = StateB::instance(); // init with StateB
}

Context::~Context()
{
  delete state_;
  state_ = NULL;
}

void Context::request() { state_->handleRequest(this); }

void Context::changeState(State *state)
{
  if (state_ != NULL) {
    delete state_;
    state_ = NULL;
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
