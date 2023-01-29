/*
*/

#ifndef EXCEPTION_HANDLER_H__
#define EXCEPTION_HANDLER_H__


//#define _POSIX_C_SOURCE 199309L

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <memory>
#include <future>


static void
sighandler(int signum, siginfo_t *info, void *ptr);


class Exception_handler
{
private:
  static int RUNNING__;
  static pid_t pid_sighandler;
  struct sigaction sa;

  void
  register_sighandler();

  // CTOR / DTOR / ...
  Exception_handler();
  Exception_handler(const Exception_handler&) = delete;
  const Exception_handler &operator=(Exception_handler const&) = delete;
  Exception_handler(Exception_handler&&) = delete;
  Exception_handler& operator=(Exception_handler&&) = delete;
  ~Exception_handler() = default;

  struct Exception_handler_deleter;

public:

  static void set_pid(pid_t pid);
  static pid_t get_pid();

  static void ignore_action();
  static void do_action();
  static int is_ignore_action();

  static void throw_exception_signal(std::string message);

  static void serve_async_exceptions();

  static Exception_handler& get_instance();
};

struct Exception_handler::Exception_handler_deleter
{
  void operator()(const Exception_handler* const ptr)
  { delete ptr; }
};


// c code

static void
sighandler(int signum, siginfo_t *info, void *ptr)
{
  // ATTENTION:
  // using stdio in signal handler is not async-signal-safe
  // ref.:
  // Linux Programming Interface, Michael Kerrisk, 2010, p.426
  fprintf(stderr, "%s() caught exception\n", __func__);

//*
  // passing a string "bla bla"
  void (*fptr)(const char *);
  const char * msg = (const char *) info->si_value.sival_ptr;
  fprintf(stderr, "%s(): message '%s' received\n", __func__, msg);
/*/
  // passing a function foo()
  void (*fptr)();
  fptr = (void (*)()) info->si_value.sival_ptr;
  fptr();
// */

  Exception_handler::do_action();
}

// c code - end


#endif /* EXCEPTION_HANDLER_H__ */
