#pragma once

#include "array.h"

class AlgorithmSort
{
public:
    AlgorithmSort(Array &arr);
    void bubbleSort();
    void insertionSort();
    void bogo();

    const std::vector<int> &getCurrentState() const;

    bool isSortingComplete() const;
    void resetSorting();
    void merge();

private:
    Array &array;
    std::vector<int> tempArray;
    size_t i, j;
    int pivotIndex;
    size_t left, middle, right;

    int partition(int low, int high);
};
