/*
 rule of zero

 1/5 copy assingment constructor
 2/5 copy move constructor
 3/5 assignment operator
 4/5 assignment move operator
 5/5 destructor

-> are resolved for stl methods by default implementation
-> 0 of the above need to be implemented or all 5

 @author: lothar Rubusch
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Box
{
private:
  const vector<string> *pItem = nullptr;
  int value;

public:
  Box() = default;
  Box(vector<string>* item, int val) : pItem(item), value(val) {}

  const vector<string>& getItem()
  {
    return *pItem;
  }

  void setItem(const vector<string> *item)
  {
    pItem = item;
  }

  const int& getValue()
  {
    return value;
  }
};



int main(void)
{
  cout << "the original pointer address:\n";
  string *pStr = new string("elephant");
  cout << "addr of pStr: \t\t\t\t" << pStr << endl << endl;
  cout << endl;

  cout << "the stl container:\n";
  vector<string> vec;
  vec.push_back(*pStr);
  cout << "addr of 'vec[0]': \t\t\t" << &vec[0] << " <- differs to pStr (implicit move happepened!)" << endl;
  cout << endl;

  cout << "the box with member vector:\n";
  Box box(&vec, 7);
  cout << "addr of 'box.getItem()[0]': \t\t" << &box.getItem()[0] << " <- same as pStr" << endl;
  cout << "addr of 'box.getValue()': \t\t" << &box.getValue() << endl;
  cout << endl;

  cout << "call copy assignment constructor\n";
//  vector<string> copyBox(box);
  Box copyBox(box);
//delete &box.getItem()[0];
  cout << "addr of 'box.getItem()[0]': \t\t" << &box.getItem()[0] << " <- original" << endl;
  cout << "addr of 'copyBox.getItem()[0]': \t" << &copyBox.getItem()[0] << " <-- does NOT differ (default)" << endl;
  cout << "addr of 'box.getValue()': \t\t" << &box.getValue() << endl;
  cout << "addr of 'copyBox.getValue()': \t\t" << &copyBox.getValue() << " <-- differs (copied)" << endl;
  cout << endl;

  cout << "call copy assignment operator\n";
  Box backupBox;
  backupBox = box;
  cout << "addr of 'box.getItem()[0]': \t\t" << &box.getItem()[0] << " <- original" << endl;
  cout << "addr of 'backupBox.getItem()[0]': \t" << &backupBox.getItem()[0] << " <-- does NOT differ (default)" << endl;
  cout << "addr of 'box.getValue()': \t\t" << &box.getValue() << endl;
  cout << "addr of 'backupBox.getValue()': \t" << &backupBox.getValue() << " <-- differs (copied)" << endl;
  cout << endl;

  cout << "call copy move constructor\n";
  Box movedBox = std::move(box);
  cout << "addr of 'box.getItem()[0]': \t\t" << &box.getItem()[0] << " <-- now is NOT null (default)" << endl;
  cout << "addr of 'movedBox.getItem()[0]': \t" << &movedBox.getItem()[0] << " <-- SAME as original" << endl;
  cout << "addr of 'box.getValue()': \t\t" << &box.getValue() << " <-- still the same (not allocated, ignored)" << endl;
  cout << "addr of 'movedBox.getValue()': \t\t" << &movedBox.getValue() << " <-- differes, moved/copied" << endl;
  cout << endl;

  cout << "call copy move operator - separate instantiation and assignment needed\n";
  Box movingBox;
  movingBox = std::move(movedBox);
  cout << "addr of 'movedBox.getItem()[0]': \t" << &movedBox.getItem()[0] << " <-- now is NOT null (default)" << endl;
  cout << "addr of 'movingBox.getItem()[0]': \t" << &movingBox.getItem()[0] << " <-- SAME as move-ctr-box::pItem!!!" << endl;
  cout << "addr of 'movedBox.getValue()': \t\t" << &movedBox.getValue() << " <-- same" << endl;
  cout << "addr of 'movingBox.getValue()': \t" << &movingBox.getValue() << " <-- differes, moved/copied" << endl;
  cout << endl;

  cout << "rule of zero: avoid writing rule-of-big-fives when not needed,\n"
       << "and try to use the default implementations\n"
       << "when working with member pointers to allocated memory be careful,\n"
       << "since deep copy won't be carried out in all cases" << endl << endl;

  cout << "CAUTION: when deleting an object passed via default operations may lead to double free\n"
    << "(each dtor will call delete), or in other cases to segmentation fault (deleted already\n"
    << "somewhere else, address does not differ)." << endl << endl;

  cout << "READY." << endl;
}
