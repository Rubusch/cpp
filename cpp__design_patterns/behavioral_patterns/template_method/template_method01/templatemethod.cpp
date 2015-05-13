// templatemethod.cpp
/*
  Define the skeleton of an algorithm in an operation, deferring some steps 
  to subclasses. 
  Template Method lets a subclasses redefine certain steps in an algorithm
  without changing the algorithm's structure.

  +---------------------+
  | AbstractClass       |
  +=====================+
  |                     |
  +---------------------+     +---------------------+\
  | templateMethod() - - - - -| operation1()        +-+
  | operation1()        |     | operation2()          |
  | operation2()        |     | ...                   |
  +---------------------+     +-----------------------+ 
           /_\
            |
            |
            |
  +---------------------+    
  | ConcreteClass       |
  +=====================+
  |                     |
  +---------------------+
  | operation1()        |
  | operation2()        |
  +---------------------+

  template methods call the following kinds of operations:
  - concrete operations (either on the ConcreteClass or on client classes)
  - concrete AbstractClass operations (i.e., operations that are generally 
  useful to subclasses)
  - primitive operations (i.e., abstract operations)
  - factory methods
  - hook operations which provide default behavior that subclasses can 
  extend if necessary. A hook operation often does nothing by default.

  (GoF, 1995)
//*/

#include <iostream>


/*
  AbstractClasss 

  - defines abstract primitive operations that concrete subclasses define to 
  implement steps of an algorithm.

  - implements a template method defining the skeleton of an algorithm. The 
  template method calls primitive operations as well as operations defined in
  AbstractClass or those of other objects.
//*/
class AbstractClass
{
public:
  int templateMethod(int arg)
  {
    std::cout << "\tAbstractClass::templateMethod(int&)\n";
    operation1(arg);
    std::cout << "\t\t...increment\n";
    ++arg;
    operation2(arg);
    std::cout << "\t\t...increment\n";
    ++arg;
    operation3(arg);
    std::cout << "\t\t...increment\n";
    ++arg;

    return arg;
  }

protected:  
  virtual void operation1(int& arg)
  {
    std::cout << "\tAbstractClass::operation1( int&)\n";
    std::cout << "\t\t...do nothing or default\n";
  }

  virtual void operation2(int& arg)
  {
    std::cout << "\tAbstractClass::operation2(int&) - do nothing or default\n";
    std::cout << "\t\t...do nothing or default\n";
  }

  virtual void operation3(int& arg)
  {
    std::cout << "\tAbstractClass::operation3(int&) - do nothing or default\n";
    std::cout << "\t\t...do nothing or default\n";
  }      
};


/*
  ConcreteClass1 - a ConcreteClass
  
  - implements the primitive operations to carry out subclass-specific steps of 
  the algorithm.
//*/
class ConcreteClass1
  : public AbstractClass
{
protected:
  void operation1(int& arg)
  {
    std::cout << "\tConcreteClass1::operation1( int&)\n";
    int val = 10;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
  
  void operation2(int& arg)
  {
    std::cout << "\tConcreteClass1::operation2( int&)\n";
    int val = 20;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }

  void operation3(int& arg)
  {
    std::cout << "\tConcreteClass1::operation3( int&)\n";
    int val = 30;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
};


/*
  ConcreteClass2 - a ConcreteClass
  
  - implements the primitive operations to carry out subclass-specific steps of 
  the algorithm.
//*/
class ConcreteClass2
  : public AbstractClass
{
protected:
  void operation1(int& arg)
  {
    std::cout << "\tConcreteClass2::operation1( int&)\n";
    int val = 10;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
  
  void operation3(int& arg)
  {
    std::cout << "\tConcreteClass2::operation3( int&)\n";
    int val = 50;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
};


int main()
{
  using namespace std;

  cout << "init\n";
  int value = 1;
  cout << endl;

  cout << "algoritm 1 - full\n";
  ConcreteClass1 full_algorithm;
  cout << "original value = " << value << ", after: " << full_algorithm.templateMethod(value) << "\n";
  cout << endl;

  cout << "algorithm 2 - only step 1 and step 3 (changed)\n";
  ConcreteClass2 partly_algorithm;
  cout << "original value = " << value << ", after: " << partly_algorithm.templateMethod(value) << "\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
