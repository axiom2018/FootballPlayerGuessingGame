#ifndef VOWELMANAGER_C_INCLUDED
#define VOWELMANAGER_C_INCLUDED
#include "VowelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

// Definitions needed for static variables.
#define VOWELS_ROWS 2
#define VOWELS_COLUMNS 5

/** All static values.

1) Reasoning for s_lastPosition:

Used in VowelBinarySearch function, when we force the cpu to go for vowels and it originally picks some random characters like "z", we know searching
for vowels with a character like "z", we'll fail, BUT, we save the last position or last index of the search and switch it to the vowel. Pretty interesting
way to go about it.

2) Reasoning for s_vowelArraySize:

We only have room for a, e, i, o, and u, all the main vowels.


3) Reasoning for s_vowels:

The 2d array we'll use to keep track of vowels and whether they've been used or not.

*/
static int s_lastPosition = -1;
static const int s_vowelArraySize = 5;
static int s_vowels[VOWELS_ROWS][VOWELS_COLUMNS];

// Structure to save the string we're currently operating on in CpuSmartStringGuess and the size of it.
struct VowelManager
{
    int ** m_ppSavedStringToSort;
    int m_stringSize;
};

// Initialization function.
VowelManagerPtr VowelManager_Init(const int strSize, int ** ppStringToSort)
{
    // Allocate memory for the structure.
    VowelManagerPtr pVMP = malloc(sizeof * pVMP);

    // Check if null.
    if(!pVMP)
    {
        printf("VowelManager null!\n");
        return NULL;
    }

    else
    {
        // Set the size of the string.
        pVMP->m_stringSize = strSize;

        // Save the double pointer.
        pVMP->m_ppSavedStringToSort = ppStringToSort;

        /** We need to use this 2d array for checking vowels. It makes it very simple to check whether a vowel has already been used or not, and if so, get another one.
        We initialize the first row like this because the characters integers aren't in a linear fashion. */
        s_vowels[0][0] = 'a';
        s_vowels[0][1] = 'e';
        s_vowels[0][2] = 'i';
        s_vowels[0][3] = 'o';
        s_vowels[0][4] = 'u';

        /** Now this step takes care of getting the "active" states ready in the other row. They're basically booleans, 1's and 0's. If there is a 1, we already used this
        particular vowel this time around. If it's 0, we did not use it. */
        for(int i = 0; i < VOWELS_COLUMNS; ++i)
        {
            s_vowels[1][i] = 0;
        }
    }

    // Return the player.
    return pVMP;
}

// O(n log n). This binary search is to help determine if vowels are still available in the stringToSort. If so, we can make accurate guesses, if not, we'll have to adjust.
int StringBinarySearch(VowelManagerPtr pVMP)
{
    // Start off by looping over the s_vowels array.
    for(int i = 0; i < VOWELS_COLUMNS; ++i)
    {
        // Get the value of the vowel in the array.
        int value = s_vowels[0][i];

        // Set low.
        int low = 0;

        // Set high.
        int high = pVMP->m_stringSize - 1;

        // While low is less than high because otherwise we've ran out of space to search.
        while(low <= high)
        {
            // Calculate the midpoint the same way we'd do in say, merge sort.
            int midpoint = (low + high) / 2;

            // printf("Value: %d. Low: %d. High: %d. Midpoint: %d.\n", value, low, high, midpoint);

            // If search value is at this midpoint, that's one half, then check this vowel still has a false value. Indicating we have not used it yet.
            if(value == pVMP->m_ppSavedStringToSort[0][midpoint] && pVMP->m_ppSavedStringToSort[1][midpoint] == 0)
            {
                // If we found one and haven't used it yet, great! We can return true because we still have vowels available.
                return true;
            }

            else if(value < pVMP->m_ppSavedStringToSort[0][midpoint])
            {
                high = midpoint - 1;
                continue;
            }

            else if(value > pVMP->m_ppSavedStringToSort[0][midpoint])
            {
                low = midpoint + 1;
                continue;
            }

            break;
        }
    }

    return false;
}

int VowelBinarySearch(VowelManagerPtr pVMP, const int searchValue)
{
    // Set low.
    int low = 0;

    // Set high.
    int high = s_vowelArraySize - 1;

    int index = -1;

    // While low is less than high because otherwise we've ran out of space to search.
    while(low <= high)
    {
        // Calculate the midpoint the same way we'd do in say, merge sort.
        int midpoint = (low + high) / 2;

        // If search value is at this midpoint, we found it!
        if(searchValue == s_vowels[0][midpoint])
        {
            index = midpoint;
            return index;
        }

        // If search value is lesser, alter high and save the last position.
        else if(searchValue < s_vowels[0][midpoint])
        {
            high = midpoint - 1;
            s_lastPosition = high;
        }

        // If search value is greater, alter low and save the last position.
        else if(searchValue > s_vowels[0][midpoint])
        {
            low = midpoint + 1;
            s_lastPosition = low;
        }
    }

    // Return false if index of character is not found. This is due to bad input from argument.
    return -1;
}

void UpdateCharacterUse(VowelManagerPtr pVMP, char * pLetter)
{
    // Run a loop, there's a certain condition we need to meet to break it.
    while(true)
    {
        // The last position held the last place from the vowels search, save that letter here.
        *pLetter = (char)s_vowels[0][s_lastPosition];

        // IF that letter was already used, we'll have to find another one.
        if(s_vowels[1][s_lastPosition] == 1)
        {
            // Get random in the array.
            s_lastPosition = (rand() % VOWELS_COLUMNS) + 0;

            // If it is in fact 1, continue, but with new last position spot.
            continue;
        }

        else
        {
            // Set the entry to true!
            s_vowels[1][s_lastPosition] = true;

            break;
        }
    }
}

void LastPositionOutOfBounds(VowelManagerPtr pVMP)
{
    if(s_lastPosition >= VOWELS_COLUMNS)
    {
        s_lastPosition = 4;
    }
}

void FullReset(VowelManagerPtr pVMP)
{
    // Reset the active states in the vowel arrays.
    for(int i = 0; i < VOWELS_COLUMNS; ++i)
    {
        s_vowels[1][i] = 0;
    }

    if(s_lastPosition != -1)
    {
        s_lastPosition = -1;
    }
}

void UpdateSizeAndString(VowelManagerPtr pVMP, const int strSize, int ** ppStringToSort)
{
    // Set the size of the string.
    pVMP->m_stringSize = strSize;

    // Save the double pointer.
    pVMP->m_ppSavedStringToSort = ppStringToSort;
}

// Delete memory.
void VowelManager_Destroy(VowelManagerPtr pVMP)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!pVMP)
    {
        return;
    }

    // Free all pointers and set to NULL.
    free(pVMP);
    pVMP = NULL;
}

#endif // VOWELMANAGER_C_INCLUDED
