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
struct IteratorOutOfBounds : public std::exception{};

template< class Item > class Iterator;
template< class Item > class ConcreteIterator;


template< class Item >
class Aggregate
{
protected:
  Item *pItems_;
  Iterator< Item > *pIter_;
  signed long size_;
  signed long count_;

public:
  Aggregate(const signed long size)
    : pItems_(NULL), pIter_(NULL), size_(size), count_(0)
  {
    try{    
      pItems_ = new Item[size_+1];     
    }catch(std::bad_alloc&){
      std::cerr << "Allocation failed!\n";
    }

    for(int idx = 0; idx<size_; ++idx){
      pItems_[idx] = "";
    }
  }

  virtual ~Aggregate()
  {
    delete [] pItems_; pItems_ = NULL;
  }

  virtual Iterator< Item >* createIterator() const = 0;
  virtual signed long count() const = 0;
  virtual Item* getItem(signed long idx) const = 0;
};


template< class Item >
struct ConcreteAggregate
  : public Aggregate< Item >
{
  ConcreteAggregate(const signed long size)
    : Aggregate< Item >( size)
  {}

  Iterator< Item >* createIterator() const
  {
    return new ConcreteIterator< Item >(this);
  }

  signed long count() const
  {
    return this->count_;
  }

  Item* getItem(signed long idx) const
  {
    return &(this->pItems_)[idx];
  }

  // just dummy to populate the list
  void push(const Item item)
  {
    if(this->size_ > this->count_ + 1){
      this->pItems_[this->count_] = item;
      ++(this->count_);
    }else{
      std::cout << "\tlist is full!\n";
      return;
    }
  }
};


template< class Item >
struct Iterator
{
  virtual void first() = 0; 
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual Item currentItem() const = 0;
};


template< class Item >
class ConcreteIterator
  : public Iterator< Item >
{
private: 
  const ConcreteAggregate< Item >* concAggregate_;
  signed long current_;

public:
  ConcreteIterator( const ConcreteAggregate< Item >* aggregate)
    : concAggregate_(aggregate), current_(0)
  {}

  virtual void first()
  {
    current_ = 0;
  }

  virtual void next()
  {
    ++current_;
  }

  virtual bool isDone() const
  {
    return (current_ >= concAggregate_->count());
  }

  virtual Item currentItem() const
  {
    if(isDone()){
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
  ConcreteAggregate< string > *list = new ConcreteAggregate< string >( 32);

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

  Iterator< string > *iter = list->createIterator();
  cout << endl;

  for(iter->first(); !iter->isDone(); iter->next()){
    cout << "item: \'" << iter->currentItem() << "\'" << endl;
  }
  cout << endl;

  // free
  delete list; list = NULL;

  cout << "READY.\n";
  return 0;

}
