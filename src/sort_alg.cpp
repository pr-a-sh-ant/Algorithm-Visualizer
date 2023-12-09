#include "sort_alg.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


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

void AlgorithmSort::merge(){

    

    if ( this->currSize <= array.getData().size() - 1) {
        if ( this->left < array.getData().size() - 1 ) {
            int mid = std::min<int>(this->left + this->currSize - 1, array.getData().size() - 1);
            int right = std::min<int>(this->left + 2 * this->currSize - 1, array.getData().size() - 1);


            // Merge the two halves:array.getData()[this->left...mid] and arr[mid+1...right]
            int n1 = mid - this->left + 1;
            int n2 = right - mid;

            std::vector<int> tempArr(n1 + n2);

            int i = this->left;
            int j = mid + 1;
            int k = 0;

            while (i <= mid && j <= right) {
                if (array.getData()[i] <= array.getData()[j]) {
                    tempArr[k++] =array.getData()[i++];
                } else {
                    tempArr[k++] =array.getData()[j++];
                }
            }

            while (i <= mid) {
                tempArr[k++] =array.getData()[i++];
            }

            while (j <= right) {
                tempArr[k++] =array.getData()[j++];
            }

            // Copy merged elements back to the original array
            for (int p = 0; p < k; p++) {
               array.getData()[this->left + p] = tempArr[p];
            }
            this->left += 2 * this->currSize;
        }
            else{

            this->currSize *= 2;
            this->left = 0;
            }
    }
    

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