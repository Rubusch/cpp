// test.cpp

#include "test.h"

// c style assert
#include <cassert>

// needs to be declared .h
#include <pthread.h>


MemberThread::MemberThread()
{
  // inner thread, called within the class creation
  thread_init();
}


/*
  step 1

  thread initialization
//*/
void MemberThread::thread_init()
{
  pthread_create(&thread, NULL, &MemberThread::thread_maker, static_cast< void* >(this));
}


/*
  step 2

  Not possible if this was not declared "static" in the class definition.
  On the other side HERE NO STATIC declaration!

  (-> Boost Threads)
//*/
void* MemberThread::thread_maker(void* self)
{
  assert(self);
  static_cast< MemberThread* >(self)->thread_routine();

  return NULL;
}


/*
  step 3

  the thread routine, due to the static thread_maker needs to be declared
  "public"
//*/
void MemberThread::thread_routine()
{
  std::cout << "Hello World!\n";
}


/*
  main...
*/
int main(int argc, char** argv)
{
  MemberThread mt;

  // outer thread
  mt.thread_init();

  // called a third time due to the static function and the ctor of that
  // classes instance - or... call up to three times

  return 0;
}
