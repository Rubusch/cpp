// test.h

#include <iostream>
#include <pthread.h>

class MemberThread
{
 private:
  pthread_t thread;
  
 public:
  MemberThread();
  void thread_init();
  void thread_routine(); 

 private:
  static void* thread_maker(void* self);
};

