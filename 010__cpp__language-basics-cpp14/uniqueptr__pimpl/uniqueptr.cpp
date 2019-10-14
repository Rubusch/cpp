/*
  C++11 - when using the pImpl idiom, define special member functions in the
  implementation file (Meyers / item 22)

  pImpl Idiom (Herb Sutter, Exceptional C++) is a special case of the bridge
  pattern, GoF "to separate implementation from their representation, so that
  the two can vary independently"
  ...or at least similar, i.e. having the same implementationthe, talking
  about a bridge pattern focusses more on exchanging representations, where
  the pImpl more on separation (?)


  CONCLUSION

  - the pImpl idiom decreases build times by reducing compilation dependencies
    between class clients and class implementations

  - for 'std::unique_ptr pImpl' pointers, declare special member functions in
    the class header, but implement them in the implementation file;
    do this even if the default function implementations are acceptable

  - the above advice applies to 'std::unique_ptr', but not to 'std::shared_ptr'

  demonstrates basic operations with unique_ptr
  resources: Effective Modern C++, Scott Meyers, 2015

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* unique_ptr */

using namespace std;


class Widget
{
private:
  struct Impl;
  std::unique_ptr< Impl > pImpl; // pointer to implementation

public:
  Widget();
  ~Widget();

  Widget(const Widget &rhs);
  Widget &operator=(const Widget &rhs);

  void setContent(std::string str);
  std::string getContent() const;
};


/** implementation ************************************************************/

// implementation
//
// access the implementation via smartptr, the access is hidden to the user of
// the representation, the representation only provides the regular interface
// to the user
//
// pImpl is about separation and stable interfaces to the outside, many changes
// can happen inside without impact to the representation and its user
struct Widget::Impl {
  std::string content;
  // ...

  void setContent(std::string str) { content = str; }
  std::string getContent() { return content; }
};

Widget::Widget() : pImpl(std::make_unique< Impl >())
{
  cout << "CALLED: Widget()" << endl;
}

Widget::~Widget() { cout << "CALLED: ~Widget()" << endl; }

Widget::Widget(const Widget &rhs) : pImpl(nullptr)
{
  cout << "CALLED: Widget(), copy constructor" << endl;
  if (rhs.pImpl) {
    pImpl = std::make_unique< Impl >(*rhs.pImpl);
  }
}

Widget &Widget::operator=(const Widget &rhs)
{
  cout << "CALLED: operator=() called" << endl;
  if (!rhs.pImpl) {
    pImpl.reset();
  } else if (!pImpl) {
    pImpl = std::make_unique< Impl >(*rhs.pImpl);
  } else {
    *pImpl = *rhs.pImpl;
  }
  return *this;
}


void Widget::setContent(std::string str) { pImpl->setContent(str); }

std::string Widget::getContent() const { return pImpl->getContent(); }


/** main **********************************************************************/

int main(void)
{
  cout << "creating 'Widget w1' and setting a name as 'content'" << endl;
  Widget w1;
  w1.setContent("Obelix");
  cout << endl;

  cout << "moving w1 to w2" << endl;
  auto w2(std::move(w1));
  cout << endl;

  auto content = w2.getContent();
  cout << "w2->content: '" << content << "'" << endl;
  cout << endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
