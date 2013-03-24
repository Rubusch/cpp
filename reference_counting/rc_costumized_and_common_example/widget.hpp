// widget.hpp
/*******************************************************************************
 *                          Class Widget (from p. 210)                         *
 *                                                                             *
 * This class is the same as that in the book, but I've added an               *
 * implementation so that RCIPtr can be tested.                                *
 *******************************************************************************

annotations:

  COW = copy on write
//*/


#ifndef WIDGET
#define WIDGET


class Widget 
{
public:
  // ctor
  Widget(int size);
  
  // copy ctor
  Widget(const Widget& rhs);

  // dtor
  ~Widget();

  // op=
  Widget& operator=(const Widget& rhs);

  // some actions
  void doThis();
  int showThat() const;  

private:
  // some data
  int value;
};

#endif

