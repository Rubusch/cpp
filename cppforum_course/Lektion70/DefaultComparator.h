// DefaultComparator.h
/*
//*/

#ifndef DEFAULTCOMPARATOR
#define DEFAULTCOMPARATOR

template<class T>
class DefaultComparator
{
public:
    bool lessThan(const T &a, const T &b)
    {
        return a<b;
    };

    bool isEqual(const T &a, const T &b)
    {
        return a==b;
    };
};

#endif


