#pragma once

#include "array.h"

class AlgorithmSort
{
public:
    AlgorithmSort(Array &arr);
    void bubbleSort();
    void insertionSort();
    void mergeSort();
    void quickSort();

    const std::vector<int> &getCurrentState() const;

    bool isSortingComplete() const;
    void resetSorting();

private:
    Array &array;
    std::vector<int> tempArray;
    size_t i, j;
    int pivotIndex;

    void merge(size_t left, size_t middle, size_t right);
    void mergeSortRecursive(size_t left, size_t right);
    void quickSortRecursive(int low, int high);
    int partition(int low, int high);
};
