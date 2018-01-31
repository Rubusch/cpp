// rational.h
/*
//*/
#ifndef RATIONAL
#define RATIONAL

class Rational
{
private:
    int m_zaehler;
    int m_nenner;
    void kuerzen();
    int ggt(int a, int b);
    int kgv(int a, int b);
    void swap(int *a, int *b);

public:
    Rational(int zaehler, int nenner);
    void print();
    Rational operator*(Rational rhs);
    Rational operator+(Rational rhs);
    Rational operator-(Rational rhs);
    Rational operator/(Rational rhs);
};

#endif
