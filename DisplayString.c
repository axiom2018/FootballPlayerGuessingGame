#ifndef DISPLAYSTRING_C_INCLUDED
#define DISPLAYSTRING_C_INCLUDED
#include "DisplayString.h"
#include <stdlib.h> // malloc, free.
#include <stdio.h> // printf.
#include <string.h> // strlen.

struct DisplayString
{
    int m_sizeOfString;
    char m_defaultChar;
    char * m_pStringToDisplay;
    char * m_pRealString;
};

/* We need 2 strings, one to show (the hidden one with underscores) and the "real" one. Ex: If we passed Lionel Messi to this function init. We'll have one allocated string
with the length of "Lionel Messi", replaced with all underscores to display, and the players will input letters to check if they guessed the right one. And we'll have
the "real string" with the real text of "Lionel Messi" so when they do input a character, THIS is the string we can check if it's right or not.

What about spaces in the string?

How to handle spaces? For example, with "Lionel Messi", we know that this string contains 12 characters, but the 7th is a space. We wouldn't want to display that
because that gives the impression that the space is a letter to be guessed.

Solution, go through REAL string in O(n) time, if we detect a space we get the DISPLAY string to replace that index with the default char to just " ". This will require
the display string to be allocated first however. */

DisplayStringPtr DisplayString_Init(const char * pNameOfFootballPlayer)
{
    // Allocate for the size of the structure.
    DisplayStringPtr pPointer = malloc(sizeof * pPointer);

    // Set default char to underscore. This will be the main thing displayed to player and cpu.
    pPointer->m_defaultChar = '_';


    /// HANDLE ALL DISPLAY STRING OPERATIONS BELOW.

    // Get the length of the argument passed in.
    int length = strlen(pNameOfFootballPlayer);

    // Save size of string.
    pPointer->m_sizeOfString = length;

    printf("Allocated string length: %d\n", length);

    // Begin allocation.
    pPointer->m_pStringToDisplay = (char*)malloc(length * sizeof(char));

    // Make sure to add the null terminator at the end or else string operations/functions with this string will fail.
    pPointer->m_pStringToDisplay[length] = '\0';

    // Since the display string will begin with all default characters, loop and insert default characters into it.
    for(int i = 0; i < length; ++i)
    {
        pPointer->m_pStringToDisplay[i] = pPointer->m_defaultChar;
    }

    // Test print.
    printf("DISPLAY String is: %s\n", pPointer->m_pStringToDisplay);

    // Test check the size.
    // printf("Length of DISPLAY string: %d\n", strlen(pPointer->m_pStringToDisplay));

    /// HANDLE ALL DISPLAY STRING OPERATIONS BELOW.





    /// HANDLE ALL "REAL STRING" OPERATIONS BELOW.

    // Begin allocation of "real string".
    pPointer->m_pRealString = (char*)malloc(length * sizeof(char));

    // Add the null terminator at the end so all string functions can correctly operate with it.
    pPointer->m_pRealString[length] = '\0';

    // Test by copying the string in the argument to newly allocated string.
    strcpy(pPointer->m_pRealString, pNameOfFootballPlayer);

    // Begin process of finding spaces in the string.
    for(int i = 0; i < length; ++i)
    {
        if(pPointer->m_pRealString[i] == ' ')
        {
            printf("Found a space at index: %d\n", i + 1);

            // Since we found a space in the real name, update the display string at THIS index with a space instead of an underscore.
            pPointer->m_pStringToDisplay[i] = ' ';
        }
    }

    // Print the REAL string.
    printf("REAL string: %s\n", pPointer->m_pRealString);

    /// HANDLE ALL "REAL STRING" OPERATIONS ABOVE.

    // Wonderful. Display string is now ready.
    printf("FINAL display string view: %s\n\n\n", pPointer->m_pStringToDisplay);

    // Return pointer.
    return pPointer;
}

/* In the constructor, we already give a string and set up the real and display strings to get the game ready. But we need a way to change strings and that's what this
function will do. First, we'll deallocate and delete memory */
void DisplayString_AssignString(DisplayStringPtr displayString, const char * pString)
{
    printf("\n\n\nReassigning strings.\n");

    // Deallocate memory for the display string.
    free(displayString->m_pStringToDisplay);
    displayString->m_pStringToDisplay = NULL;

    // Deallocate memory for the real string.
    free(displayString->m_pRealString);
    displayString->m_pRealString = NULL;

    // Reset the length to 0.
    displayString->m_sizeOfString = 0;


    /// Below, begin allocation and operations for the NEW display string passed in the argument.

    // Get the length of the argument passed in.
    int length = strlen(pString);

    // Save size of string.
    displayString->m_sizeOfString = length;

    printf("[new] Allocated string length: %d\n", length);

    // Begin allocation.
    displayString->m_pStringToDisplay = (char*)malloc(length * sizeof(char));

    // Make sure to add the null terminator at the end or else string operations/functions with this string will fail.
    displayString->m_pStringToDisplay[length] = '\0';

    // Since the display string will begin with all default characters, loop and insert default characters into it.
    for(int i = 0; i < length; ++i)
    {
        displayString->m_pStringToDisplay[i] = displayString->m_defaultChar;
    }

    // Test print.
    printf("[new] DISPLAY String is: %s\n", displayString->m_pStringToDisplay);

    /// Above, begin allocation and operations for the NEW display string passed in the argument.




    /// Below, begin allocation and operations for the NEW real string passed in the argument.

    // Begin allocation of "real string".
    displayString->m_pRealString = (char*)malloc(length * sizeof(char));

    // Add the null terminator at the end so all string functions can correctly operate with it.
    displayString->m_pRealString[length] = '\0';

    // Test by copying the string in the argument to newly allocated string.
    strcpy(displayString->m_pRealString, pString);

    // Begin process of finding spaces in the string.
    for(int i = 0; i < length; ++i)
    {
        if(displayString->m_pRealString[i] == ' ')
        {
            printf("Found a space at index: %d\n", i + 1);

            // Since we found a space in the real name, update the display string at THIS index with a space instead of an underscore.
            displayString->m_pStringToDisplay[i] = ' ';
        }
    }

    // Print the REAL string.
    printf("REAL string: %s\n", displayString->m_pRealString);

    /// HANDLE ALL "REAL STRING" OPERATIONS ABOVE.


    // Wonderful. Display string is now ready.
    printf("FINAL display string view: %s\n\n\n", displayString->m_pStringToDisplay);

    /// Above, begin allocation and operations for the NEW real string passed in the argument.
    printf("\n");
}

void DisplayString_Destroy(DisplayStringPtr displayString)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!displayString)
    {
        return;
    }

    printf("Cleaning display string!\n");
    free(displayString->m_pRealString);
    free(displayString->m_pStringToDisplay);
    free(displayString);
}

#endif // DISPLAYSTRING_C_INCLUDED
