// prototype.cpp
/*
  Specify the kinds of objects to create using a prototypical instance,
  and create new objects by copying this prototype.


  +--------+        +---------------------+
  | client |------->| Prototype           |
  +--------+        +=====================+
                    | clone()             |
                    +---------------------+
                             /_\
                              |
                              |
                              |
             +-----------------------------------+
             |                                   |
  +---------------------+             +---------------------+
  | ConcretePrototype1  |             | ConcretePrototype2  |
  +=====================+             +=====================+
  | clone() : Prototype |             | clone() : Prototype |
  +---------------------+             +---------------------+

  (GoF, 1995)
//*/


#include <iostream>


/*
  Prototype

  - declares an interface for cloning itself
//*/
class Prototype
{
private:
  std::string data_;

protected:
  std::string getData() { return data_; }

public:
  Prototype() : data_("") { std::cout << "\tPrototype::Prototype() - ctor\n"; }

  Prototype(Prototype const &pt)
  {
    std::cout << "\tPrototype::Prototype(Prototype const&) - cpy ctor\n";
    data_ = pt.data_;
  }

  virtual ~Prototype() {}

  virtual Prototype *clone() const = 0;
  virtual void show() = 0;

  void setData(const std::string data) { data_ = data; }
};


/*
  Concrete Prototype 1

  - implements an operation for cloning itself
//*/
class ConcretePrototype1 : public Prototype
{
private:
  std::string str_;

public:
  ConcretePrototype1() : str_("first")
  {
    std::cout << "\tConcretePrototype1::ConcretePrototype1() - ctor\n";
  }

  ConcretePrototype1(ConcretePrototype1 const &cpt) : Prototype(cpt)
  {
    std::cout << "\tConcretePrototype1::ConcretePrototype1(ConcretePrototype1 "
                 "const&) - cpy ctor\n";
    if (this == &cpt)
      return;
    str_ = cpt.str_;
  }

  Prototype *clone() const
  {
    std::cout << "\tConcretePrototype1::clone()\n";
    return new ConcretePrototype1(*this);
  }

  void show()
  {
    std::cout << "\n"
              << "CONTENT:\n"
              << "class ConcretePrototype1\n"
              << "Prototype::data_ = \t\t\'" << getData() << "\'\n"
              << "ConcretePrototype1::str_ = \t\'" << str_ << "\'\n"
              << "\n\n";
  }
};


/*
  Concrete Prototype 2 - another Concrete Prototyp
//*/
class ConcretePrototype2 : public Prototype
{
private:
  int cnt_;

public:
  ConcretePrototype2() : cnt_(22)
  {
    std::cout << "\tConcretePrototype2::ConcretePrototype2() - ctor\n";
  }

  ConcretePrototype2(ConcretePrototype2 const &cpt) : Prototype(cpt)
  {
    std::cout << "\tConcretePrototype2::ConcretePrototype2(ConcretePrototype2 "
                 "const&) - cpy ctor\n";
    if (this == &cpt)
      return;
    cnt_ = cpt.cnt_;
  }

  Prototype *clone() const
  {
    std::cout << "\tConcretePrototype2::clone()\n";
    return new ConcretePrototype2(*this);
  }

  void show()
  {
    std::cout << "\n"
              << "CONTENT:\n"
              << "class ConcretePrototype2\n"
              << "Prototype::data_ = \t\t\'" << getData() << "\'\n"
              << "ConcretePrototype2::cnt_ = \t" << cnt_ << "\n"
              << "\n\n";
  }
};


/*
  Client

  - creates a new object by asking a prototype to clone itself
//*/
class Client
{
private:
  Prototype *pPrototype1, *pPrototype2;

public:
  Client()
      : pPrototype1(new ConcretePrototype1()),
        pPrototype2(new ConcretePrototype2())
  {
    std::cout << "\tClient::Client() - ctor\n";
    pPrototype1->setData("Common Base Data First Form");
    pPrototype2->setData("Common Base Data Second Form");
  }

  Prototype *createCopy(const int selected_type) const
  {
    std::cout << "\tClient::createCopy(int)\n";

    switch (selected_type) {
    case 1:
      return pPrototype1->clone();
    case 2:
      return pPrototype2->clone();
    default:
      return NULL;
    }
  }

  ~Client()
  {
    std::cout << "\tClient::~Client()\n";
    delete pPrototype1;
    pPrototype1 = NULL;
    delete pPrototype2;
    pPrototype2 = NULL;
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  // init
  cout << "init...\n";
  const int FIRST_FORM = 1;
  const int SECOND_FORM = 2;
  Client cl;
  ConcretePrototype1 *pUsage1 = NULL;
  ConcretePrototype2 *pUsage2 = NULL;
  cout << endl;


  // use the client
  cout << "get a FIRST_FORM object:\n";
  pUsage1 = dynamic_cast< ConcretePrototype1 * >(cl.createCopy(FIRST_FORM));
  pUsage1->show();
  cout << endl;


  // get one of the second forms
  cout << "get a SECOND_FORM object:\n";
  pUsage2 = dynamic_cast< ConcretePrototype2 * >(cl.createCopy(SECOND_FORM));
  pUsage2->show();
  cout << endl;

  // free
  cout << "free...\n";
  delete pUsage1;
  pUsage1 = NULL;
  delete pUsage2;
  pUsage2 = NULL;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
