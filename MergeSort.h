#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

/** Previously insertion sort was used in CpuSmartStringGuess, but merge sort is faster, so it has replaced insertion sort. This was translated into
C from my own C++ implementation of merge sort found on my github: https://github.com/axiom2018/MergeSort/tree/master/MergeSort */

typedef struct MergeSort * MergeSortPtr;

MergeSortPtr MergeSort_Init();
void MergeSort_Sort(MergeSortPtr msp, int ** ppStringToSort, const int low, const int high);
void MergeSort_Destroy(MergeSortPtr msp);

#endif // MERGESORT_H_INCLUDED
