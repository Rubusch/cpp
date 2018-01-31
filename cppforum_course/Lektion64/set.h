// set.h
/*
//*/

#ifndef SET
#define SET

#include "vector.h"

class Set
{
private:
    Vector<double> m_data;
    int m_size;

public:
    Set();
    ~Set();
};

#endif
