#ifndef CPUSMARTSTRINGGUESS_H_INCLUDED
#define CPUSMARTSTRINGGUESS_H_INCLUDED

/** Reasoning for this interface:

This will help the cpu system. The OLD cpu system literally guessed random characters over and over. Obviously that's a failing system because who knows if
it will EVER be able to guess a string correctly. This interface will provide functions to help just the cpu with getting a string correctly and force it to
make smarter choices.


1) Reasoning for CpuSmartGuessPtr:

Standard part of the abstract data type in c is to have a typedef struct in the header file.


2) Reasoning for CSGP_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


3) Reasoning for CSGP_Update:

Be able to potentially change the letter to a smart, more sensible choice. This actually helps the cpu not play like a bloody idiot. Choosing random characters in a string?
Not exactly wise. We could have something like "John Terry" as a string, and any football fan (especially Chelsea supporter like me) can tell "Jo_n Terry" is "John Terry".
So we help the cpu by letting it check for vowels like I seen people do in most game shows, and when it gets to a certain point, it knows what the string is potentially.


4) Reasoning for CSGP_IncreaseCpuCurrentGuesses:

When we make a correct guess, we'll have to let this interface take record, because once we get enough correct guesses (like a human) we'll know the string and be able to
easily figure it out. Same applies to the cpu. We have to go through GameParticipants.c, and Cpu.c, to eventually come to this function. But it's vital for the overall
algorithm.


5) Reasoning for CSGP_SetData:

When it's time for the cpu's turn, we'll set the data here, giving it the current string to be guessed for the later part of the algorithm.


6) Reasoning for CSGP_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.



                                                                                Algorithm Analysis:

1) During initialization, we allocate memory fort he CpuSmartGuessPtr (call this m1, m is memory).

Allocate for the double array, (m2).

Allocate each value in the double array, (O(n)).

There's a portion of code to take care of spaces, upper case character and put them all in the 2d array, (O(n)).

Another loop to set the 2nd row of the double pointer to default 0's. (O(n)).

Insertion sort, in order to SORT the array. We do this because the function UpdateStringToSort is called to update if we found a "a" in the string, (O(n^2)).

Initialize the vowels array, (O(n)).

Total is m1 + m2 + O(n) + O(n) + O(n) + O(n^2) + O(n).

The biggest is O(n^2), so we can say the overall time is O(n^2) for initialization.



2) Each of the functions runs in a pretty decent time. Let's consider the big o cheat sheet for a second here: https://www.bigocheatsheet.com/

The top 4 (champions league) run times are O(1), O(log n), O(n), and O(n log n). And our primary functions used in the algorithm are:

a. StringBinarySearch - O(n log n).
b. Allocate2dArray - Multiple for loops O(n) + memory to allocate dynamic array + O(n^2) for Insertion sort. Since asymptotic notation makes us drop the low terms, we can
say this runs in O(n^2) time.
c. VowelBinarySearch - O(log n).
e. GuessFromString - Worst case O(n).
f. UpdateStringToSort - O(n).
g. CharacterBeenUsed - O(n).

*/

typedef struct CpuSmartGuess * CpuSmartGuessPtr;

CpuSmartGuessPtr CSGP_Init(char * pString);
char CSGP_Update(CpuSmartGuessPtr csgp);
void CSGP_IncreaseCpuCurrentGuesses(CpuSmartGuessPtr csgp);
void CSGP_SetData(CpuSmartGuessPtr csgp, char * pString);
void CSGP_Destroy(CpuSmartGuessPtr csgp);


#endif // CPUSMARTSTRINGGUESS_H_INCLUDED
