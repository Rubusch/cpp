// rcwidget.cpp
/*
//*/


#include "rcwidget.hpp"


/*
  ctor
//*/
RCWidget::RCWidget(int size) : value(new Widget(size)) {}


/*
  dummy: some action to be performed
//*/
void RCWidget::doThis()
{
  // do COW if Widget is shared
  if (value.getRCObject().isShared()) {
    value = new Widget(*value);
  }
  value->doThis();
}


/*
  dummy: present some results
//*/
int RCWidget::showThat() const { return value->showThat(); }
