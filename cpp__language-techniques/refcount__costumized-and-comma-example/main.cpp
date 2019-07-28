// main.cpp
/******************************************************************************
 *                                                                             *
 *        Code from Item 29 ("Reference Counting") of MORE EFFECTIVE C++       *
 *                                                                             *
 *                               Scott Meyers                                  *
 *                                                                             *
 *            Copyright 1996 (c) Addison-Wesley Publishing Company             *
 *       You are free to use this code for non-commercial purposes only.       *
 *                                                                             *
 * This page contains the code for the classes and class templates making up   *
 * the Reference Counting Item of More Effective C++.  To use this code,       *
 * either copy this page and paste it into a C++ source file or save the       *
 * entire page as text into a C++ source file.  Don't save the HTML source     *
 * and expect that to compile :-)                                              *
 *                                                                             *
 * Each class or template in this file follows a block comment that shows the  *
 * corresponding pages in the book.  This page also contains a main function   *
 * that performs a VERY limited test of the code in this file.  You can        *
 * compile the code in this file as a stand-alone program, and you should get  *
 * this output:                                                                *
 *                                                                             *
 *     SomeClass with no changes.                                                 *
 *     SomeClass with    changes.                                                 *
 *     10                                                                      *
 *     -1                                                                      *
 *                                                                             *
 * The code here reflects all changes made to date in response to bug reports  *
 * from readers of the book.  (To see a complete list of known bugs in More    *
 * Effective C++, as well as whether they've been fixed yet, visit the         *
 * More Effective C++ Errata List.)  If you find any additional bugs, please   *
 * send them to me.                                                            *
 *******************************************************************************

  Reference counting example of Scott Meyers - "simple" and for "existing
  objects"



  The General Implementation of Reference Counting

  Some data structures (e.g., directed graphs) lead to self-referential
  or circular dependency structures. Such data structures have a tendency
  to spawn isolated collections of objects, used by no one, whose reference
  counts never drop to zero. That's because each object in the unused
  structure is pointed to by at least one other object in the same structure.
  Industrial-strength garbage collectors use special techniques to find such
  structures and eliminate them, but the simple reference-counting approach
  we've examined here is not easily extended to include such techniques.

  (More Effective C++ / 29 / Meyers)

  - Relatively few values are shared by relatively many objects. Such sharing
  typically arises through calls to assignment operators and copy constructors.
  The higher the objects/values ratio, the better the case for
  reference counting.

  - Object values are expensive to create or destroy, or they use lots of
  memory. Even when this is the case, reference counting still buys you
  nothing unless these values can be shared by multiple objects.


  The Idea of Reference Counting in case of a Customized Implementation

                                 +------------------+
                                 |                  |
                                 | RCObject         |
                                 |                  |
                                 +------------------+
                                            /_\
                                             |
                                             | inherits to inner class
                                             | SomeClassValue
                                             |
                                 +-----------|------+
                                 | SomeClass |      |
                                 |           |      |
                      type:      |           |      |
    +---------------+ <SomeClass |           |      |
    |               |   Value>   |           |      |
    | RCPtr         |<---------<>|           |      |
    |  (Smart Ptr)  |    (var)   |+--------------+  |          +----------------+
    +---------------+            ||              |  |  points  | unspecified    |
       < >                       ||SomeClassValue|<>---------->| data, here     |
        |                        ||(inner class) |  |    to    | char*          |
        |                        |+--------------+  |          +----------------+
        |                        +----------/|\-----+
        |                                    |
        +------------------------------------+

   - RCObject could also be "real" protocoll class for reference counting
   - RCPtr is a smart pointer used by SomeClass to point to the inner class SomeClassValue
   - SomeClassValue implements the idea of reference counting and common data itself
   - SomeClass is a client that also holds a smart pointer to the SomeClassValue object
   - unspecified data can be stored shared / not-shared, copy on write is also possible



   The Idea of Reference Counting in case of a "General Implementation"

                                 +------------------+
                                 |                  |
                                 | RCObject         |
                                 |                  |
                                 +------------------+
                                         /_\
                                          |
                                          | inherits to inner class
                                          | CountHolder
                                          |
                                 +--------|---------+
                                 | RCIPtr |    smart|
                                 |   < >  |      ptr|
                                 |    |   |         |
    +---------------+  type:     |    |   |         |
    |               |  <Widget>  |    |   |         |
    | RCWidget      |<>--------->|   \|/  |         |
    |               |    (var)   |+-------------+   |          +----------------+
    +---------------+            ||             |   |  points  |                |
                                 || CountHolder |<>----------->| Widget         |
                                 ||(inner class)|   |    to    |                |
                                 |+-------------+   |          +----------------+
                                 +------------------+

   - RCObject could also be "real" protocoll class for reference counting
   - RCIPtr is a smart pointer that maintains a reference counting class: CountHolder
   - CountHolder implements the idea of reference counting and common data itself
   - RCWidget is a client that initializes the RCI Pointer with the type "Widget"
   - Widget will be the representation of "data" to store shared / not-shared
*/


#include <iostream>
/*
  The iostream facilities are not used in the classes in this file,
  but they are used in the code that tests the classes.
//*/

#include <cstring>
/*
  This includes the C string functions, e.g., strlen, strncpy, etc.
  They are used in the implementation of class SomeClass::SomeClassValue.

  The following is for compilers that don't support bool.  Uncomment these
  lines if your compilers lack bool support.  For details on this emulation
  of bool, see More Effective C++, pp. 3-4.

  typedef int bool;
  const bool false = 0;
  const bool true = 1;
//*/


/*******************************************************************************
 * Functions to perform VERY simple test of the above.                         *
 ******************************************************************************/
#include "someclass.hpp"
#include "rcwidget.hpp"


/*
  reference counting without cyclic dependencies
//*/
void testRCPtr()
{
  SomeClass s1 = "SomeClass with no changes.";
  SomeClass s2(s1);

  s2[15] = s2[16] = ' ';

  std::cout << s1 << '\n';      // prints "SomeClass with no changes."
  std::cout << s2 << '\n';      // prints "SomeClass with    changes."
}


/*
  reference counting having cyclic dependencies (widget implementation)
//*/
void testRCIPtr()
{
  RCWidget w1(10);
  RCWidget w2(w1);

  w2.doThis();

  std::cout << w1.showThat() << '\n';       // prints 10
  std::cout << w2.showThat() << '\n';       // prints -1
}


/*
  some main function
//*/
int main()
{
  // reference counting "simple"
  testRCPtr();

  // reference counting "extended - existing files"
  testRCIPtr();

  std::cout << "READY.\n";
  return 0;
}
