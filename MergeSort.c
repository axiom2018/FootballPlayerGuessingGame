#ifndef MERGESORT_C_INCLUDED
#define MERGESORT_C_INCLUDED
#include "MergeSort.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Structure for the merge sort algorithm.
struct MergeSort
{
    bool m_initialized;
};

/** Below are "private" merge sort functions. */

// Bring two pieces of the array together.
static void Merge(int ** ppStringToSort, const int low, const int high, const int mid)
{
    // Set up needed variables to get this done.
    int k = low;
	int i = low;
	int j = mid + 1;
	int temp[50];

    while (i <= mid && j <= high)
	{
		// Check if the left array entry is less than the right array entry.
		if (ppStringToSort[0][i] < ppStringToSort[0][j])
		{
			// We will save this entry to the main array.
			temp[k] = ppStringToSort[0][i];

			// Must increment i because the current i value in left array has been selected already.
			++i;
		}

		else if (ppStringToSort[0][i] > ppStringToSort[0][j])
		{
			// We will save this entry to the main array.
			temp[k] = ppStringToSort[0][j];

			// Must increment j because the current j value in left array has been selected already.
			++j;
		}

		// Special case to check for duplicate values.
		else if (ppStringToSort[0][i] == ppStringToSort[0][j])
		{
			// Doesn't really matter exactly which one we save since they're the same.
			temp[k] = ppStringToSort[0][i];

			// Increment integer.
			++i;
		}

		// Always increment k because no matter what, we will find a value to insert into main array and we'll need to forward the current position.
		++k;
	}

    while (i <= mid)
	{
		// We will save this entry to the main array.
		temp[k] = ppStringToSort[0][i];

		// Always increment k because no matter what, we will find a value to insert into main array and we'll need to forward the current position.
		++k;

		// Must increment i because the current i value in left array has been selected already.
		++i;
	}

	while (j <= high)
	{
		// We will save this entry to the main array.
		temp[k] = ppStringToSort[0][j];

		// Always increment k because no matter what, we will find a value to insert into main array and we'll need to forward the current position.
		++k;

		// Must increment j because the current j value in left array has been selected already.
		++j;
	}

	// Finally we'll have to insert the temporary values into the main array using k because it's definitely an indicator of how many values we have in the temp array.
	for (i = low; i < k; i++)
	{
		ppStringToSort[0][i] = temp[i];
	}
}

// Begin the algorithm that will use recursive calls to solve the sorting issue at hand.
static void UseMergeSort(int ** ppStringToSort, const int low, const int high)
{
    if(low < high)
    {
        int midpoint = (low + high) / 2;

        UseMergeSort(ppStringToSort, low, midpoint);
        UseMergeSort(ppStringToSort, midpoint + 1, high);

        Merge(ppStringToSort, low, high, midpoint);
    }
}

/** Above are "private" merge sort functions. */


MergeSortPtr MergeSort_Init()
{
    // Allocate memory for the structure.
    MergeSortPtr pMSP = malloc(sizeof * pMSP);

    // Check if null.
    if(!pMSP)
    {
        printf("MergeSort Pointer null!\n");
        return NULL;
    }

    else
    {
        pMSP->m_initialized = true;
    }

    // Return the player.
    return pMSP;
}

// Begin the merge sort algorithm.
void MergeSort_Sort(MergeSortPtr msp, int ** ppStringToSort, const int low, const int high)
{
    // check if initialized.
    if(msp->m_initialized != true)
    {
        // If not, return.
        printf("Not initialized!\n");
        return;
    }

    // If initialized, continue to sorting.
    UseMergeSort(ppStringToSort, low, high);
}

void MergeSort_Destroy(MergeSortPtr msp)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!msp)
    {
        return;
    }

    // Free all pointers and set to NULL.
    free(msp);
    msp = NULL;
}


#endif // MERGESORT_C_INCLUDED
