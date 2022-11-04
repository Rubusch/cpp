// singleton.cpp
/*
  Ensure a class only has one instance, and provide a global point of
  access to it.

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

  Actually, if Singleton is not deleted, that's not a memory
  leak. Memory leaks appear when you allocate accumulating data and
  lose all references to it. This is not the caase here: Nothing is
  accumulating, and we hold knowledge about the allocated memory until
  the end of the application.  Furthermore, all modern operating
  systems take care of completely deallocating a process's memory upon
  termination. (For an interesting discussion on what is and is not a
  memory leak, refer to Item 10 in Effective C++, Meyers, 1998).

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
*/


#include <iostream>


class Singleton
{
private:
  static Singleton *pInstance_;

  Singleton() {}
  ~Singleton() {}
  Singleton(const Singleton &);
  const Singleton &operator=(Singleton const &);

public:
  static Singleton *getInstance()
  {
    if (NULL == pInstance_) {
      if (NULL == (pInstance_ = new (std::nothrow) Singleton)) {
        std::cerr << "ERROR: Singleton instantiation failed!\n";
        pInstance_ = NULL;
      }
    }
    return pInstance_;
  }

  void doSomething()
  {
    std::cout << "Singleton::doSomething() - some function\n";
  }
};


// static initialization: outside of class definition!
Singleton *Singleton::pInstance_ = NULL;


/*
  main..
*/
int main()
{
  using namespace std;

  Singleton *ptr = NULL;

  do {
    cout << "create Singleton:\n";
    if (NULL == (ptr = Singleton::getInstance())) {
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
