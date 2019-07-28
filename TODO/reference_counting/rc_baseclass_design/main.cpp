// main.cpp
/*
  Where is the copy constructor? Where is the assignment operator? Where is the destructor?
  Something is definitely amiss here.

  We don't need those functions anymore. Sure, copying of String objects is still supported,
  and yes, the copying will correctly handle the underlying reference-counted StringValue
  objects, but the String class doesn't have to provide a single line of code to make this
  happen. That's because the compiler-generated copy constructor for String will automatically
  call the copy constructor for String's RCPtr member, and the copy constructor for that class
  will perform all the necessary manipulations of the StringValue object, including its
  reference count. An RCPtr is a smart pointer, remember? We designed it to take care of the
  details of reference counting, so that's what it does. It also handles assignment and
  destruction, and that's why String doesn't need to write those functions, either.


                                   RCBaseObject
	                        (abstract class)
                                       / \
                                     /_____\
                                        |
                                        | public
                                        | inheritance
                                        |
                                        |
                                        |
                                        |
                              +-------------------------+
                              |SomeClass|               |
            +---------------<>| (obj)   | ...contains:  |
           \|/                |         |               |
     +-----------+            | +-------|-------------+ |
     | RCPtr     |            | |       |             | |
     |      <>--------------------> SomeClassValue <>-------------> data
     | (var/obj) | (smartptr: | |  (inner class obj)  | | ptr/var    (Heap Memory)
     |           | "pointee") | +---------------------+ |
     +-----------+  template  +-------------------------+


//*/


#include <iostream>

#include "someclass.hpp"


/*
  some main function
//*/
int main()
{
  std::string initstring = "*** reference counter data ***";

  // init
  std::cout << "init obj_1\n";
  SomeClass obj_1(initstring.c_str());

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << std::endl;

  // operator= test
  std::cout << "deep copy to obj_2\n";
  SomeClass obj_2; // DON'T call obj_2() - that might be a declaration of a (new) function, not the ctor!
  obj_2 = obj_1;

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << "obj_2: " << obj_2 << std::endl;
  std::cout << std::endl;

  // cpy ctor test
  std::cout << "shallow copy to obj_3\n";
  SomeClass obj_3(obj_1);

  // output
  std::cout << "obj_1: " << obj_1 << std::endl;
  std::cout << "obj_2: " << obj_2 << std::endl;
  std::cout << "obj_3: " << obj_3 << std::endl;
  std::cout << std::endl;

  // output by index
  std::cout << "output on indexes (copy on write - out):\n";
  for(int idx=0; idx < initstring.length(); ++idx){
    std::cout << "obj_1[" << idx << "] \t= " << obj_1[idx] << "\n";
  }
  std::cout << std::endl;

  // done
  std::cout << "READY.\n";
  return 0;
}
