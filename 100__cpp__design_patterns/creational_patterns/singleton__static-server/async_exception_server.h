// singleton

#ifndef SINGLETON_H__
#define SINGLETON_H__

#include <iostream>
#include <memory>

#include "observer.h"


/*
  asynchronous exception handler, e.g. for threads etc

  instantiation:
    ...
    ExceptionObserver eo; // derrived from IExceptionObserver
    AsyncExceptionServer __attribute__(( unused )) &eh = AsyncExceptionServer::getInstance(eo);
    ...

  usage:
    try {
      ...
    } catch (std::exception &e) {
      auto &aExSer = AsyncExceptionServer::getInstance();
      aExSer->Throw(e);
    }
*/
class AsyncExceptionServer
{
public:
  struct AsyncExceptionServer_deleter;

  IExceptionObserver* getObserver() const;

  static void Throw(std::exception &e);
  static AsyncExceptionServer& getInstance();
  static AsyncExceptionServer& getInstance(IExceptionObserver& eo);

private:

  static std::unique_ptr< AsyncExceptionServer, AsyncExceptionServer_deleter > instance_;
  IExceptionObserver* observer_;

  // CTOR / DTOR /...
  AsyncExceptionServer(IExceptionObserver& eo) :observer_(&eo) {}

  AsyncExceptionServer(const AsyncExceptionServer&) = delete;
  const AsyncExceptionServer &operator=(AsyncExceptionServer const&) = delete;
  AsyncExceptionServer(AsyncExceptionServer&&) = delete;
  AsyncExceptionServer& operator=(AsyncExceptionServer&&) = delete;
};


struct AsyncExceptionServer::AsyncExceptionServer_deleter
{
  void operator()(const AsyncExceptionServer* const ptr) { delete ptr; }
};


#endif
