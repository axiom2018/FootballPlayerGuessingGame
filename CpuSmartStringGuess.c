#ifndef CPUSMARTSTRINGGUESS_C_INCLUDED
#define CPUSMARTSTRINGGUESS_C_INCLUDED
#include "CpuSmartStringGuess.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// All definitions needed for static variables.
#define VOWELS_ROWS 2
#define VOWELS_COLUMNS 5
#define TIMER_DEFAULT 90000000

/**

                                                            Explanation of structure variables:

1) Reasoning for m_minimumGuesses:

We want the cpu to think like a person as best as we can. To do this, we have to come to an understanding of how people think. Now if you're a fellow software
engineer that isn't a football fan, guesses the strings is going to be hard for you. But someone familiar with the sport will most likely get some guesses.
Now let's consider the string "_____ __ ___". What would you think this string is? Of course you'd have no idea. So you just randomly guess the letter "a"
And now it's "_a___ __ __a". Any new guesses for what it is? PROBABLY not. Now let's say if a football fan pressed the "d" keyword. Now the string is
"Da__d D_ __a". Almost any football fan would be able to tell that name is: David De Gea.

We get to a point where we're more likely to know rather than not. And that's how this new cpu system works. The variable m_minimumGuesses will be the number
the cpu has to get RIGHT before we dive into a deeper algorithm for it to guess correctly. The amount to get right at the moment is 2.


2) Reasoning for m_currentGuesses:

Keep track of how many we have to go to get to the next part of the algorithm.


3) Reasoning for m_pCurrentStringToBeGuessed:

We have to keep the actual string in order to sort it and do operations on it.


4) Reasoning for m_ppStringToSort:

We're using a dynamic 2d array so we can save the integer versions of characters, sort them, and apply operations on them.


5) Reasoning for m_xSize and m_ySize:

Keep the size of the dynamic 2d array.


6) Reasoning for m_spacesToSkip:

All the strings have spaces, that's a fact, we don't need to worry about spaces while searching the 2d dynamic integer array. This
variable helps us skip them.


7) Reasoning for m_previouslyEnteredCharacter:

Eventually we'll leave the update function but if IncreaseCpuCurrentGuesses is called, it needs to keep track of the character the cpu
entered in order to update the 2d array.


8) Reasoning for m_stringSize:

We need to keep the string size in order to better the algorithm. Well what was the old problem you might ask? I wrote code that made it so the cpu wasn't IMMORTAL.
Meaning that when they got past the minimum guesses, they'd just get the string easily from there. That code was:

    int random = (rand() % 10) + 1;

    if(random < 2)
    {
        // Use special rand() to get lowercase characters.
        *pLetter = (char)(rand() % (97 - 122) + 97);
        printf("RANDOM letter from GuessFromString function!\n");
    }

It's simple as you can see. If we get a random number lower than 2, than pick a different character. The PROBLEM was at a certain point, just like a human, they'll be able
to completely guess the string no worries. For example the string "Leo Messi" displayed as "L_o M_ss_i" would obviously be Lionel Messi to any football fan across the entire
planet. So we need to make the cpu guess better. Getting the string size is just the first part in that process because we'll get a FOURTH of that size, floor it, and use
that as the temporary max and the random number must be less than that. Example, let's say the string is "Eden Hazard", has 10 characters. 10 / 4 = 2.5, we'll floor it so
it's 2. Now:

    if(random < customMax)
    {
        *pLetter = (char)(rand() % (97 - 122) + 97);
    }

Every time the cpu guesses a correct character from the string. We decrement the customMax, we'll take the actual max, in this case 2 and then get a 4th or a 6th of it. Whatever
feels like a good decrement value. Ex: 2 / 4 = 0.5 This is a fourth of 2. 2 / 6 = 0.3 This is a sixth. The more characters guessed, the lower it goes until it hits zero
then it'll stay 0 and of course it'll be reset for the next string.


9) Reasoning for m_randomCharMaxRange:

It's for the above logic, see the customMax variable above. This will be the maximum or the boundary that the random number needs to be lesser than to get a random character.
Also it'll be altered, decremented by a 4th or 6th of itself.


10) Reasoning for m_decrementAmount:

Ties into the algorithm in #8, this will be the amount we decrement customMax while trying to get a random value.







                                                            Explanation of static variables:

1) Reasoning for s_timerDefault:

Give some timer before leaving this .c file so player can see what the cpu chooses.


2) Reasoning for s_minGuesses:

When a player guesses a string, we can take the football thing COMPLETELY out of the equation and factor in any regular old string, at a certain point they might
be able to guess the entire string on a few characters. If we're guessing cars, Ex: _ _ _ _ _ _ _ _. I guess m? M _ _ _ _ _ _ _. Now I guess e.
M e _ _ e _ e _. Maybe right now you can tell it's Mercedes. So after a certain amount of correct guesses. The cpu can then actually tackle the real string.


3) Reasoning for s_lastPosition:

Used in VowelBinarySearch function, when we force the cpu to go for vowels and it originally picks some random characters like "z", we know searching
for vowels with a character like "z", we'll fail, BUT, we save the last position or last index of the search and switch it to the vowel. Pretty interesting
way to go about it.


4) Reasoning for s_vowels:

Keep track of what vowels were currently used.


5) Reasoning for s_rows:

The rows in the dynamic array are 2. Only because we'll have all the integer values of characters in row 1, and whether we've use them (a true or false sort of
thing).


6) Reasoning for s_spaceIndicator:

This helps us determine if there was a space in the string, if so, we basically ignore it.


7) Reasoning for s_spaces:

On the ascii table, 32 is the numerical value of a space, once we detect one, we increment spaces to skip and also assign a space indicator in that index.


8) Reasoning for s_preTimer & s_postTimer:

These help the cpu wait before it rushes onto the next part of the code.


9) Reasoning for s_minChar & s_maxChar:

Helps the initial function to get a cpu key get one that is lowercase.


10) Reasoning for s_randRange:

Use this float for a more accurate range of floating point numbers in the GuessFromString function.


11) Reasoning for s_lowerBegin & s_lowerEnd:

Used in update to get proper range.


12) Reasoning for s_e/i/o/uKey:

These will be checked in the update function if StringBinarySearch does NOT find a vowel that the cpu can input. No a key necessary since that's taken care of by s_lowerBegin.


13) Reasoning for s_vowelArraySize:

All the main vowels are of course a, e, i, o, u. That's why this is 5 and used in vowel binary search.



*/

