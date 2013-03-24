// set.cpp
/*
  Verwendet eine Initialisierungsliste
//*/

#include <iostream>
using namespace std;

#include "set.h"
#include "vector.h"

Set::Set()
    :m_data(10)
{
    m_size=0;
};


Set::~Set()
{
};


bool Set::has(const double &toFind)
{
    return find(toFind) != 0;
};


void Set::insert(const double &toInsert)
{
    if(!has(toInsert)){
        m_data.grow(m_size + 1);
        m_data[m_size] = toInsert;
        ++m_size;
    };
};


double Set::*find(const double &toFind)
{
    int found = findIndex(toFind);
    if(found != -1)
        return &m_data[found];
    else
        return 0;
};


void Set::remove(const double &toRemove)
{
    int found = findIndex(toRemove);
    if(found != -1){
        m_data.moveDown(found+1, m_size, found);
        --m_size;
    };
};


int Set::findIndex(const double &toFind)
{
    for(int i=0; i<m_size; ++i)
        if(m_data[i] == toFind)
            return i;

    return -1;
};


