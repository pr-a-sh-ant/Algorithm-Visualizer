#include "sort_alg.h"

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

            else{
                this->i++;
                
                this->j = this->i;
            }
        }
        
    
}

void AlgorithmSort::mergeSort()
{
    if (i < array.getData().size() - 1)
    {
        mergeSortRecursive(0, array.getData().size() - 1);
        i = array.getData().size() - 1;
    }
}

void AlgorithmSort::quickSort()
{
    if (i == 0 && j == 0)
    {
        quickSortRecursive(0, array.getData().size() - 1);
    }
    else
    {
        i = 0;
        j = 0;
        pivotIndex = -1;
    }
}


void AlgorithmSort::merge(size_t left, size_t middle, size_t right)
{
    size_t n1 = middle - left + 1;
    size_t n2 = right - middle;

    for (size_t i = 0; i < n1; i++)
    {
        tempArray[i] = array.getData()[left + i];
    }
    for (size_t j = 0; j < n2; j++)
    {
        tempArray[n1 + j] = array.getData()[middle + 1 + j];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < n1 && j < n2)
    {
        if (tempArray[i] <= tempArray[j])
        {
            array.swap(k, left + i);
            i++;
        }
        else
        {
            array.swap(k, middle + 1 + j);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array.swap(k, left + i);
        i++;
        k++;
    }

    while (j < n2)
    {
        array.swap(k, middle + 1 + j);
        j++;
        k++;
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

const std::vector<int> &AlgorithmSort::getCurrentState() const
{
    return array.getData();
}

// Implementation of added functions
bool AlgorithmSort::isSortingComplete() const
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