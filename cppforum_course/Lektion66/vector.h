// vector.h
/*
  Vector Klasse mit Copy-Constructor
//*/

#ifndef VECTOR
#define VECTOR

#include <iostream>
using namespace std;

#include <assert.h>

template<class T>
class Vector
{
private:
    T *m_data;
    int m_size;
    static const int GROW_SIZE = 10;

public:

    Vector(int size)
    {
        m_size = size;
        m_data = new double[m_size];
    };


    Vector(const Vector &derAndereVector)
    {
        m_size = derAndereVector.m_size;
        m_data = new double[m_size];
        for(int i=0; i<m_size; ++i)
            m_data[i] = derAndereVector.m_data[i];
    };


    ~Vector()
    {
        delete[] m_data;
    };


    int getSize()
    {
        return m_size;
    };


    void grow(int newSize)
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


    void moveDown(int start, int end, int newStart)
    {
        int newSize = (newStart - 0)+(end - start);
        T *newData = new T[newSize];

        for(int i=0; i<newStart; ++i)
            newData[i] = m_data[i];

        for(int i=0; i<(end-start); ++i)
            newData[newStart + i] = m_data[start + i];

        delete[] m_data;

        m_size = newSize;
        m_data = newData;
    };


    double& operator[](int index)
    {
        assert(index >= 0);
        assert(index < m_size);
        return m_data[index];
    };


    Vector& operator=(const Vector &derAndereVector)
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
};

#endif
