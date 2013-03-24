// vector.h
/*
//*/

#ifndef VECTOR
#define VECTOR

class Vector
{
private:
    double *m_data;
    int m_size;
    
public:
    Vector(int size);
    ~Vector();

    double &operator[](int index);
    int getSize();
    void grow(int newSize);
};

#endif
