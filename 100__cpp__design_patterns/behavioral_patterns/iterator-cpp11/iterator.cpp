// iterator.cpp
/*
  Provide a way to access the elements of an aggregate Object sequentially
  without exposing its underlying representation.

  +---------------------+       +--------+       +---------------------+
  | Aggregate           |<------| Client |------>| Iterator            |
  +=====================+       +--------+       +=====================+
  | createIterator()    |                        | first()             |
  +---------------------+                        | next()              |
           /_\                                   | isDone()            |
            |                                    | currentItem()       |
            |                                    +---------------------+
            |                                              /_\
            |                                               |
  +---------------------+                        +---------------------+
  | ConcreteAggregate   |- - - - - - - - - - - ->|  ConcreteIterator   |
  +=====================+                        +=====================+
  |                     |<-----------------------|                     |
  +---------------------+                        +---------------------+
  | createIterator()    |                        | first()             |
  +------------------|--+                        | next()              |
                                                 | isDone()            |
                     |                           | currentItem()       |
                                                 +---------------------+
                     |
                +-----------------------------------+\
                | return new ConcreteIterator(this) +-+
                +-------------------------------------+
  (GoF, 1995)
//*/


#include <iostream>


/*
  forward declaration and additional "helpers"
//*/
struct IteratorOutOfBounds : public std::exception {
};

template < class Item >
class Aggregate;
template < class Item >
class ConcreteAggregate;
template < class Item >
class Iterator;
template < class Item >
class ConcreteIterator;


/*
  Aggregate, e.g. a list, vector, or something like

  - defines an interface for creating an Iterator object
//*/
template < class Item >
class Aggregate
{
protected:
  Item *pItems_;
  Iterator< Item > *pIter_;
  signed long size_;
  signed long count_;

public:
  Aggregate(const signed long size)
      : pItems_(nullptr), pIter_(nullptr), size_(size), count_(0)
  {
    std::cout << "\tAggregate::Aggregate(signed long)\n";

    // allocation
    try {
      pItems_ = new Item[size_ + 1];
    } catch (std::bad_alloc &) {
      std::cerr << "Allocation failed!\n";
    }

    // init
    for (int idx = 0; idx < size_; ++idx) {
      pItems_[idx] = "";
    }
  }

  virtual ~Aggregate()
  {
    std::cout << "Aggregate< Item >::~Aggreagte() - dtor\n";
    delete[] pItems_;
    pItems_ = nullptr;
  }

  virtual Iterator< Item > *createIterator() const = 0;
  virtual signed long count() const = 0;
  virtual Item *getItem(signed long idx) const = 0;
};


/*
  ConcreteAggregate

  - implements the Iterator creation interface to return an instance of the
  proper ConcreteIterator
//*/
template < class Item >
class ConcreteAggregate : public Aggregate< Item >
{
public:
  ConcreteAggregate(const signed long size) : Aggregate< Item >(size)
  {
    std::cout << "\tConcreteAggregate< Item >::ConcreteAggregate( signed long) "
                 "- ctor\n";
  }

  Iterator< Item > *createIterator() const
  {
    std::cout << "\tConcreteAggregate< Item >::createIterator()\n";
    return new ConcreteIterator< Item >(this);
  }

  signed long count() const
  {
    std::cout << "\tConcreteAggregate< Item >::count()\n";
    return this->count_;
  }

  Item *getItem(signed long idx) const
  {
    std::cout << "\tConcreteAggregate< Item >::getItem( signed long)\n";
    return &(this->pItems_)[idx];
  }

  // just dummy to populate the list
  void push(const Item item)
  {
    std::cout << "\tConcreteAggregate< Item >::push( Item)\n";
    if (this->size_ > this->count_ + 1) {
      this->pItems_[this->count_] = item;
      ++(this->count_);
    } else {
      std::cout << "\tlist is full!\n";
      return;
    }
  }
};


/*
  Iterator

  - defines an interface for accessing and traversing elements
//*/
template < class Item >
class Iterator
{
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual Item currentItem() const = 0;
};


/*
  ConcreteIterator

  - implements the Iterator Interface
  - keeps track of the current position in the traversal of the aggregate
//*/
template < class Item >
class ConcreteIterator : public Iterator< Item >
{
private:
  const ConcreteAggregate< Item > *concAggregate_;
  signed long current_;

public:
  ConcreteIterator(const ConcreteAggregate< Item > *aggregate)
      : concAggregate_(aggregate), current_(0)
  {
    std::cout << "\tConcreteIterator< Item >::ConcreteIterator( const "
                 "Aggregate< Item >* ) - ctor\n";
  }

  virtual void first()
  {
    std::cout << "\tConcreteIterator< Item >::first()\n";
    current_ = 0;
  }

  virtual void next()
  {
    std::cout << "\tConcreteIterator< Item >::next()\n";
    ++current_;
  }

  virtual bool isDone() const
  {
    std::cout << "\tConcreteIterator< Item >::isDone()\n";
    return (current_ >= concAggregate_->count());
  }

  virtual Item currentItem() const
  {
    std::cout << "\tConcreteIterator< Item >::currentItem()\n";
    if (isDone()) {
      throw IteratorOutOfBounds();
    }
    return *(concAggregate_->getItem(current_));
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init aggregate: list\n";
  auto *list = new ConcreteAggregate< string >(32);
  cout << endl;

  cout << "populate list\n";
  list->push("All");
  list->push("Work");
  list->push("And");
  list->push("No");
  list->push("Play");
  list->push("Makes");
  list->push("Jack");
  list->push("A");
  list->push("Dull");
  list->push("Boy");
  cout << endl;

  cout << "set up new iterator\n";
  // CAUTION:
  // the type of the pointer here is:                    "Iterator*"
  // virtual function in base returns:                   "Iterator*"
  // derived function returns and:                       "Iterator*"
  // -> but derived funciton allocates a:                "ConcreteIterator*"
  Iterator< string > *iter = list->createIterator();
  cout << endl;

  cout << "parse with iterator through elements\n";
  for (iter->first(); !iter->isDone(); iter->next()) {
    cout << "item: \'" << iter->currentItem() << "\'" << endl;
  }
  cout << endl;

  // free
  delete list;
  list = nullptr;

  cout << "READY.\n";
  return 0;
}
