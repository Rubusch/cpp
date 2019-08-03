// state.cpp
/*
 The 'State' pattern can be used to replace 'switch' (extendibility!) and
 'if' statements which can be difficult to maintain and are less type-safe.
//*/


#include <iostream>
#include <cstdlib>


class State;


/*
  context
//*/
class Context
{
private:
  friend class State;
  void changeState( State* state);

private:
  State *state_;

public:
  Context();
  ~Context();

  void request();
};


/*
  State
//*/
class State
{
private:
  bool state_;
  State(bool state)
  {
    state_ = state;
  }

public:
  static State* instance()
  {
    try{
      return new State(false);
    }catch(std::bad_alloc){
      std::cerr << "\tAllocation of StateA failed!\n";
      exit(-1);
    }
  }

  virtual void handleRequest( Context* pContext)
  {
    switch(state_){
    case true:
      std::cout << ">> open device and get ready\n";
      break;

    case false:
      std::cout << "<< close device and go standby\n";

      // state transition
      changeState( pContext, new State(true));
      break;
    }
  }

protected:
  void changeState( Context* pContext, State *state)
  {
    pContext->changeState(state);
  }
};


/*
  Context.. implementation
//*/

Context::Context()
{
  state_ = State::instance();  // init with StateB
}

Context::~Context()
{
  delete state_; state_ = NULL;
}

void Context::request()
{
  state_->handleRequest(this);
}

void Context::changeState( State *state)
{
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
