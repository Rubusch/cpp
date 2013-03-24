// SortedArray.h
/*
  Default Template Argument.
  Wichtig: nie '>>' schreiben, wenn zwei '>' gemeint sind!
//*/

#ifndef SORTEDARRAY
#define SORTEDARRAY

#include <iostream>
#include <string>
using namespace std;
#include <assert.h>

#include "DefaultComparator.h"
#include "vector.h"

template< class T, class C=DefaultComparator<T> >
class SortedArray
{
private:
    C m_comp;
    Vector<T> m_data;
    int m_size;


    void swap(T *pa, T *pb)
    {
        T tmp=*pa;
        *pa = *pb;
        *pb = tmp;
    };

    
public:
    SortedArray()
        :m_data(10)
    {
        m_size=0;
    };


    ~SortedArray()
    {};


    bool has(const T &toFind)
    {
        return find(toFind) != 0;
    };


    void insert(const T &toInsert)
    {
        if(!has(toInsert)){
            m_data.grow(m_size + 1);
            ++m_size;
            m_data[m_size-1] = toInsert;

            if(m_size > 1){  
                for(int j=(m_size-1); j > 0; --j){
                    if(m_comp.lessThan(m_data[j], m_data[j-1]))
                        swap(&m_data[j-1], &m_data[j]);
                    else
                        break;    
                };
            };
        };
    };


    T* find(const T &toFind)
    {
        int found = findIndex(toFind);
        if(found != -1)
            return &m_data[found];
        else
            return 0;
    };


    void remove(const T &toRemove)
    {
        int found = findIndex(toRemove);
        if(found != -1){
            m_data.moveDown(found+1, m_size, found);
            --m_size;
        };
    };


    int findIndex(const T &toFind)
    {
        int lower = 0;
        for(int i=m_size-1; (i>0)&&(lower + i < m_size); i/=2)
            if( m_comp.lessThan(m_data[lower + i], toFind) 
                || m_comp.isEqual(m_data[lower + i], toFind) )
                lower += i;

        if(m_comp.isEqual(m_data[lower], toFind))
            return lower;
        
        return -1;
    };


    int getSize()
    {
        return m_size;
    };


    const T &operator[](int index)
    {
        assert(index < m_size);
        return m_data[index];
    };        
};

#endif
