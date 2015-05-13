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


template<class T>
void Set::swap(T *pa, T *pb)
{
    T tmp=*pa;
    *pa = *pb;
    *pb = tmp;
};


void Set::insert(const double &toInsert)
{
    if(!has(toInsert)){
        m_data.grow(m_size + 1);
        ++m_size;
        m_data[m_size] = toInsert;

        for(int j=(m_size-1); j >= 0; --j){
            if(m_data[j-1] > m_data[j])
                swap(&m_data[j-1], &m_data[j]);
            else
                break;    
        };
    };
};


double* Set::find(const double &toFind)
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


/* try?!
int Set::findIndex(const double &toFind)
{
    int lower = 0;
    for(int i=m_size; i>0; i/=2)
        if(m_data[lower + i] <= toFind)
            lower += i;

    if(m_data[lower] == toFind)
        return lower;

    return -1;
};
//*/


int Set::findIndex(const double &toFind)
{
    int oben = m_size-1, unten = 0, mitte = int(m_size/2);
    do{
        if(m_data[mitte]<=toFind){
            unten = mitte;
            mitte = int(mitte + ((oben - mitte)/2));
        }else{
            oben = mitte - 1;
            mitte = int(mitte - (mitte - unten)/2);
        };
    }while(oben-unten > 1);
    
    if(m_data[oben] == toFind)
        return oben;
    else if(m_data[unten] == toFind)
        return unten;
    else
        return -1;
};

        
