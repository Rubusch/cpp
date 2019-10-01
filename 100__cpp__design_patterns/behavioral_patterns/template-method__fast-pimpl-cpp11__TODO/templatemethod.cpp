// templatemethod.cpp
/*
  Define the skeleton of an algorithm in an operation, deferring some steps
  to subclasses.
  Template Method lets a subclasses redefine certain steps in an algorithm
  without changing the algorithm's structure.

  +---------------------+             +---------------------+
  | Worker              |             | WorkerImpl          |
  +=====================+  private    +=====================+
  | *pImpl_ [private]   |<>-----------|                     |
  +---------------------+             +---------------------+
  | templateMethod()    |             | operation1() [virt] |
  +---------------------+             | operation2() [virt] |
                                      +---------------------+
                                                A
                                                | (opt)
                                                |
                                      +---------------------+
                                      | SpecialClassImpl    |
                                      +=====================+
                                      |                     |
                                      +---------------------+
                                      | ...                 |
                                      +---------------------+



  template methods call the following kinds of operations:
  - concrete operations (either on the ConcreteClass or on client classes)
  - concrete Worker operations (i.e., operations that are generally
  useful to subclasses)
  - primitive operations (i.e., abstract operations)
  - factory methods
  - hook operations which provide default behavior that subclasses can
  extend if necessary. A hook operation often does nothing by default.



  NOTE

  This design works rather with aggregation instead of inheritance, which is
  preferable. Inheritance brings in a higher complexity and thus more problems
  in maintenance.



  RESOURCES

  * Design Patterns, GoF, 1995

  * Exceptional C++, Herb Sutter, 2000
//*/

#include <iostream>


struct WorkerImpl
{
  virtual ~WorkerImpl(){}

  virtual void operation1(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation1( int&)\n";
    auto val = 10;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }

  virtual void operation2(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation2( int&)\n";
    auto val = 20;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }

  virtual void operation3(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation3( int&)\n";
    auto val = 30;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
};


struct ConcWorkerImpl
: public WorkerImpl
{
  void operation1(int& arg) const
  {
    std::cout << "\tConcreteClass2::operation1( int&)\n";
    auto val = 10;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }

  void operation3(int& arg) const
  {
    std::cout << "\tConcreteClass2::operation3( int&)\n";
    auto val = 50;
    std::cout << "\t\t...add " << val << "\n";
    arg += val;
  }
};


/*
  Workers

  - defines abstract primitive operations that concrete subclasses define to
  implement steps of an algorithm.

  - implements a template method defining the skeleton of an algorithm. The
  template method calls primitive operations as well as operations defined in
  Worker or those of other objects.
//*/
class Worker
{
public:
  Worker(const WorkerImpl& pImpl)
  {
    pImpl_ = &pImpl;
  }

  virtual ~Worker()
  {}
  int templateMethod(int arg)
  {
    std::cout << "\tWorker::templateMethod(int&)\n";
    pImpl_->operation1(arg);
    std::cout << "\t\t...increment\n";
    ++arg;
    pImpl_->operation2(arg);
    std::cout << "\t\t...increment\n";
    ++arg;
    pImpl_->operation3(arg);
    std::cout << "\t\t...increment\n";
    ++arg;

    return arg;
  }

private:
  const WorkerImpl *pImpl_;
};


int main()
{
  using namespace std;

  cout << "init\n";
  int value = 1;
  cout << endl;

  cout << "algoritm 1 - full\n";
  WorkerImpl full_algorithm;
  Worker *pAlgo = new Worker(full_algorithm);
  cout << "original value = " << value << ", after: " << pAlgo->templateMethod(value) << "\n";
  cout << endl;

  cout << "algorithm 2 - only step 1 and step 3 (changed)\n";
  ConcWorkerImpl partly_algorithm;
  Worker *pSpecialAlgo = new Worker(partly_algorithm);
  cout << "original value = " << value << ", after: " << pSpecialAlgo->templateMethod(value) << "\n";
  cout << endl;

  delete pAlgo;
  delete pSpecialAlgo;

  cout << "READY.\n";
  return 0;
}
