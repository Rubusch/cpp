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
// */

#include <iostream>
#include <memory> /* smart pointers */
#include <exception>

class MemoryDisaster : public std::exception
{
public:
  const char* what() const throw()
  {
    return "FIXME: Memory Pool Issues!";
  }
};


/*
  Small allocator as Singleton.

  NOTE: this allocator is a hip shot and not tested at all, the purpose
  of the implementation is to show where and how to fix in a customized allocator
  and not how to implement a correct allocator
// */
class FixedAllocator
{
  static  FixedAllocator* pInstance_;

  static constexpr auto memory_size_ = 10000;
  static int memory_consumed_;
  static uint8_t memory_[memory_size_];

public:
  static FixedAllocator& getInstance();

  void* Allocate( const size_t size )
  {
    std::cout << "CALLED: Allocate()" << std::endl;

// alternative: dynamic allocation with malloc()
//    return malloc(sizeof(void*) * size);

// alternative: static allocation with mem pool (simple)
    size_t header_size = 1; // first item keeps the offset
    size_t alloc_size = header_size + size;


    // check that size is not bigger than capable to keep as offset
    if (sizeof(uint8_t) > alloc_size) throw MemoryDisaster();

    // check if there's still memory
    if (memory_size_ < memory_consumed_ + alloc_size) throw MemoryDisaster();

    uint8_t *ptr = memory_ + memory_consumed_;

    // write offset into first element
    *ptr = alloc_size;

    // shift to 'real' address for user
    ptr = ptr + header_size;

    // book keeping
    memory_consumed_ += alloc_size;

    return (void*) ptr;
  }

  void Deallocate( void* ptr )
  {
    std::cout << "CALLED: Deallocate()" << std::endl;

// alternative: dynamic
//    free(ptr);

// alternative: static pool
    if (nullptr == ptr) throw MemoryDisaster();

    uint8_t* memory_ptr = (uint8_t*) ptr; // FIXME
    size_t header_size = 1;

    // get address before pointer i.e. the header and read out stored offset value
    size_t offset = *(memory_ptr - header_size);

    // compute alloc_size
    size_t alloc_size = header_size + offset;

    if (0 > memory_consumed_ - alloc_size) throw MemoryDisaster();
    memory_consumed_ -= alloc_size;
  }

private:
  FixedAllocator() = default;
  ~FixedAllocator() = default;
  FixedAllocator(const FixedAllocator&) = delete;
  const FixedAllocator& operator=( FixedAllocator const& ) = delete;
};

// separate declaration due to 'static'
int FixedAllocator::memory_consumed_ = 0;
uint8_t FixedAllocator::memory_[FixedAllocator::memory_size_];
FixedAllocator* FixedAllocator::pInstance_;

// separate declaration due to 'static'
FixedAllocator&
FixedAllocator::getInstance()
{
  if (nullptr == pInstance_) {
    pInstance_ = new FixedAllocator(); // OK, if not supposed to be killed
    if (nullptr == pInstance_) {
      std::cerr << "ERROR: Singleton instantiation failed!" << std::endl;
    }
  }
  return *pInstance_;
}

struct FastArenaObject
{
  virtual ~FastArenaObject() = default;

  // ALWAYS when implementing 'operator new()', also implement 'operator delete()'
  // and vice versa!!!
  static void* operator new( size_t s)
  {
    return FixedAllocator::getInstance().Allocate(s);
  }

  static void operator delete( void* p)
  {
    FixedAllocator::getInstance().Deallocate(p);
  }
};

struct WorkerImpl : public FastArenaObject
{
  virtual ~WorkerImpl() = default;

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
  virtual ~ConcWorkerImpl() = default;

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
