#include "async_exception_server.h"


using namespace std;

// needed for static declaration, yet here the definition
std::unique_ptr< AsyncExceptionServer, AsyncExceptionServer::AsyncExceptionServer_deleter > AsyncExceptionServer::instance_ = nullptr;

IExceptionObserver*
AsyncExceptionServer::getObserver() const
{
    return observer_;
}

void
AsyncExceptionServer::Throw(std::exception &e)
{
//    auto *aExSer = AsyncExceptionServer::getInstance();
    auto &aExSer = AsyncExceptionServer::getInstance();
    aExSer.getObserver()->AsyncException(e);
}

AsyncExceptionServer&
AsyncExceptionServer::getInstance()
{
    return *instance_;
}

// CTOR / DTOR...
AsyncExceptionServer&
AsyncExceptionServer::getInstance(IExceptionObserver& eo)
{
//    if (nullptr == instance_) { // can be checked for existence..
    instance_.reset(new AsyncExceptionServer(eo));
//    if (nullptr == instance_) {
    return *instance_;
}
