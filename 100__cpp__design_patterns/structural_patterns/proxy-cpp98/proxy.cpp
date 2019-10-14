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
  | RealSubject         |<----------<>| Proxy               |
+-------------------------+\
  +=====================+             +=====================+      | ... +-+ |
|             | pRealSubject_ - - - - - - -| pRealSubject_->request(); |
  +---------------------+             +---------------------+      | ... | |
request()           |             | request()           |
+---------------------------+
  +---------------------+             | getSubject()        |
                                      +---------------------+

  (GoF, 1995)
//*/


#include <iostream>


struct Subject {
  virtual ~Subject() {}
  virtual void request() = 0;
};


struct RealSubject : public Subject {
  void request() { std::cout << "-> request in real subject\n"; }
};


struct Proxy : public Subject {
  Proxy() : pRealSubject_(NULL) { getSubject(); }

  ~Proxy()
  {
    if (NULL == pRealSubject_)
      return;
    delete pRealSubject_;
    pRealSubject_ = NULL;
  }

  void request() { pRealSubject_->request(); }

private:
  RealSubject *pRealSubject_;

protected:
  void getSubject()
  {
    if (NULL != pRealSubject_)
      return;

    try {
      pRealSubject_ = new RealSubject;
    } catch (...) {
      std::cerr << "allocation failed\n";
    }
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

  proxy.request();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
