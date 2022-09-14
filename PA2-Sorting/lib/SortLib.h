#pragma once

/*
(S) Simple sorts: Bubble, Insertion, Selection, Exchange
(N) Non-comparative sorts: Radix, Counting, Bucket
(D) Divide-and-conquer sorts: Merge, Quick

For group size = 1, you must implement 3 algorithms in total, consisting of 1 of your choosing from each
of the categories S, N, and D

 - Selection Sort
 - Counting Sort
 - Quicksort
*/

namespace SortLib {
	template <typename T>
	void BubbleSort(T arr[], int size);

	template <typename T>
	void InsertionSort(T arr[], int size);

	template <typename T>
	void SelectionSort(T arr[], int size);

	template <typename T>
	void ExchangeSort(T arr[], int size);

	template <typename T>
	void RadixSort(T arr[], int size);

	template <typename T>
	void BucketSort(T arr[], int size);

	template <typename T>
	void CountingSort(T arr[], int size);

	template <typename T>
	void MergeSort(T arr[], int size);

	template <typename T>
	void QuickSort(T arr[], int size);

}
