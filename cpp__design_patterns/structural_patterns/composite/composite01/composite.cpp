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
                                           /_\
                                            |
                                            ... (next category level)

  Basic idea is to treat categories or compositions of objects equally as individual objects.

  (GoF, 1995)
//*/


#include <iostream>
#include <vector>
#include <algorithm>


/*
  Component

  - declares the interface for objects in the composition
  - implements default behavior for the interface common to all classes, 
     as appropriate
  - declares an interface for accesing and managing its child components
  - (optional) defines an interface for accessing a component's parent in 
     the recursive structure, and implements it if that's appropriate
//*/
class Component
{
public:
  virtual void operation() = 0;

  virtual void add(Component*)
  {}

  virtual void remove(Component*)
  {}

  virtual Component* getChild(int)
  {
    return NULL;
  }
};


/*
  Leaf

  - represents leaf objects in the composition. A leaf has no children
  - defines behavior for primitive objects in the composition
//*/
class Leaf
  : public Component
{
public:
  void operation()
  {
    std::cout << "\tLeaf::operation()\n";
    std::cout << "-> operation in a Leaf class\n";
  }
};


/*
  Composite
  
  - defines behavior for components having children
  - stores child components
  - implements child-related operations in the Component interface
//*/
class Composite
  : public Component
{
private:
  std::vector< Component* > components_;

  // forbid copying
  Composite( Composite const&);

public:
  Composite()
  {
    std::cout << "\tComposite::Composite()\n";
  }

  void operation()
  {
    std::cout << "\tComposite::operation()\n";
    std::cout << "-> operation in the Composite class\n";
    
    // remember avoid for loops: check mem_fun()
    std::for_each( components_.begin(), components_.end(), std::mem_fun(&Component::operation)); 
  }
  
  void add( Component *pComponent)
  {
    std::cout << "\tComposite::add( Component*)\n";
    if(NULL == pComponent) return;
    components_.push_back( pComponent);
  }

  void remove( Component *pComponent)
  {
    std::cout << "\tComposite::remove( Component*)\n";
    if(NULL == pComponent) return;
    
    // remember: end() points AFTER the last element
    std::vector< Component* >::iterator iter = std::find(components_.begin(), components_.end(), pComponent); 
    
    // remember: if find failed, it points to the last index, hence end() which is outside the vector
    if(iter == components_.end()) return;

    components_.erase( iter);
  }

  Component* getChild( int idx)
  {
    std::cout << "\tComposite::getChild( int)\n";
    return components_.at(idx);
  }
};


/*
  main... - client
  
  - manipulates objects in the composition through the Component interface
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Composite composite;
  Leaf leaf;
  cout << endl;

  cout << "add new Leaf object\n";
  composite.add(&leaf);
  cout << endl;

  cout << "call the \'operation\'\n";
  composite.operation();
  cout << endl;

  cout << "remove Leaf object\n";
  composite.remove(&leaf);
  cout << endl;

  cout << "call the \'operation\'\n";
  composite.operation();
  cout << endl;
  
  cout << "READY.\n";
  return 0;
}
