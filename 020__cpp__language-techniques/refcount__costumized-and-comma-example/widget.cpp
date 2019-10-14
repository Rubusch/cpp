// widget.cpp
/*
//*/


#include "widget.hpp"


/*
  ctor
//*/
Widget::Widget(int size) : value(size) {}


/*
  copy ctor
//*/
Widget::Widget(const Widget &rhs) : value(rhs.value) {}


/*
  dtor
//*/
Widget::~Widget() {}


/*
  op=
//*/
Widget &Widget::operator=(const Widget &rhs)
{
  value = rhs.value;
  return *this;
}


/*
  some action
//*/
void Widget::doThis() { value = -1; }


/*
  some result
//*/
int Widget::showThat() const { return value; }
