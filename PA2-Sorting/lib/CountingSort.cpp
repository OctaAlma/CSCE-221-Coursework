#include "SortLib.h"
#include <iostream>

template <typename T>
void SortLib::CountingSort(T arr[], int size){
    // find the max and the min:
    T max = arr[0];
    T min = arr[0];

    for (int i = 0; i < size; i++){
        if (arr[i] > max){
            max = arr[i];
        }
        if (arr[i] < min){
            min = arr[i];
        }
    }
    int range = max - min + 1;

    // Make a list with the obtained range
    //  - count[0]       = #ofMin
    //  ...
    //  - count[range-1] = #ofMax
    int* count = new int[range];
    for (int i = 0; i < range; i++){
        count[i] = 0;
    }

    // Iterate through the list and count the values:
    for (int i = 0; i < size; i++){
        count[arr[i]-min]++;
    }

    // Populate the list in order using the counter list:
    int arrIndex = 0;
    for (int j = 0; j < range; j++){
        for (int c = 0; c < count[j]; c++){
            arr[arrIndex] = min+j;
            arrIndex++; 
        }
    }

    delete [] count;
}

template void SortLib::CountingSort(int*, int);