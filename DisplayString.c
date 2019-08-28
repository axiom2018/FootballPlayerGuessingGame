#ifndef DISPLAYSTRING_C_INCLUDED
#define DISPLAYSTRING_C_INCLUDED
#include "DisplayString.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/** Explanation of structure variables:

1) Reasoning of m_sizeOfString:

Properly display the actual string in a for loop.


2) Reasoning for m_defaultChar:

The default character is just an underscore in place of any character any participants guess in the future.


3) Reasoning for m_pStringToDisplay:

This is the string we'll display that has the underscores.


4) Reasoning for m_pRealString:

The REAL string actually has say, "Lionel Messi" in it. The reasoning we have it is because when we want to check to see if a character entered was IN the string the
participant is clearly guessing for, we'd have to have a source of the original.


5) Reasoning for m_totalPointsForWord:

A macro above called s_pointsForChar gives points for each char, a constant amount. So THIS variable is the total points for any string.


6) Reasoning for m_totalCharsToGuessInRound:

If we have the string "Gareth Bale", the total number of characters that needs to be guessed is 10. After all 10 are guessed, the round is over and the turn player
will receive their points as mentioned above.


7) Reasoning for m_currentGuessAttempts:

Save how many guess attempts the turn player has had, if exceeded, end the turn and switch to other participant.


8) Reasoning for m_matchingChar:

When we're looking in the string FOR a matching character we'll then need some sort of indication that we did and we don't have to minus the amount of tries
the participant has left.

*/


// Every string will have these points PER character guessed as a prize. So not all string are worth the same points.
static const int s_pointsForChar = 50;

// Lowercase and uppercase characters are separated on the ascii table by a constant factor of 32, save that constant here.
static const int s_charCase = 32;

// This is the maximum attempts the turn player has at guessing BEFORE we switch to the other participant.
static const int s_attemptsAtGuessing = 3;

// 2 static variables to check for upper case.
static const int s_upperBegin = 65;
static const int s_upperEnd = 90;

// Save the null terminator, it's used in PrepareStrings.
static const char s_nullTerm = '\0';


struct DisplayString
{
    int m_sizeOfString;
    char m_defaultChar;
    char * m_pStringToDisplay;
    char * m_pRealString;
    int m_totalPointsForWord;
    int m_totalCharsToGuessInRound;
    int m_currentGuessAttempts;
    bool m_matchingChar;
};

// Helper function to determine whether character is lower or uppercase.
static bool CaseCheck(const int value)
{
    // 65 - 90 is uppercase.
    if(value >= s_upperBegin && value <= s_upperEnd)
    {
        return true;
    }

    // 97 - 122 is lowercase.
    return false;
}

/** Helper function to help handle string business. Previously, 2 functions did pretty much the exact same thing in chunks of code. This one function reduces that.
Remember, DRY! (D)on't (r)epeat (y)ourself! */
static void PrepareStrings(DisplayStringPtr ds, const char * pString)
{
    // Get the length of the argument passed in.
    int length = strlen(pString);

    // Save size of string.
    ds->m_sizeOfString = length;

    // Begin allocation.
    ds->m_pStringToDisplay = (char*)malloc(length * sizeof(char));

    // Make sure to add the null terminator at the end or else string operations/functions with this string will fail.
    ds->m_pStringToDisplay[length] = s_nullTerm;

    // Since the display string will begin with all default characters, loop and insert default characters into it.
    for(int i = 0; i < length; ++i)
    {
        ds->m_pStringToDisplay[i] = ds->m_defaultChar;
    }

    // Begin allocation of "real string".
    ds->m_pRealString = (char*)malloc(length * sizeof(char));

    // Add the null terminator at the end so all string functions can correctly operate with it.
    ds->m_pRealString[length] = s_nullTerm;

    // Test by copying the string in the argument to newly allocated string.
    strcpy(ds->m_pRealString, pString);

    // Begin process of finding spaces in the string.
    for(int i = 0; i < length; ++i)
    {
        if(ds->m_pRealString[i] == ' ')
        {
            // Since we found a space in the real name, update the display string at THIS index with a space instead of an underscore.
            ds->m_pStringToDisplay[i] = ' ';
        }

        else
        {
            // Calculate how much points each word is worth by the predefined macro.
            ds->m_totalPointsForWord = ds->m_totalPointsForWord + s_pointsForChar;

            // Get the total amount of characters we need to guess this round in order to make sure we know how to win.
            ds->m_totalCharsToGuessInRound += 1;
        }
    }
}

