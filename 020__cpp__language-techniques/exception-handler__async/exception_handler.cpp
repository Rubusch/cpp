#include <iostream>
#include <future>
#include <signal.h>
#include "exception_handler.h"

using namespace std;

// NB: static variables are only _declared_ in the header, but need a
// separate _definition_ in the .cpp
pid_t Exception_handler::pid_sighandler;
int Exception_handler::RUNNING__;

void
Exception_handler::register_sighandler()
{
  sa.sa_sigaction = sighandler; // NB: either set sa.sa_handler (simple), or sa.sa_sigaction (extended)
  sigemptyset(&sa.sa_mask); // now need a signal mask, pre-init mask
  sa.sa_flags = SA_SIGINFO; // for message passing, needs SA_SIGINFO!!!
  sigaction(SIGUSR1, &sa, NULL);
}

void
Exception_handler::set_pid(pid_t pid)
{
  pid_sighandler = pid;
}

pid_t
Exception_handler::get_pid()
{
  return pid_sighandler;
}

void
Exception_handler::ignore_action()
{
  Exception_handler::RUNNING__ = 1;
}

void
Exception_handler::do_action()
{
  Exception_handler::RUNNING__ = 0;
}

int
Exception_handler::is_ignore_action()
{
  return Exception_handler::RUNNING__;
}


void
Exception_handler::throw_exception_signal(string message)
{
  // convert msg to c-string
  const char* msg = message.c_str();
  fprintf(stderr, "%s(): message '%s'\n", __func__, msg);

  /*
    prepare message and issue signal
  */
  union sigval value;
  value.sival_ptr = (void *) msg;
  sigqueue(Exception_handler::get_pid(), SIGUSR1, value);
}

Exception_handler&
Exception_handler::get_instance()
{
  static std::unique_ptr< Exception_handler, Exception_handler_deleter > inst(new Exception_handler());
  return *inst;
}

void
Exception_handler::serve_async_exceptions()
{
  fprintf(stderr, "%s() started\n", __func__);

  while (Exception_handler::is_ignore_action()) {
    std::this_thread::sleep_for(std::chrono::seconds(60));
  }

  // do some cleanup / take measure when exception was thrown
  fprintf(stderr, "%s(): XXX do some cleanup actions goes here...\n", __func__);
}

// CTOR / DTOR / ...
Exception_handler::Exception_handler()
{
  register_sighandler();
  set_pid(getpid());
}
