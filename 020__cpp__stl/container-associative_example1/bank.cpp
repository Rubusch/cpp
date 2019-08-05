// bank.cpp
/*
  demonstrates set and multiset modifying

  +-----------------+----------------+------------------+
  |                 | one occurance  | more occurances  |
  |                 |                |                  |
  +-----------------++================+=================+
  | only keys       || set            | multiset        |
  +-----------------++----------------+-----------------+
  | keys and values || map            | multimap        |
  +-----------------++----------------+-----------------+

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <set>


class Account
{
private:
  const int number_;
  double balance_;

public:
  Account(int number, double balance = 0.0) : number_(number), balance_(balance){}

  int getNumber() const { return number_; }
  double getBalance() const { return balance_; }
  void deposit( double money){ balance_ += money; }
};


/*
  functor
//*/
class CompareAccounts
  : public std::binary_function< Account, Account, bool>
{
public:
  bool operator()(const Account& account_x, const Account& account_y) const
  {
    return account_x.getNumber() < account_y.getNumber();
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Account accounts[] = { Account(10, 1.11), Account(20, 2.22), Account(30, 3.33) };
  cout << endl;

  cout << "init set\n";
  set< Account, CompareAccounts > account_set(accounts, accounts + 3);
  cout << endl;

  cout << "init set iterator\n";
  set< Account, CompareAccounts >::iterator iter = account_set.find(Account(20));
  cout << endl;

  cout << "call function of set element\n";
  if( iter != account_set.end()){
    (const_cast< Account& >(*iter)).deposit(100.00);
    cout << "Balance: " << iter->getBalance();
  }
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
