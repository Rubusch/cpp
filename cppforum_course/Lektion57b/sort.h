#ifndef SORT
#define SORT

class Sort
{
private:
    template<class T>
    void swap(T *pa, T *pb);

public:
    Sort();
    ~Sort();

    template<class T>
    void bubbleSort(T *array, int size);
    void straightSelectionSort(int *array, int size);
    void straightInsertionSort(int *array, int size);
    void shellSort(int *array, int size);
};

#endif