static const int s_minGuesses = 3;
static int s_lastPosition = -1;
static int s_vowels[VOWELS_ROWS][VOWELS_COLUMNS];
static const int s_rows = 2;
static const int s_spaceIndicator = -1;
static const int s_spaces = 32;
static int s_preTimer = TIMER_DEFAULT;
static int s_postTimer = TIMER_DEFAULT;
static const int s_minChar = 97;
static const int s_maxChar = 122;
static const float s_randRange = 10.0;
static const int s_lowerBegin = 97;
static const int s_lowerEnd = 122;
static const int s_eKey = 101;
static const int s_iKey = 105;
static const int s_oKey = 111;
static const int s_uKey = 117;
static const int s_vowelArraySize = 5;

struct CpuSmartGuess
{
    int m_minimumGuesses;
    int m_currentGuesses;
    char * m_pCurrentStringToBeGuessed;
    int ** m_ppStringToSort;
    int m_xSize;
    int m_ySize;
    int m_spacesToSkip;
    char m_previouslyEnteredChar;
    int m_stringSize;
    float m_randomCharMaxRange;
    float m_decrementAmount;
};

/** O(n). When we must update the stringToSort double pointer in the struct due to cpu guessing correctly, we'll do it here. Why even do that? Let's say we had the name
"Pierre Emerick Aubameyang", cpu goes through the vowel process and guesses i, well they're correct! But what if they get past the 3 required characters needed to
guess the full string? Well once we get there, the double pointer won't be updated with the "i" we guessed because we never bothered to beforehand. This function
ensures no repeats when it's time to crack at the full string.

Why is it in O(n) time? Well there are some repeat characters in the string "Pierre Emerick Aubameyang". Like "i". So if we did a binary search, sure we'd FIND
i, but just ONE of them, we need to make sure we set all of the possible "i" characters to true! */
static void UpdateStringToSort(CpuSmartGuessPtr csgp, const char character)
{
    // Get int version of the character.
    int charToNum = (int)character;

    // Start the loop from the spaces to skip, ignoring any spaces.
    for(int i = csgp->m_spacesToSkip; i < csgp->m_xSize; ++i)
    {
        // If an index is the integer value of our character.
        if(csgp->m_ppStringToSort[0][i] == charToNum)
        {
            // Set it's row 2 value to true.
            csgp->m_ppStringToSort[1][i] = true;
        }
    }
}

