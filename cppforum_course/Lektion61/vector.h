// vector.h
/*
  Vector Klasse mit Copy-Constructor
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
    Vector(const Vector &derAndereVector);
    ~Vector();

    double &operator[](int index);
    int getSize();
    void grow(int newSize);
};

#endif
