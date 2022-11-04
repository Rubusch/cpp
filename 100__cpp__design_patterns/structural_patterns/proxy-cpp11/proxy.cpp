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
*/


#include <iostream>
#include <memory>


/*
  Subject

  - defines the common interface for RealSubject and Proxy so that a Proxy
  can be used anywhere a RealSubject is expected
*/
class Subject
{
public:
  virtual ~Subject() = default;
  virtual void request() = 0;
};


/*
  RealSubject

  - defines the real object that the proxy represents
*/
class RealSubject : public Subject
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
*/
class Proxy : public Subject
{
private:
  std::shared_ptr< RealSubject > pRealSubject_;

protected:
  void getSubject()
  {
    std::cout << "\tProxy::getSubject()\n";
    if (nullptr != pRealSubject_)
      return;
    pRealSubject_ =
        std::make_shared< RealSubject >(); // shift exception handling to client
  }

public:
  Proxy()
  {
    std::cout << "\tProxy::Proxy() - ctor\n";
    getSubject();
  }

  void request()
  {
    std::cout << "\tProxy::request()\n";
    pRealSubject_->request();
  }
};


/*
  main..
*/
int main()
{
  using namespace std;

  cout << "init..\n";
  auto proxy = make_unique< Proxy >();
  cout << endl;

  cout << "call subject's request via proxy\n";
  proxy->request();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
