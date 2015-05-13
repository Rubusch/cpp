// memorypool.cpp
/*
  demonstrates the usage of a memory pool, the memory pool only contains a dummy implementation and is 
  therefore completely stubbed, since there might be several strategies possible, especially to handle 
  and avoid internal fragmentation.

  Since this is kind of tricky and I'm a lowrider I didn't implement the memory pool here ;)
//*/


#include <iostream>
#include <new>  // if <new> doesn't compile, try <new.h>

class Memorypool;
class Foobar;
class FoobarRepresentation;


/*
  This class is rather an interface than a real implemenation, because the acurate
  implementation allows various strategies to handle the fragmentation problem. 
//*/
class Memorypool
{
private:
  // e.g. a basic possiblity might be this here..
  const unsigned int BLOCKS;
  void* pSpace;

public:
  Memorypool(size_t size);
  ~Memorypool();

  void* alloc(size_t size);
  void free(void* ptr, size_t size);
};

Memorypool::Memorypool(size_t size)
  :BLOCKS(size)
{
  std::cerr << "Memorypool - ctor(" << size << ")" << std::endl; // some comment  
  pSpace = ::operator new(BLOCKS);
}

Memorypool::~Memorypool()
{
  std::cerr << "Memorypool - dtor" << std::endl; // some comment
  free(pSpace, BLOCKS); // quickfix
}

void* Memorypool::alloc(size_t size)
{
  std::cerr << "allocation of " << size << " bytes of memory from the pool" << std::endl; // some comment

  /*
    Here generally a section of the already allocated memory will be returned and will
    be marked as "used".
  //*/

  if(BLOCKS != size) return NULL;

  pSpace = ::operator new(size); // quickfix
  void* ptr = pSpace; // quickfix

  return ptr;  
}

void Memorypool::free(void* ptr, size_t size)
{
  std::cerr << "cleaning " << size << " bytes of memory!" << std::endl; // some comment

  /*
    Generally here nothing will be freed, only the used section will be marked as 
    "available" again.

    Caution: this is tricky!

    If e.g. something within the middle of the memory section will be removed, a
    a form of inner fragmentation will raise up (several strategies are possible, 
    e.g. buddy syste, etc..)
   
    *** Therefore here no implementation of free(), sry! ***
    This is not a memory leak, though, there's still a pointer (of MemoryPool) pointing to 
    the memory. Only in case the buffer is used up, there's no more memory, that's all!
  //*/    

  if(ptr != pSpace) return; // quickfix - ptr is not (part of) pSpace

  // else free
  ::operator delete(pSpace);  // quickfix
  pSpace = NULL; // quickfix
}


class FoobarRepresentation
{
  // ...
};


class Foobar
{
public:
  // ...

  static void* operator new(size_t size);
  static void operator delete(void* ptr, size_t size);
  
private:
  FoobarRepresentation* rep; 
  static Memorypool pool;
};

inline void* Foobar::operator new(size_t size)
{
  std::cerr << "overloaded Foobar::operator new()" << std::endl; // some comment
  return pool.alloc(size);
}

inline void Foobar::operator delete(void* ptr, size_t size)
{
  std::cerr << "overlaoded Foobar::operator delete()" << std::endl; // some comment
  pool.free(ptr, size);
}

// creation of the memory pool for Foobar objects, this is defined in the source 
// file of the Foobar class
Memorypool Foobar::pool(sizeof(Foobar));


int main()
{
  Foobar * pFoobar = new Foobar;

  // do something...

  delete pFoobar; pFoobar = NULL;

  pFoobar = new Foobar;

  // do something...

  delete pFoobar; pFoobar = NULL;


  std::cout << "READY.\n" << std::endl;
  return 0;
}
