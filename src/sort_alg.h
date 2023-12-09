#pragma once

#include "array.h"

class AlgorithmSort
{
public:
    AlgorithmSort(Array &arr);
    void bubbleSort();
    void insertionSort();
    void bogo();

    std::vector<int> &getCurrentState();

    bool isSortingComplete();
    void resetSorting();
    void merge();

private:
    Array &array;
    std::vector<int> tempArray;
    size_t i, j;
    int pivotIndex;
    size_t left=0, middle, right;
    size_t currSize=0;

    int partition(int low, int high);
};
