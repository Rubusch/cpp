// vector.cpp
/*
  Nutzbar machen des operator[] um eine Zuweisung zuzulassen.
//*/

#include <iostream>
using namespace std;
#include <assert.h>

#include "vector.h"

Vector::Vector(int size)
{
    m_size = size;
    m_data = new double[m_size];
};


Vector::Vector(const Vector &derAndereVector)
{
    m_size = derAndereVector.m_size;
    m_data = new double[m_size];
    for(int i=0; i<m_size; ++i)
        m_data[i] = derAndereVector.m_data[i];
};


Vector::~Vector()
{
    delete[] m_data;
};


int Vector::getSize()
{
    return m_size;
};


void Vector::grow(int newSize)
{
    if(newSize > m_size){
        newSize += GROW_SIZE;
        T *newData = new T[newSize];

        for(int i=0; i<m_size; ++i)
            newData[i] = m_data[i];

        delete[] m_data;

        m_size = newSize;
        m_data = newData;
    };
};


void Vector::moveDown(int start, int end, int newStart)
{
    int newSize = (newStart - 0)+(end - start);
    T *newData = new T[newSize];
    
    for(int i=0; i<newStart; ++i)
        newData[i] = m_data[i];
    
    for(int i=0; i<(end-start); ++i)
        newDatax[newStart + i] = m_data[start + i];
    
    delete[] m_data;
    
    m_size = newSize;
    m_data = newData;
};


double& Vector::operator[](int index)
{
    assert(index >= 0);
    assert(index < m_size);
    return m_data[index];
};


/*
  Vector& erlaubt mehrere (geschachtelte) Zuweisungen, wie etwa:
  a = b = 3
//*/
Vector& Vector::operator=(const Vector &derAndereVector)
{
    if(&derAndereVector != this){ 
        delete[] m_data;
        m_size = derAndereVector.m_size;
        m_data = new double[m_size];
        for(int i=0;i<m_size; ++i)
            m_data[i] = derAndereVector.m_data[i];
    };
    return *this;
};
