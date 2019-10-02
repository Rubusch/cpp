// singleton.cpp
/*
  Ensure a class only has one instance, and provide a global point of access to it.

  +-----------------------+
  | Singleton             |
  +-----------------------+
  | private:              |
  | Singleton *pInstance_ |<----+
  +-----------------------+     |
  | private:              |     |
  | Singleton()           |     |
  |                       |     |
  | public:               |     |
  | getInstance()         |-----+
  +-----------------------+

  Destruction of the Singelton

  The Singleton should not be destroyed by the user! The only correct
  way to avoid resource leaks is to delete the Singleton object during
  the application's shutdown.

  No Memory leak?
  Actually, if Singleton is not deleted, that's not a memory leak. Memory
  leaks appear when you allocate accumulating data and lose all references
  to it. This is not the caase here: Nothing is accumulating, and we hold
  knowledge about the allocated memory until the end of the application.
  Furthermore, all modern operating systems take care of completely
  deallocating a process's memory upon termination. (For an interesting
  discussion on what is and is not a memory leak, refer to Item 10 in
  Effective C++, Meyers, 1998).

  However, there is a leak, and a more insidious one: a resource leak.

  To achieve this the following strategies are possible:
   - return a reference instead of a pointer:

       static Singeton& Singleton::getInstance()

     a variante is to return a local instance:
       static Singleton& Singleton::getInstance()
       {
         static Singeton obj;
         return obj;
       }

    the local instance dies out due to language ruels.

   - return a pointer and make the destructor private, to
     avoid deleting the instance.

  (GoF, 1995)
//*/


#include <iostream>
#include <memory>

/*
  Singleton

  - defines an instance operation that lets clients access its unique instance.
  Instance  is a class operation (that is, a class method in Smalltalk and a static
  member function in C++)
  - may be responsible for creating its own unique instance
//*/
class Singleton
{
private:
  static Singleton* pInstance_;

  // only one instance -> private ctor
  Singleton()
  {
    std::cout << "Singleton::Singleton() - ctor\n";
  }

  // no copy constructor -> private
  Singleton(const Singleton&) = delete;

  // no assignment -> private
  const Singleton& operator=( Singleton const&) = delete;

  // no public dtor -> private, will never be called
  ~Singleton() = delete; // NOTE: depends... see discussion in Alexandrescu's Modern C++

public:
  // global point of access
  static Singleton* getInstance()
  {
    if (nullptr == pInstance_) {
      pInstance_ = new Singleton(); // OK, if the Singleton is not supposed to be killed and restarted (see discussion in Alexandrescu)
      if (nullptr == pInstance_) {
        std::cerr << "ERROR: Singleton instantiation failed!\n";
      }
    }
    return pInstance_;
  }

  // a Singleton function
  void doSomething()
  {
    std::cout << "Singleton::doSomething() - some function\n";
  }
};

// static initialization: outside of class definition!
Singleton* Singleton::pInstance_ = nullptr;


/*
  main..
//*/
int main()
{
  using namespace std;

  // pointer to the static singleton instance
  auto ptr = Singleton::getInstance();

  do{
    cout << "create Singleton:\n";
    if (nullptr == ptr) {
      cout << "Singleton allocation failed!\n";
      break;
    }
    cout << endl;

    cout << "use the Singleton\n";
    ptr->doSomething();
    cout << endl;

    cout << "destroy Singleton.. - is not permitted!\n";
  } while (false);

  cout << "READY.\n";
  return 0;
}
