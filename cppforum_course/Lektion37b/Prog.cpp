// Prog.cpp
/*
  Funktion die drei Werte sortiert. Dabei wird call-by-referenze II eingesetzt,
  d.h. es werden Referenzen als Parameter uebergeben.
//*/

#include <iostream>
using namespace std;

void sort(int *pa, int *pb, int *pc);
void swap(int *pa, int *pb);


int main()
{
    int a=3;
    int b=5;
    int c=2;
    sort(&a,&b,&c);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    
    return 0;
};


void swap(int *pa, int *pb)
{
    int tmp=*pa;
    *pa=*pb;
    *pb=tmp;
};


void sort(int *pa, int *pb, int *pc)
{
    if(*pa>*pb)
        swap(pa,pb);

    if(*pb>*pc){
        swap(pb,pc);
        if(*pa>*pb)
            swap(pa,pb);
    };
};


    
    
