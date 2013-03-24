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
    static const int GROW_SIZE = 10;

public:
    Vector(int size);
    Vector(const Vector &derAndereVector);
    ~Vector();

    int getSize();
    void grow(int newSize);
    void moveDown(int start, int end, int newStart);

    double &operator[](int index);
    Vector &operator=(const Vector &derAndereVector);
};

#endif
