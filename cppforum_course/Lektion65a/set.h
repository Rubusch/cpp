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

    bool has(const double &toFind);

public:
    Set();
    ~Set();

    double *find(const double &toFind);
    void insert(const double &toInsert);
    void remove(const double &toRemove);
    int findIndex(const double &toFind);
};

#endif
