#include "SortLib.h"
#include <iostream>

template <typename T>
void SortLib::SelectionSort(T arr[], int size){
    T currMin;
    T temp;
    int minIndex;

    for (int i = 0; i < size; i++){
        currMin = arr[i];
        minIndex = i;
        for (int j = i+1; j < size; j++){
            if (currMin > arr[j]){
                currMin = arr[j];
                minIndex = j;
            }
        }

        temp = arr[i];
        arr[i] = currMin;
        arr[minIndex] = temp;
    }
}

template void SortLib::SelectionSort(int*, int);