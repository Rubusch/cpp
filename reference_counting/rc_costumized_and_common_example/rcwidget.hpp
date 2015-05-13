// rcwidget.hpp
/*******************************************************************************
 *                         Class RCWidget (from p. 210)                        *
 *                                                                             *
 * I modified this class for the 13th printing of the book.  For details on    *
 * why, consult the erratum affecting pages 209, 210, and 316 that was fixed   *
 * on 7/15/02 in the book's errata list.                                       *
 *******************************************************************************

annotations:

  a simple rc widget implementation
  COW = copy on write
//*/


#ifndef RC_WIDGET
#define RC_WIDGET


#include "rciptr.hpp"
#include "widget.hpp"


class RCWidget 
{
public:
  // ctor
  RCWidget(int size);
  
  // perform some action depending on COW mechanism
  void doThis();
  int showThat() const;
  
private:
  RCIPtr<Widget> value;
};

#endif
