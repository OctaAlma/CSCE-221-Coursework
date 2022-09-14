#include "SortLib.h"
#include <iostream>

template <typename T>
void concArrays(T arr[], int size, T lArr[], int lSize, T eArr[], int eSize, T gArr[], int gSize){
    int arrIndex = 0;
    for (int i = 0; i < lSize; i++){
        arr[arrIndex] = lArr[i];
        arrIndex++;
    }

    for (int i = 0; i < eSize; i++){
        arr[arrIndex] = eArr[i];
        arrIndex++;
    }

    for (int i = 0; i < gSize; i++){
        arr[arrIndex] = gArr[i];
        arrIndex++;
    }
}

template <typename T>
void SortLib::QuickSort(T arr[], int size){
    if (size == 1){
        return;
    }

    int midpoint = size/2;
    T pivot = arr[midpoint];
    //printArr(arr,size);

    int lSize = 0;
    int gSize = 0;
    int eSize = 0;

    // Get the appropriate sizes for the arrays:
    for (int i = 0; i < size; i++){
        if (arr[i] < pivot){
            lSize++;
        }else if(arr[i] > pivot) {
            gSize++;
        }else{
            eSize++;
        }
    }

    // THERE IS A CHANCE OF A SIZE BEING 0, specially once we get small enough arrays via recursion
    // We should check for that before initializing the arrays
    T* lArr = nullptr;
    int lIndex = 0;
    T* gArr = nullptr;
    int gIndex = 0;
    T* eArr = nullptr;
    int eIndex = 0;

    if (lSize){
        lArr = new T[lSize];
    }
    if (eSize){
        eArr = new T[eSize];
    }
    if (gSize){
        gArr = new T[gSize];
    }

    // Fill up the arrays we made
    for (int i = 0; i < size; i++){
        if (arr[i] < pivot){
            lArr[lIndex] = arr[i];
            lIndex++;
        }else if(arr[i] > pivot) {
            gArr[gIndex] = arr[i];
            gIndex++;
        }else{
            eArr[eIndex] = arr[i];
            eIndex++;
        }
    }

    if (lSize){QuickSort(lArr, lSize);}
    if (gSize){QuickSort(gArr, gSize);}
    // The eArr does not need any sorting
    
    // Now we overwrite the OG array:
    concArrays(arr, size, lArr, lSize, eArr, eSize, gArr, gSize);

    delete [] lArr;
    delete [] eArr;
    delete [] gArr;

    return;
}

template void SortLib::QuickSort(int*, int);