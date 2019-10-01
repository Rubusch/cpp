// templatemethod.cpp
/*
  The Fast Impl is a tuning for the Template Method, in case allocation /
  deallocation becomes a performance issue. Further it shows a combination of
  the Template Pattern with a use case for a Singleton Pattern.

  First make things correct, before trying to make them fast (tuning)!!!

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
#include <memory> /* smart pointers */


/* TODO     
class FixedAllocator
{
public:
  static FixedAllocator& Instance();
  void* Allocate( size_t );
  void Deallocate( void* );
private:
  // singleton
  // TODO
};

struct FastArenaObject
{
  // ALWAYS when implementing 'operator new()', also implement 'operator delete()'
  // and vice versa!!!
  static void* operator new( size_t s)
  {
    return FixedAllocator::Instance()->Allocate(s);
  }
  static void operator delete( void* p)
  {
    FixedAllocator::Instance()->Deallocate(p);
  }
};


struct WorkerImpl : private FastArenaObject
{
  // TODO: private elements here
};
// */

struct WorkerImpl
{
  virtual ~WorkerImpl(){}

  virtual void operation1(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation1( int&)\n";
    auto val = 10;
    std::cout << "\t\t...add " << val << std::endl;
    arg += val;
  }

  virtual void operation2(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation2( int&)\n";
    auto val = 20;
    std::cout << "\t\t...add " << val << std::endl;
    arg += val;
  }

  virtual void operation3(int& arg) const
  {
    std::cout << "\tConcreteClass1::operation3( int&)\n";
    auto val = 30;
    std::cout << "\t\t...add " << val << std::endl;
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
    std::cout << "\t\t...add " << val << std::endl;
    arg += val;
  }

  void operation3(int& arg) const
  {
    std::cout << "\tConcreteClass2::operation3( int&)\n";
    auto val = 50;
    std::cout << "\t\t...add " << val << std::endl;
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
    pImpl_ = std::make_unique< WorkerImpl >( pImpl );
  }

  virtual ~Worker()
  {}

  int templateMethod(int arg) const
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
  std::unique_ptr< WorkerImpl > pImpl_;
};


int main()
{
  using namespace std;

  cout << "init\n";
  auto value = 1;
  cout << endl;

  cout << "algoritm 1 - full" << endl;
  auto full_algorithm = WorkerImpl();
  auto pAlgo = std::make_unique< Worker >(full_algorithm);
  cout << "original value = " << value << ", after: " << pAlgo->templateMethod(value) << endl;
  cout << endl;

  cout << "algorithm 2 - only step 1 and step 3 (changed)" << endl;
  auto partly_algorithm = ConcWorkerImpl();
  auto pSpecialAlgo = std::make_unique< Worker >( partly_algorithm);
  cout << "original value = " << value << ", after: " << pSpecialAlgo->templateMethod(value) << endl;
  cout << endl;

  cout << "READY." << endl;
  return 0;
}
