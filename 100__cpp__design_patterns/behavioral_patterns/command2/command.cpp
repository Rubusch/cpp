// command.cpp
/*
  "Encapsulate a request as an object, thereby letting you parametrize
  clients with different requests, queue or log requests, and support
  undo-able operations."

  +---------------------+                      +---------------------+
  | Invoker             |<>--------------------| Command             |
  +=====================+                      +=====================+
  | pCommand_: *Command |                      | execute()           |
  +---------------------+                      +---------------------+
  |                     |                      |                     |
  +---------------------+                      +---------------------+
                                                        /_\
                                                         |
                                                         |
                                                         |
  +---------------------+                      +---------------------+
  | Receiver            |<---------------------| Concrete Command    |
  +=====================+                      +=====================+
  | action()            |                      | pReceiver_          |
  +---------------------+      +--------+      |    : Receiver       |
  |                     |<-----| Client |- - ->+---------------------+      +--------------------+\
  +---------------------+      +--------+      | execute()      - - - - - - | receiver->action() +-+
                                               +---------------------+      +----------------------+



  (GoF, Design Patterns)


  "The design that describes encapsulated requests, and that generalized
  functors follow, is Command."

  "The command pattern thus ensures an important separation between the invoker
  and the receiver."

  "The command pattern enables delayed calls."
  (Alexandrescu, 2001)


  The following example implements operations on an array, in the example case:

  sorting

  The dualism of Receiver and ConcreteCommand can be implemented like a brigde,
  hence another action() in another Receiver could implement a complete
  different sort algorithm or even mixing. Operations on other structures, say,
  searching on binary trees for instance, could be implemented using another
  ConcreteCommand.

  The client builds up one 'set' and passes it to the invoker. The invoker calls
  the functor command and activates execution. The ConcreteCommand instance shall
  be queued in the invoker. The re-do of the data happens in the receiver().
//*/


#include <iostream>
#include <vector>
#include <cstdlib>


/*
  Receiver

  - knows how to perform the operations associated with carrying out the request
//*/
class Receiver
{
private:
  unsigned int *arr_;
  unsigned int *arr_orig_;
  const  unsigned int size_;

  /*
    this is just some operation to be performed on the data..
    can be anything, here it's a sort
  //*/
  void doSort()
  {
    std::cout << "\tReceiver::doSort()\n";
    if(size_ < 2) return;
    int tmp=0;
    unsigned idx=size_-2;
    bool swapped = true;

    do{
      if(idx == size_-2){
        if(!swapped) break;
        idx=0;
        swapped = false;
      }else ++idx;

      if(arr_[idx] > arr_[idx+1]){
        tmp = arr_[idx];
        arr_[idx] = arr_[idx+1];
        arr_[idx+1] = tmp;

        swapped = true;
      }

    }while(true);
  }

public:
  Receiver(unsigned int* arr, const unsigned int size)
    : arr_(arr), size_(size)
  {
    std::cout << "\tReceiver::Receiver(unsigned int*, const unsigned int) - ctor\n";

    // checks
    if( arr_ == NULL) return;

    // do copy, stored here to enable the undo operation
    try{
      arr_orig_ = new unsigned int[size];
    }catch(...){
      std::cerr << "Receiver::ERROR: allocation failed!";
      exit(-1);
    }
    for(unsigned int idx=0; idx < size_; ++idx){
      arr_orig_[idx] = arr_[idx];
    }
  }

  void action()
  {
    std::cout << "\tReceiver::action()\n";
    doSort();
  }

  void undo()
  {
    std::cout << "\tReceiver::undo()\n";

    // checks
    if(NULL == arr_){
      std::cerr << "\tReceiver::ERROR - original array was NULL!\n";
      return;
    }

    for(unsigned int idx=0; idx < size_; ++idx){
      arr_[idx] = arr_orig_[idx];
    }
  }
};


/*
  Command

  - declares an interface for executing an operation
//*/
class Command
{
private:
  Command* pCommand_;

public:
  virtual ~Command(){}
  virtual void execute() = 0;
  virtual void undo() = 0;
};


/*
  ConcreteCommand

  - defines a binding between a Receiver object and an action
  - implements execute() by invoking the corresponding operation(s) on Receiver
//*/
class ConcreteCommand
  : public Command
{
private:
  Receiver *pReceiver_;

public:
  ConcreteCommand(Receiver& receiver)
    : pReceiver_(&receiver)
  {
    std::cout << "\tConcreteCommand::ConcreteCommand(int) - ctor\n";
  }

  void execute()
  {
    std::cout << "\tConcreteCommand::execute()\n";
    pReceiver_->action();
  }

  void undo()
  {
    std::cout << "\tConcreteCommand::undo()\n";
    pReceiver_->undo();
  }
};


/*
  Invoker

  Functor - asks the command to carry out the request
  and queues the commands
//*/
class Invoker
{
private:
  std::vector< Command* > commands_;

public:
  void operator()(Command& command)
  {
    std::cout << "\tInvoker::operator(Command&)\n";
    commands_.push_back(&command);
    commands_.back()->execute();
  }

  void undo()
  {
    std::cout << "\tInvoker::undo() - there's no redo ;)\n";
    if(!commands_.empty()){
      commands_.back()->undo();
      commands_.pop_back();
    }
  }
};


/*
  Client

  creates a ConcreteCommand object and sets its receiver
//*/
class Client
{
private:
  Receiver *pReceiver_;
  ConcreteCommand *pCommand_;

public:
  Client()
    : pReceiver_(NULL), pCommand_(NULL)
  {
    std::cout << "\tClient::Client() - ctor\n";
  }

  ~Client()
  {
    std::cout << "\tClient::~Client() - dtor\n";
    if(NULL != pReceiver_){
      delete pReceiver_;
      pReceiver_ = NULL;
    }

    if(NULL != pCommand_){
      delete pCommand_;
      pCommand_ = NULL;
    }
  }

  Command& getCmd(unsigned int* arr, const unsigned int size)
  {
    std::cout << "\tClient::getCmd(unsigned int*, const unsigned int)\n";
    try{
      pReceiver_ = new Receiver(arr, size);
    }catch(...){
      std::cerr << "\tClient::getCmd() - allocation of Receiver failed\n";
      exit(-1);
    }

    try{
      pCommand_ = new ConcreteCommand(*pReceiver_);
    }catch(...){
      std::cerr << "\tClient::getCmd() - allocation of ConcreteCommand failed\n";
      exit(-1);
    }

    return *pCommand_;
  }
};


/*
  show
//*/
void show(unsigned int* arr, unsigned int size)
{
  std::cout << "content:\n";
  for(unsigned int idx = 0; idx < size; ++idx){
    std::cout << arr[idx] << "\t";
  }
  std::cout << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << " - the user acts as Invoker - \n\n";


  cout << "init data - the data are stored here!\n";
  unsigned int arr[] = { 2, 3, 5, 4, 7, 6, 1 };
  unsigned int size = sizeof(arr) / sizeof(unsigned int);


  cout << "set a Invoker\n";
  Invoker arrayInvoker;
  cout << endl;


  cout << "a client creates a ConcreteCommand object with a receiver\n";
  Client arrayClient;
  show( arr, size);
  cout << endl;


  cout << "do a command\n";
  arrayInvoker(arrayClient.getCmd(arr, size));
  show( arr, size);
  cout << endl;


  cout << "undo the last command\n";
  arrayInvoker.undo();
  show( arr, size);
  cout << endl;

  cout << "READY.\n";
  return 0;
}