// O(n). Get the initial input.
static char CSGP_GetCpuInput(CpuSmartGuessPtr csgp)
{
    // Print message indicating cpu is thinking.
    printf("Cpu deciding what letter to choose...\n");

    // Ready the variable to return outside of loop below.
    char c = '/';

    // A small timer to give the cpu time.
    while(s_preTimer != 0)
    {
        --s_preTimer;
    }

    // Decide what the cpu will choose regarding a character.
    c = (char)(rand() % (s_maxChar - s_minChar + 1)) + s_minChar;

    while(s_postTimer != 0)
    {
        --s_postTimer;
    }

    // Reset the timers.
    s_preTimer = TIMER_DEFAULT;
    s_postTimer = TIMER_DEFAULT;

    // Return the character.
    return c;
}

// Let's see if the cpu already guessed the character "e",
static void UpdateCharacterUse(CpuSmartGuessPtr csgp, char * pLetter)
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

// O(n). This function just checks to see if the random character selected by the cpu is already in use. This process helps us get no repeats.
static bool CharacterBeenUsed(CpuSmartGuessPtr csgp, char * pCharacter)
{
    // Get int version of the character.
    int charToNum = (int)*pCharacter;

    // Start the loop from the spaces to skip, ignoring any spaces.
    for(int i = csgp->m_spacesToSkip; i < csgp->m_xSize; ++i)
    {
        // If an index is the integer value of our character AND if it's state is not "been used".
        if(csgp->m_ppStringToSort[0][i] == charToNum && csgp->m_ppStringToSort[1][i] == 1)
        {
            return true;
        }
    }

    return false;
}

// O(n). This function is for the ai to guess the rest of the string, somewhat like a human can do when they see the name.
static void GuessFromString(CpuSmartGuessPtr csgp, char * pLetter)
{
    // Check if the random number we get is less than the required value, if so, get a random character from entire alphabet.
    float random = ((float)rand() / (float)(RAND_MAX)) * s_randRange;

    // If less than max range, get a random character.
    if(random < csgp->m_randomCharMaxRange)
    {
        // Use special rand() to get lowercase characters.
        *pLetter = (char)(rand() % (s_lowerBegin - s_lowerEnd) + s_lowerBegin);

        // If we try and detect if the character has been used, simply select another one then continue until the function is false.
        while(CharacterBeenUsed(csgp, pLetter))
        {
            *pLetter = (char)(rand() % (s_lowerBegin - s_lowerEnd) + s_lowerBegin);
            continue;
        }
    }

    // If that's not the case, then we take a random character from the 2d array.
    else
    {
        for(int i = 0; i < csgp->m_xSize; ++i)
        {
            if(csgp->m_ppStringToSort[1][i] == 0 && csgp->m_ppStringToSort[0][i] != s_spaceIndicator)
            {
                // Get a random character in the double array according to the spaces to skip.
                *pLetter = (char)csgp->m_ppStringToSort[0][i];

                // Set it to used.
                csgp->m_ppStringToSort[1][i] = true;

                break;
            }
        }
    }
}

// O(log n). Be able to take an integer character that we KNOW is likely not here but still match it to a close vowel so the cpu can use.
static int VowelBinarySearch(CpuSmartGuessPtr csgp, const int searchValue)
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
            // printf("Index: %d\n", index);
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

