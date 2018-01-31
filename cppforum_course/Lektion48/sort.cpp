// sort.cpp
/*
//*/
#include "swap.h"
#include "sort.h"

void sort(int *px, int *py)
{
    if(*px > *py)
        swap(px, py);
};


void sort(int *pa, int *pb, int *pc)
{
    // die kleinste Zahl nach vorn (pa) ziehen
    sort(pa, pb);
    sort(pa, pc);

    // die zweitkleinste Zahl nach vorn (pb) ziehen
    sort(pb, pc);

    // fertig
};
