// IgnoreCaseStringComparator.h
/*
//*/

#ifndef COMPARATOR
#define COMPARATOR

#include <iostream>
#include <string>
using namespace std;

class IgnoreCaseStringComparator
{
private:
    string toLower(const string &str);

public:
    bool lessThan(const string &a, const string &b);
    bool isEqual(const string &a, const string &b);
};

#endif