// O(n). When the cpu runs out of guesses, we need to reset certain things.
static void CSGP_WipeData(CpuSmartGuessPtr csgp)
{
    // Delete the dynamic array and replace it with new string.
    for(int i = 0; i < s_rows; ++i)
    {
        free(csgp->m_ppStringToSort[i]);
        csgp->m_ppStringToSort[i] = NULL;
    }

    free(csgp->m_ppStringToSort);
    csgp->m_ppStringToSort = NULL;

    // Set current guesses back to 0.
    csgp->m_currentGuesses = 0;

    // Set current string to be guessed to empty.
    csgp->m_pCurrentStringToBeGuessed = "";

    // Set spaces to skip back to 0.
    csgp->m_spacesToSkip = 0;

    // Set sizes x and y to be 0.
    csgp->m_xSize = 0;
    csgp->m_ySize = 0;

    // Reset the 3 variables to help us with random characters.
    csgp->m_stringSize = 0;
    csgp->m_randomCharMaxRange = 0.0f;
    csgp->m_decrementAmount = 0.0f;

    // Reset the active states in the vowel arrays.
    for(int i = 0; i < VOWELS_COLUMNS; ++i)
    {
        s_vowels[1][i] = 0;
    }
}

// O(n^2). worst/average case. Run insertion sort on the string because we'll help the cpu get "ranges" of where to guess.
static void InsertionSort(CpuSmartGuessPtr csgp)
{
    // Loop.
    for(int i = 1; i < csgp->m_xSize; ++i)
    {
        // Grab the key with the loop variable i.
        int key = csgp->m_ppStringToSort[0][i];

        // Get the previous index since this is a backtracking algorithm.
        int j = i - 1;

        // Check if j is still within array range (0 to n) and the value behind key is greater.
        while(j >= 0 && csgp->m_ppStringToSort[0][j] > key)
        {
            // Set what's in FRONT of j, TO j.
            csgp->m_ppStringToSort[0][j + 1] = csgp->m_ppStringToSort[0][j];

            // Decrement.
            j = j - 1;
        }

        // Put the old key back in the array.
        csgp->m_ppStringToSort[0][j + 1] = key;
    }
}

// O(n) + memory allocation. Allocate the 2d array needed for the cpu turn.
static void Allocate2dArray(CpuSmartGuessPtr csgp, const char * pString)
{
    /** Allocate memory for the ROWS. This begs the question, why do this 2d dynamically while the vowels array is not done the same way? Couldn't we make a regular
    array? Well we could but it'd be to no use. Because the vowels array is of constant size, it's literally never going to change. It's safe the way it is. With
    the dynamic array, we have to allocate memory for the string passed and future strings. */
    csgp->m_ppStringToSort = (int**)malloc(csgp->m_ySize * sizeof(int*));

    // Allocate memory for each COLUMN according to string length.
    for(int i = 0; i < csgp->m_ySize; ++i)
    {
        csgp->m_ppStringToSort[i] = (int*)malloc(csgp->m_xSize * sizeof(int));
    }

    // Get the entire first row to be the int values in the string.
    for(int i = 0; i < csgp->m_xSize; ++i)
    {
        // Make sure no spaces get in.
        if(pString[i] == s_spaces)
        {
            // Set this value in the array to -1.
            csgp->m_ppStringToSort[0][i] = s_spaceIndicator;

            // Increase this variable to help with the overall algorithm as explained above.
            csgp->m_spacesToSkip = csgp->m_spacesToSkip + 1;

            // Print a space just to keep the overall string looking normal.
            printf(" ");

            // Proceed with loop.
            continue;
        }

        // Do we have capital letters in the string? Make them lowercase, makes it easier for an algorithm to deal with only one or the either, not both.
        else if((int)pString[i] >= 65 && (int)pString[i] <= 90)
        {
            // Get the lower case version by simply adding a constant of 32.
            int lower = (int)pString[i] + s_spaces;

            // Assign that new character to the string with lower integer previously created..
            csgp->m_ppStringToSort[0][i] = (char)lower;

            // Increase the size.
            csgp->m_stringSize += 1;
        }

        // If it's already lowercase, great!
        else
        {
            // Assign that new character to the string.
            csgp->m_ppStringToSort[0][i] = (int)pString[i];

            // Increase the size.
            csgp->m_stringSize += 1;
        }
    }

    // Second row will be binary, either true or false, so 1 or 0, to tell whether this key was chosen already or not.
    for(int i = 0; i < csgp->m_xSize; ++i)
    {
        csgp->m_ppStringToSort[1][i] = 0;
    }

    // Calculate a fourth of the string.
    csgp->m_randomCharMaxRange = floor(csgp->m_stringSize / 4.0f);

    // Set the decrement amount by calculating the fourth of the random char max range.
    csgp->m_decrementAmount = csgp->m_randomCharMaxRange / 4.0f;

    // Use insertion sort to sort the 2d arrays integers.
    InsertionSort(csgp);
}

