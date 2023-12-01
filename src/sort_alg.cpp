#include "sort_alg.h"
#include <iostream>

AlgorithmSort::AlgorithmSort(Array &arr) : array(arr), i(0), j(0), pivotIndex(-1), tempArray(arr.getData().size()) {}

void AlgorithmSort::bubbleSort()
{
    if (i < array.getData().size() - 1)
    {
        if (j < array.getData().size() - i - 1)
        {
            if (array.getData()[j] > array.getData()[j + 1])
            {
                array.swap(j, j + 1);
            }
            j++;
        }
        else
        {
            j = 0;
            i++;
        }
    }
}

void AlgorithmSort::insertionSort()
{
    if (this->i < array.getData().size())
    {
        int key = array.getData()[this->j];

        if (this->j > 0 && array.getData()[this->j - 1] > key)
        {
            array.swap(this->j, this->j - 1);
            this->j--;
        }

        else
        {
            this->i++;

            this->j = this->i;
        }
    }
}

void AlgorithmSort::bogo()
{

    if (!isSortingComplete())
    {
        array.shuffle();
    }
}

int AlgorithmSort::partition(int low, int high)
{
    int pivot = array.getData()[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (array.getData()[j] < pivot)
        {
            array.swap(i + 1, j);
            i++;
        }
    }

    array.swap(i + 1, high);
    return (i + 1);
}

std::vector<int> &AlgorithmSort::getCurrentState()
{
    return array.getData();
}

// Implementation of added functions
bool AlgorithmSort::isSortingComplete()
{

    return i >= array.getData().size() - 1;
}

void AlgorithmSort::resetSorting()
{
    this->array.shuffle();
    i = 0;
    j = 0;
    pivotIndex = -1;
}