/** Say we have the letter 'a' as input. And we have the string Cristiano Ronaldo. We have to change OUR 'a' to the opposite size which is 'A' and begin checking
the "R" on Ronaldo. Lets say we still have 'a' but we have a string like "Aaron" instead. We check "A" first but our character 'a' won't match up. So the overall
goal or strategy should basically be to switch our own character we received (in this example it's 'a') and change it back and forth from lower to uppercase to check
every character in the footballer name string. */
DisplayStringPtr DS_Init(const char * pNameOfFootballPlayer)
{
    // Allocate for the size of the structure.
    DisplayStringPtr pPointer = malloc(sizeof * pPointer);

    // Set default char to underscore. This will be the main thing displayed to player and cpu.
    pPointer->m_defaultChar = '_';

    // Set the total points for the word.
    pPointer->m_totalPointsForWord = 0;

    // Set the total chars to guess to 0.
    pPointer->m_totalCharsToGuessInRound = 0;

    // Set current guess attempts.
    pPointer->m_currentGuessAttempts = s_attemptsAtGuessing;

    // Set matching char to false, no characters have been checked yet.
    pPointer->m_matchingChar = false;

    // Ready all strings.
    PrepareStrings(pPointer, pNameOfFootballPlayer);

    // Return pointer.
    return pPointer;
}

/** In the constructor, we already give a string and set up the real and display strings to get the game ready. But we need a way to change strings and that's what this
function will do. First, we'll deallocate and delete memory */
void DS_AssignString(DisplayStringPtr ds, const char * pString)
{
    // Deallocate memory for the display string.
    free(ds->m_pStringToDisplay);
    ds->m_pStringToDisplay = NULL;

    // Deallocate memory for the real string.
    free(ds->m_pRealString);
    ds->m_pRealString = NULL;

    // Reset the length to 0.
    ds->m_sizeOfString = 0;

    // Ready all strings.
    PrepareStrings(ds, pString);

    printf("\n");
}

// Get the string to give it to the CPU so it's string guessing algorithm can be properly set up.
char * DS_GetString(DisplayStringPtr ds)
{
    return ds->m_pRealString;
}

void DS_ShowHiddenString(DisplayStringPtr ds)
{
    printf("\n--------------------Guess the footballer!--------------------\n\n\n");

    for(int i = 0; i < ds->m_sizeOfString; ++i)
    {
        printf("%c", ds->m_pStringToDisplay[i]);
    }

    printf("\n\n\n");
}

/**  This function will take in either a lowercase or uppercase character, then go ahead and check the string for that character in both lower and uppercase.
So we'll need to check if the character is in the string in a fancy unorthodox way. */
int DS_CheckStringForMatchingChar(DisplayStringPtr ds, const char input)
{
    // This integer will help us easily determine if our char matches a char in the string regardless of lower or uppercase.
    int value = 0;

    // First, is the character we received lower or uppercase.
    if(CaseCheck(input))
    {
        // printf("This character is uppercase!\n");
        value = s_charCase;
    }

    else
    {
        // printf("This character is lowercase!\n");
        value = -s_charCase;
    }

    // Loop over the real string, IF we do find a matching value (Say the string is "Didier Drogba" and the char is 'd' then update display string at THOSE indexes with the char.
    for(int i = 0; i < ds->m_sizeOfString; ++i)
    {
        // We have the regular character to check.
        if(ds->m_pRealString[i] == input)
        {
            ds->m_pStringToDisplay[i] = input;

            // Set the matching character to true, it helps indicate to this function to return true, we found the character a participant gave us.
            ds->m_matchingChar = true;

            // Decrement the total characters to be guessed.
            ds->m_totalCharsToGuessInRound -= 1;
        }

        // We have the opposite here thanks to value, opposite of a is A, and opposite of G is g, etc.
        else if(ds->m_pRealString[i] == (char)(input + value))
        {
            ds->m_pStringToDisplay[i] = (char)(input + value);

            // Set the matching character to true, it helps indicate to this function to return true, we found the character a participant gave us.
            ds->m_matchingChar = true;

            // Decrement the total characters to be guessed.
            ds->m_totalCharsToGuessInRound -= 1;
        }
    }

    // If the boolean is true, great we found a matching character! Set it to false and return true!
    if(ds->m_matchingChar)
    {
        ds->m_matchingChar = false;
        return true;
    }

    // We didn't find a matching character if we reached this line of code, return false.
    return false;
}

