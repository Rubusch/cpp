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


double& Vector::operator[](int index)
{
    assert(index >= 0);
    assert(index < m_size);
    return m_data[index];
};


int Vector::getSize()
{
    return m_size;
};


void Vector::grow(int newSize)
{
    double *newData = new double[newSize];
    for(int i=0; i<m_size; ++i)
        newData[i] = m_data[i];

    delete [] m_data;

    m_size = newSize;
    m_data = newData;
};
