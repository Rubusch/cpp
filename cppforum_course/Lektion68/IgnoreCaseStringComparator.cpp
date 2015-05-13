// IgnoreCaseStringComparator.cpp
/*
  Fuer den "richtigen" Vergleich zweier Strings muessen entweder locales und facets
  verwendet werden oder gleich externe Klassen benutzt werden -> humesikins stricmp.h
//*/

#include "IgnoreCaseStringComparator.h"

string IgnoreCaseStringComparator::toLower(const string &str)
{
    string result = str;
    for(int i=0; i<result.size(); ++i)
        result[i] = tolower(result[i]);
    return result;
};


bool IgnoreCaseStringComparator::lessThan(const string &a, const string &b)
{
    return toLower(a) < toLower(b);
};


bool IgnoreCaseStringComparator::isEqual(const string &a, const string &b)
{
    return toLower(a) == toLower(b);
};