// If this value is 0, aka, if we got all the guesses, the participant receives the full points for that word.
int DS_GuessCompleted(DisplayStringPtr ds)
{
    if(ds->m_totalCharsToGuessInRound <= 0)
    {
        return true;
    }

    printf("Still have %d characters to guess!\n", ds->m_totalCharsToGuessInRound);

    return false;
}

// Return the points when it's time to assign it to a participant.
int DS_GetPoints(DisplayStringPtr ds)
{
    return ds->m_totalPointsForWord;
}

void DS_DisplayTriesLeft(DisplayStringPtr ds)
{
    printf("Attempts remaining: %d\n", ds->m_currentGuessAttempts);
}

int DS_CanParticipantContinue(DisplayStringPtr ds)
{
    // If return false, participant may not continue their turn, they have no more remaining chances.
    if(ds->m_currentGuessAttempts <= 0)
    {
        return false;
    }

    return true;
}

void DS_DecrementTriesLeft(DisplayStringPtr ds)
{
    ds->m_currentGuessAttempts -= 1;
}

// Make SURE that no char is entered twice in the same round!
int DS_CharAlreadyEntered(DisplayStringPtr ds, const char input)
{
    // This integer will help us easily determine if our char matches a char in the string regardless of lower or uppercase.
    int value = 0;

    // Variable to hold number of times we saw this input.
    int numOfTimesSeen = 0;

    // First, is the character we received lower or uppercase.
    if(CaseCheck(input))
    {
        value = s_charCase;
    }

    else
    {
        value = -s_charCase;
    }

    // Loop over the string and check if the character might have already been found in lower or uppercase.
    for(int i = 0; i < ds->m_sizeOfString; ++i)
    {
        if(ds->m_pStringToDisplay[i] == input)
        {
            ++numOfTimesSeen;
        }

        else if(ds->m_pStringToDisplay[i] == (char)(input + value))
        {
            ++numOfTimesSeen;
        }
    }

    // If var is greater 0, we've seen it already.
    if(numOfTimesSeen > 0)
    {
        printf("Character %c has already been entered! Enter again please!", input);
        return true;
    }

    return false;
}

void DS_DisplayPointsForName(DisplayStringPtr ds)
{
    printf("*** The current name is worth: %d points. ***\n\n\n", ds->m_totalPointsForWord);
}

void DS_Reset(DisplayStringPtr ds)
{
    // Set size of string to 0.
    ds->m_sizeOfString = 0;

    // Clear memory of both real and display strings.
    free(ds->m_pStringToDisplay);
    ds->m_pStringToDisplay = NULL;

    free(ds->m_pRealString);
    ds->m_pRealString = NULL;

    // Reset the total points for the word.
    ds->m_totalPointsForWord = 0;

    // Reset the total chars to guess to 0.
    ds->m_totalCharsToGuessInRound = 0;

    // Reset current guess attempts.
    ds->m_currentGuessAttempts = s_attemptsAtGuessing;
}

void DS_Destroy(DisplayStringPtr ds)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!ds)
    {
        return;
    }

    // Free all pointers and set to NULL.
    free(ds->m_pRealString);
    ds->m_pRealString = NULL;
    free(ds->m_pStringToDisplay);
    ds->m_pStringToDisplay = NULL;
    free(ds);
    ds = NULL;
}

#endif // DISPLAYSTRING_C_INCLUDED
