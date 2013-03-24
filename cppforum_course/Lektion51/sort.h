#ifndef SORT
#define SORT

class Sort
{
private:
    void swap(int *pa, int *pb);

public:
    Sort();
    ~Sort();

    void bubbleSort(int *array, int size);
    void straightSelectionSort(int *array, int size);
    void straightInsertionSort(int *array, int size);
};

#endif