// In order for the cpu to have LESS of a chance entering a random character despite it "knowing" the string already, decrementing the range lesses the chance of that.
static void DecrementRandomMaxRange(CpuSmartGuessPtr csgp)
{
    // Check if already 0. If so, do not decrement.
    if(csgp->m_randomCharMaxRange == 0.0f)
    {
        return;
    }

    // Do the math of getting the max and decrementing by the saved amount. 4th, 6th, whatever it might be.
    float value = csgp->m_randomCharMaxRange - csgp->m_decrementAmount;

    // If the value is less than 0, just set max to 0.
    if(value <= 0.0f)
    {
        csgp->m_randomCharMaxRange = 0.0f;
    }

    else
    {
        // If it's not 0, then set the max to the value above. Ex: If max is 2, and the decrement amount if 0.3, result will be 1.7.
        csgp->m_randomCharMaxRange = value;
    }
}

// O(n log n). This binary search is to help determine if vowels are still available in the stringToSort. If so, we can make accurate guesses, if not, we'll have to adjust.
static int StringBinarySearch(CpuSmartGuessPtr csgp)
{
    // Start off by looping over the s_vowels array.
    for(int i = 0; i < VOWELS_COLUMNS; ++i)
    {
        // Get the value of the vowel in the array.
        int value = s_vowels[0][i];

        // Set low.
        int low = 0;

        // Set high.
        int high = csgp->m_xSize - 1;

        // While low is less than high because otherwise we've ran out of space to search.
        while(low <= high)
        {
            // Calculate the midpoint the same way we'd do in say, merge sort.
            int midpoint = (low + high) / 2;

            // printf("Value: %d. Low: %d. High: %d. Midpoint: %d.\n", value, low, high, midpoint);

            // If search value is at this midpoint, that's one half, then check this vowel still has a false value. Indicating we have not used it yet.
            if(value == csgp->m_ppStringToSort[0][midpoint] && csgp->m_ppStringToSort[1][midpoint] == 0)
            {
                // If we found one and haven't used it yet, great! We can return true because we still have vowels available.
                return true;
            }

            else if(value < csgp->m_ppStringToSort[0][midpoint])
            {
                high = midpoint - 1;
                continue;
            }

            else if(value > csgp->m_ppStringToSort[0][midpoint])
            {
                low = midpoint + 1;
                continue;
            }

            break;
        }
    }

    return false;
}

