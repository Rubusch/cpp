// composite.cpp
/*
  Compose objects into tree structures to represent part-whole hierarchies.
  Composite lets clients treat individual objects and compositions of
  objects uniformly.

  +--------+      +---------------------+
  | Client |----->| Component           |
  +--------+      +=====================+
                  |                     |<-------------------+
                  +---------------------+    children        |
                  | operation()         |                    |
                  | add( Component*)    |                    |
                  | remove( Component*) |                    |
                  | getChild( int)      |                    |
                  +---------------------+                    |
                            /_\                              |
                             |                               |
             +---------------+--------------+                |
             |                              |                |
  +---------------------+        +---------------------+     |
  | Leaf                |        | Composite           |<>---+
  +=====================+        +=====================+
  |                     |        |                     |      +----------------------+\
  +---------------------+        +---------------------+      | for all g : children +-+
  | operation()         |        | operation() - - - - - - - -| g.operation()          |
  +---------------------+        | add( Component*)    |      +------------------------+
                                 | remove( Component*) |
                                 | getChild( int)      |
                                 +---------------------+

  (GoF, 1995)
//*/


#include <iostream>
#include <vector>
#include <algorithm>


struct Component
{
  virtual ~Component(){}
  virtual void operation() = 0;
  virtual void add(Component*){}
  virtual void remove(Component*){}
  virtual Component* getChild(int){ return NULL; }
};


struct Leaf
  : public Component
{
  void operation(){ std::cout << "-> operation in a Leaf class\n"; }
};


class Composite
  : public Component
{
private:
  std::vector< Component* > components_;

  // forbid copying
  Composite( Composite const&);

public:
  Composite(){}

  void operation()
  {
    std::cout << "-> operation in the Composite class\n";

    // remember avoid for loops: check mem_fun()
    std::for_each( components_.begin(), components_.end(), std::mem_fun(&Component::operation));
  }

  void add( Component *pComponent)
  {
    if(NULL == pComponent) return;
    components_.push_back( pComponent);
  }

  void remove( Component *pComponent)
  {
    if(NULL == pComponent) return;

    // remember: end() points AFTER the last element
    std::vector< Component* >::iterator iter = std::find(components_.begin(), components_.end(), pComponent);

    // remember: if find failed, it points to the last index, hence end() which is outside the vector
    if(iter == components_.end()) return;

    components_.erase( iter);
  }

  Component* getChild( int idx)
  {
    return components_.at(idx);
  }
};


int main()
{
  using namespace std;

  cout << "init..\n";
  Composite composite;
  Leaf leaf;
  cout << endl;

  composite.add(&leaf);
  cout << endl;

  composite.operation();
  cout << endl;

  composite.remove(&leaf);
  cout << endl;

  composite.operation();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
