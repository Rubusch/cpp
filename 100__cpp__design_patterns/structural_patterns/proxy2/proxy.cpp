// proxy.cpp
/*
  Provide a surrogate or placeholder for another object to control access to it.


  +--------+        +---------------------+
  | Client |------->| Subject             |
  +--------+        +=====================+
                    |                     |
                    +---------------------+
                    | request()           |
                    +---------------------+
                              /_\
                               |
             +-----------------+-----------------+
             |                                   |
  +---------------------+             +---------------------+
  | RealSubject         |<----------<>| Proxy               |      +-------------------------+\
  +=====================+             +=====================+      | ...                     +-+
  |                     |             | pRealSubject_ - - - - - - -| pRealSubject_->request(); |
  +---------------------+             +---------------------+      | ...                       |
  | request()           |             | request()           |      +---------------------------+
  +---------------------+             | getSubject()        |
                                      +---------------------+

  (GoF, 1995)
//*/


#include <iostream>


/*
  Subject

  - defines the common interface for RealSubject and Proxy so that a Proxy
  can be used anywhere a RealSubject is expected
//*/
class Subject
{
public:
  virtual ~Subject(){}
  virtual void request() = 0;
};


/*
  RealSubject

  - defines the real object that the proxy represents
//*/
class RealSubject
  : public Subject
{
public:
  void request()
  {
    std::cout << "\tRealSubject::request()\n";
    std::cout << "-> request in real subject\n";
  }
};


/*
  Proxy

  - maintains a reference that lets the proxy access the real
  subject. Proxy may refer to a Subject if the RealSubject and
  Subject interfaces are the same

  - provides an interface identical to Subject's so that a proxy
  can be substituted for the real subject

  - controls access to the real subject and may be responsible
  for creating and deleting it

  - other responsibilities depend on the kind of proxy:
  -> remote proxies are responsible for encoding a request and
  its arguments and for sending the encoded request to the real
  subject in a different address space

  -> virtual proxies may cache additional information about the
  real subject so that they can postpone accessing it.

  -> protection proxies check that the caller has the access
  permissions required to perform a request
//*/
class Proxy
  : public Subject
{
private:
  RealSubject* pRealSubject_;

protected:
  void getSubject()
  {
    std::cout << "\tProxy::getSubject()\n";
    if(NULL != pRealSubject_) return;

    try{
      pRealSubject_ = new RealSubject;
    }catch(...){
      std::cerr << "allocation failed\n";
    }
  }

public:
  Proxy()
    : pRealSubject_(NULL)
  {
    std::cout << "\tProxy::Proxy() - ctor\n";
    getSubject();
  }

  ~Proxy()
  {
    std::cout << "\tProxy::~Proxy() - dtor\n";
    if(NULL == pRealSubject_) return;
    delete pRealSubject_;
    pRealSubject_ = NULL;
  }

  void request()
  {
    std::cout << "\tProxy::request()\n";
    pRealSubject_->request();
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Proxy proxy;
  cout << endl;

  cout << "call subject's request via proxy\n";
  proxy.request();
  cout << endl;

  cout << "READY.\n";
  return 0;
}

