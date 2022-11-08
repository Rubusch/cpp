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
  the functor command and activates execution. The ConcreteCommand instance
  shall be queued in the invoker. The re-do of the data happens in the
  receiver().
*/


#include <cstdlib>
#include <iostream>
#include <vector>


struct Receiver {
  Receiver() { std::cout << "\tdo a backup of the passed data\n"; }

  void action() { std::cout << "\tdo some operation\n"; }

  void undo()
  {
    std::cout << "\tundo the last operation by resetting to the backup\n";
  }
};


class Command
{
private:
  Command *pCommand_;

public:
  virtual ~Command() {}
  virtual void execute() = 0;
  virtual void undo() = 0;
};


class ConcreteCommand : public Command
{
private:
  Receiver *pReceiver_;

public:
  ConcreteCommand(Receiver &receiver) : pReceiver_(&receiver) {}

  void execute() { pReceiver_->action(); }

  void undo() { pReceiver_->undo(); }
};


class Invoker
{
private:
  std::vector< Command * > commands_;

public:
  void operator()(Command &command)
  {
    commands_.push_back(&command);
    commands_.back()->execute();
  }

  void undo()
  {
    if (!commands_.empty()) {
      commands_.back()->undo();
      commands_.pop_back();
    }
  }
};


class Client
{
private:
  Receiver *pReceiver_;
  ConcreteCommand *pCommand_;

public:
  Client() : pReceiver_(NULL), pCommand_(NULL) {}

  ~Client()
  {
    if (NULL != pReceiver_) {
      delete pReceiver_;
      pReceiver_ = NULL;
    }

    if (NULL != pCommand_) {
      delete pCommand_;
      pCommand_ = NULL;
    }
  }

  Command &getCmd()
  {
    try {
      pReceiver_ = new Receiver();
    } catch (...) {
      std::cerr << "\tClient::getCmd() - allocation of Receiver failed\n";
      exit(-1);
    }

    try {
      pCommand_ = new ConcreteCommand(*pReceiver_);
    } catch (...) {
      std::cerr
          << "\tClient::getCmd() - allocation of ConcreteCommand failed\n";
      exit(-1);
    }

    return *pCommand_;
  }
};


/*
  main..
*/
int main()
{
  using namespace std;


  cout << "init data - the data are stored here!\n";


  cout << "set a Invoker\n";
  Invoker arrayInvoker;
  cout << endl;


  cout << "a client creates a ConcreteCommand object with a receiver\n";
  Client arrayClient;
  cout << endl;


  cout << "do a command\n";
  arrayInvoker(arrayClient.getCmd());
  cout << endl;


  cout << "undo the last command\n";
  arrayInvoker.undo();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
