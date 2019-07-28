#include <iostream>

using namespace std;


struct Node
{
  int data_;
  Node* next;
  Node(int data): data_(data), next(NULL){}
  void add(Node* item)
  {
    if (!next) {
      next = item;
    } else {
      next->add(item);
    }
  }
  void print()
  {
    cout << "Node(" << data_ << ")" << endl;
  }
};


struct Inverter
{
  Node *root_, *revRoot_;
  Inverter(Node* root): root_(root), revRoot_(NULL){};
  Node* getInverse(){
    while(root_) {
        Node* tmp = root_;
        root_ = root_->next;
        tmp->next = revRoot_;
        revRoot_ = tmp;
    }
    return revRoot_;
  }
};


int main()
{
  Node* root=NULL;
  root = new Node(1);
  root->add(new Node(2));
  root->add(new Node(3));

  for( Node* tmp=root; NULL != tmp; tmp=tmp->next){
    tmp->print();
  }
  cout << endl;

  Inverter inv(root);
  root = inv.getInverse();
  for( Node* tmp=root; NULL != tmp; tmp=tmp->next){
    tmp->print();
  }
  cout << endl;

  cout << "READY." << endl;
  return 0;
}