CpuSmartGuessPtr CSGP_Init(char * pString)
{
    // Allocate memory for the structure.
    CpuSmartGuessPtr pSgp = malloc(sizeof * pSgp);

    // Check if null, return if so.
    if(!pSgp)
    {
        printf("SmartStringGuess null!\n");
        return NULL;
    }

    // If not null, carry on.
    else
    {
        // Set current guesses to 0 to begin and set minimum guesses to the desired minimum.
        pSgp->m_currentGuesses = 0;
        pSgp->m_minimumGuesses = s_minGuesses;

        /** Save the string passed in order to potentially need it for the later algorithm later in the cpu's guesses. When the cpu guesses enough, it'll be able
        to basically "know" the string in a sense and start filling it in just like a human. */
        pSgp->m_pCurrentStringToBeGuessed = pString;


        /** Set the space skip variable, because the strings in fact have spaces. Eventually, we'll create the dynamic 2d int array and be able to convert indexes
        to char and back to int. But while in integer form, we'll replace the spaces with a default value of -1. And this spacesToSkip variable will help us know
        where to START in the array. For example, if we have a string like "Michael Essien", there's clearly a space in there. It would take that into account and
        the final string would be:

        -1         97 99 101 101 101 104 105 105 108 109 110 115 115
        S (space)  a  c   e   e   e   h   i   i   l   m   n   s   s

        Since there's 1 space, we know we begin any algorithm, in the difficult part, at index 1 of the dynamic array. */
        pSgp->m_spacesToSkip = 0;

        // Initialize string size to 0.
        pSgp->m_stringSize = 0;

        // Get string length to help with dynamic memory allocation and save in the size.
        pSgp->m_xSize = strlen(pSgp->m_pCurrentStringToBeGuessed); // Columns.
        pSgp->m_ySize = s_rows; // Rows.

        // Allocate memory for 2d array.
        Allocate2dArray(pSgp, pString);

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

    // Return the sgp.
    return pSgp;
}

/** Get input for cpu. The letter comes from the CpuInput.c function called GetCpuInput.
O(n) - Best case, because once the minimum guesses is reached, we'll be using guess from string function, which is an O(n) function.

O(n) - Average case. Why is it average? Because the minimum guesses is 3, the first if statement will only run for an average of 3 times.
(Give or take because the cpu MIGHT still get a character wrong despite it even starting out with vowels.) But once it does exhaust vowels
and reaches past the minimum guesses (this will happen more than not in the game), we'll begin using the guess from string function.

O(n log n) - Worst case. O(n log n)  + O(log n) + O(n) is the FULL version. This is weird but I believe accurate. This will take the most time
if StringBinarySearch is NOT false, so IT'S runtime of n log n is already done and through. Then we go to VowelBinarySearch and that's log n,
factor that in as well. The function VowelBinarySearch might or might not be true but regardless, UpdateCharacterUse will run and that's O(n).
Asymptotic notation makes us drop the low ordered terms, so we're left with O(n log n) being the worst case scenario.

*/
char CSGP_Update(CpuSmartGuessPtr csgp)
{
    // Get letter from initial function.
    char letter = CSGP_GetCpuInput(csgp);

    /** Minimum guesses could be anything, 1, 2, 3, to n, and when the current guesses is lower, the 2nd part of the algorithm won't run. Remember we want
    the cpu to work somewhat like a human, if a human is guessing a string and midway they see "M___tain" they're most likely to guess "Mountain". That's
    the point of the current guesses and minimum guesses. We have to have the cpu meet the minimum guesses in order to really "know" the string like a
    human being would. */
    if(csgp->m_currentGuesses < s_minGuesses)
    {
        /** This helps the cpu be able to still make guesses without enough vowels to make the "easy" guesses I could say. For example take literally any
        string right now. One preferably with 1 or 2 vowels. We can take "Eden Hazard" for example. Only has vowels a and e. So at BEST the old  algorithm
        could get those 2 but it'll still TRY to use the remaining vowels despite none being available in the string. That's where we improvise and begin
        choosing at random in order to get to the minimum number of 3 for the cpu to guess the entire string.

        If a string has 1 vowel, it'll find that one vowel and if the cpu guesses that vowel, we ran out of remaining vowels to choose. That's basically
        what the if statement with StringBinarySearch does.

        The string binary search works in O(n log n). to see if we have vowels to pull from the string. It's possible there will be none. And if there's none
        we will get a random character and throw it as our guess. */
        if(!StringBinarySearch(csgp))
        {
            // It's false, so that means we're out of vowels to choose or there were none present. Set another variable because we'll get ourselves a random letter now.
            int value = 0;

            // Run this while loop as long as the value equals yet another vowel. None exist, so there's no point in going with that.
            do {
                // Get a random lowercase character.
                value = (rand() % (s_lowerBegin - s_lowerEnd) + s_lowerBegin);

                // Convert to character.
                letter = (char)value;

                // Now we have a valid letter, update the string.
                UpdateStringToSort(csgp, letter);

            } while(value == s_lowerBegin || value == s_eKey || value == s_iKey || value == s_oKey || value == s_uKey);

        }

        /** The char argument passed was a vowel, great, in these types of games humans almost always start with vowels to give hints on the entire string.
        So the function VowelBinarySearch checks if it was a vowel that we received. */
        else if(VowelBinarySearch(csgp, (int)letter) > -1)
        {
            // Set the character in the array to true.
            UpdateCharacterUse(csgp, &letter);

            // Set the previously entered character for later IF it's the correct character to update the string to sort.
            csgp->m_previouslyEnteredChar = letter;
        }

        else
        {
            // If the last position is out of bounds that means the search didn't work. Char AFTER u was inserted.
            if(s_lastPosition >= VOWELS_COLUMNS)
            {
                s_lastPosition = 4;
            }

            // Set the character in the array to true.
            UpdateCharacterUse(csgp, &letter);

            // Set the previously entered character for later IF it's the correct character to update the string to sort.
            csgp->m_previouslyEnteredChar = letter;
        }
    }

    else
    {
        // Call function to get character from real string.
        GuessFromString(csgp, &letter);

        // Set the previously entered character for later IF it's the correct character to update the string to sort.
        csgp->m_previouslyEnteredChar = letter;

        printf("\n");
    }

    // Display what the cpu chose.
    printf("Cpu chooses %c!\n", letter);
    printf("Press (enter) to continue.\n");
    getchar();

    return letter;
}

// We have to be able to increase guesses in order to move forward in the algorithm.
void CSGP_IncreaseCpuCurrentGuesses(CpuSmartGuessPtr csgp)
{
    // Just increase by 1.
    csgp->m_currentGuesses += 1;

    // Update the double pointer to the entered character, so if cpu DOES end up getting 3 characters and then start picking from string, it won't REPEAT characters.
    UpdateStringToSort(csgp, csgp->m_previouslyEnteredChar);

    // Decrement the max range.
    DecrementRandomMaxRange(csgp);
}

void CSGP_SetData(CpuSmartGuessPtr csgp, char * pString)
{
    // We'll be setting data but don't want to OVERWRITE our CURRENT data. So check the string, if greater than 0 we know we have previous data and pointers used.
    if(strlen(csgp->m_pCurrentStringToBeGuessed) > 0)
    {
        // Wipe all of that data out before we set the new one.
        CSGP_WipeData(csgp);
    }

    /** Save the string passed in order to potentially need it for the later algorithm later in the cpu's guesses. When the cpu guesses enough, it'll be able
    to basically "know" the string in a sense and start filling it in just like a human. */
    csgp->m_pCurrentStringToBeGuessed = pString;

    // Get string length to help with dynamic memory allocation.
    int strLength = strlen(csgp->m_pCurrentStringToBeGuessed);

    // Save the sizes.
    csgp->m_xSize = strLength;
    csgp->m_ySize = s_rows;

    // Allocate memory for 2d array.
    Allocate2dArray(csgp, pString);
}

void CSGP_Destroy(CpuSmartGuessPtr csgp)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!csgp)
    {
        return;
    }

    // Wipe the dynamic arrays values.
    for(int i = 0; i < s_rows; ++i)
    {
        if(csgp->m_ppStringToSort[i])
        {
            free(csgp->m_ppStringToSort[i]);
            csgp->m_ppStringToSort[i] = NULL;
        }
    }

    // Wipe the dynamic array itself.
    if(csgp->m_ppStringToSort != NULL)
    {
        free(csgp->m_ppStringToSort);
        csgp->m_ppStringToSort = NULL;
    }

    // Delete self.
    free(csgp);
    csgp = NULL;
}

#endif // CPUSMARTSTRINGGUESS_C_INCLUDED
