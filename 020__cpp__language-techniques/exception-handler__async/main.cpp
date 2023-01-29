/*
  The demo shows an excpetion handler for asynchronous exceptions
  e.g. from threads or asynchronous sub-processes.
*/

#include "exception_handler.h"

#include <iostream>
#include <future>

#include <signal.h>

using namespace std;

void
do_something()
{
  // TODO demo for a try/catch exception escalation     
  fprintf(stderr, "%s(): throw exception...\n", __func__);    
  Exception_handler::throw_exception_signal("EXCEPTION TEXT");
}

int main()
{
  fprintf(stderr, "%s(): initialize\n", __func__);    
  Exception_handler &eh = Exception_handler::get_instance();
  {
    auto future = std::async(std::launch::async, [&eh]{eh.serve_async_exceptions;});
  }

  fprintf(stderr, "%s(): execute some code\n", __func__);    
  sleep(5);
  do_something();

  return EXIT_SUCCESS;
}
