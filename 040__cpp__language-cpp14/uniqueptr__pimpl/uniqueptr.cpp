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

  Widget( const Widget& rhs);
  Widget& operator=(const Widget& rhs);

  std::string content();
};


/** implementation ************************************************************/

// implementation
struct Widget::Impl {
  std::string content;
// ...

  std::string content() const
  {
    return content;
  }
};

Widget::Widget()
: pImpl( std::make_unique< Impl >())
, name("Obelix")
{
  cout << "CALLED: Widget()" << endl;
}

Widget::~Widget()
{
  cout << "CALLED: ~Widget()" << endl;
}

Widget::Widget( const Widget& rhs)
: pImpl(nullptr)
{
  cout << "CALLED: Widget(), copy constructor" << endl;
  if (rhs.pImpl) {
    pImpl = std::make_unique< Impl >(*rhs.pImpl);
  }
}

Widget&
Widget::operator=(const Widget& rhs)
{
  cout << "CALLED: operator=() called" << endl;
  if (!rhs.pImpl) {
    pImpl.reset();
  } else if (!pImpl) {
    pImpl = std::make_unique< Impl >(*rhs.pImpl);
  } else {
    *pImpl = *rhs.pImpl;
  }
}

std::string Widget::content() const
{
  return pImpl->content();
}



int main(void)
{
  cout << "creating 'Widget w1'" << endl;
  Widget w1;

  cout << "moving w1 to w2" << endl;
  auto w2(std::move(w1));

  auto content = w2.content();
  cout << "w2->content: " << content << endl;


  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
