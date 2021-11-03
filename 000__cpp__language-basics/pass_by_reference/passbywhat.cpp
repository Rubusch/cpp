// passbywhat.cpp
/*
  demonstrates
  - pass-by-value
  - pass-by-reference (pass-by-reference using a reference)
  - pass-by-pointer (pass-by-reference using a pointer)
//*/


#include <iostream>

template < class T >
class Acceptor
{
private:
  const T *pVal = nullptr;

public:
  Acceptor() : pVal(NULL) {}
  virtual ~Acceptor() = default;

  inline void passReference(const T &ref) {
    // assignment is always valid! checking for NULL results in compiler warning!
    pVal = &ref;

    // EITHER, check the assigned pointer for NULL!
    if (!pVal) {
      std::cerr << "ERROR: passReference() - ref == nullptr!!!" << std::endl;
      return;
    }
  }

  void printData()
  {
    if (!pVal)
      return;

    std::cout << "pVal:\t" << pVal << "\n*pVal:\t" << *pVal << "\n&pVal:\t"
              << &pVal << "\n*&pVal:\t" << *&pVal << std::endl;
    std::cout << std::endl;
  }
};


int main()
{
  Acceptor< int > a, b, c;

  int value = 123;
  int *pointer = &value;
  int *nulled_pointer = nullptr; // the danger!
  int *uninitialized_pointer; // DANGEROUS!

  std::cout << "pass-by-reference - pointer" << std::endl;
  a.passReference(*pointer);
  a.printData();
  std::cout << std::endl;

  std::cout << "pass-by-reference - nulled_pointer" << std::endl; // this is possibel, will point to anything (undefined) but: it won't crash the application
  // OR, check at pointer dereferenciation
// TODO
// do a check here: if (nulled_pointer) { - or check inside the application
  b.passReference(*nulled_pointer);
  b.printData();
  std::cout << std::endl;

  std::cout << "pass-by-reference - uninitialized_pointer" << std::endl; // compiler throws a WARNING
  c.passReference(*uninitialized_pointer);
  c.printData();
  std::cout << std::endl;

  std::cout << "READY." << std::endl;
  return 0;
}
