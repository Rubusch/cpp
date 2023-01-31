#ifndef OBSERVER_H__
#define OBSERVER_H__

#include <iostream>

using namespace std;

/*
  some central exception server
*/
class IExceptionObserver
{
public:
    virtual void AsyncException(std::exception &ex) = 0;
};


class ExceptionObserver : public IExceptionObserver
{
public:
  void AsyncException(std::exception &ex)
  { cerr << "EXCEPTION received: " << ex.what() << endl; }
};

#endif
