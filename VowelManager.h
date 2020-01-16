#ifndef VOWELMANAGER_H_INCLUDED
#define VOWELMANAGER_H_INCLUDED

/** Reasoning for this interface:

Use the abstract data type to create an interface for the player of the game so we can carry out certain operations when it comes to vowel operations
inside of CpuSmartStringGuess. The old implementation had a lot of clunky functions in it that made that one file an eye sore, but here we follow SRP
a bit better by making an interface that has ONE job, just handle the vowel business. My INITIAL idea was to use a hash table for a data structure,
but whilst I was coding it up I realized most of the interface functions on the hash were significantly slower than our current implementation.
As of 1/15/2020 here are the function comparisons of the hash vs current implementation with array inside of CpuSmartStringGuess:

---Hash---
Insert: n
VowelsLeft: n^2
UpdateVowel: n^2
DestroyHashTable: n^2

---Array---
StringBinarySearch: n^2
UpdateStringToSort: n
VowelBinarySearch: log n
UpdateCharacterUse: n

What the functions do isn't really important to explain right now but they were all necessary to get the job done. As we can see, the hash would be
significantly slower AND also take up more memory, so I've decided against it. So this interface cleans up the code in CpuSmartStringGuess, and follows SRP.
Win, win.



                                                                                Interface variables:

1) Reasoning for VowelManagerPtr:

Standard part of the abstract data type in c is to have a typedef structure in the header file.


                                                                                Interface functions:

1) Reasoning for VowelManager_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for StringBinarySearch:

To help determine if vowels are even still available in the string.


3) Reasoning for VowelBinarySearch:

Searches and checks to see if cpu input was a vowel.


4) Reasoning for UpdateCharacterUse:

Continue to find a vowel that was NOT used, if the one at the s_lastPosition index WAS used.


5) Reasoning for LastPositionOutOfBounds:

It's possible that this happens, it exceeds 5 or equals it, bring it back down to index 4.


6) Reasoning for FullReset:

The states of the vowel will change frequently to used, so undo that in this function when we have a new string.


7) Reasoning for UpdateSizeAndString:

When it's time to guess a new string, simply pass the string and size to this function.


5) Reasoning for VowelManager_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

*/

typedef struct VowelManager * VowelManagerPtr;

VowelManagerPtr VowelManager_Init(const int strSize, int ** ppStringToSort);
int StringBinarySearch(VowelManagerPtr pVMP);
int VowelBinarySearch(VowelManagerPtr pVMP, const int searchValue);
void UpdateCharacterUse(VowelManagerPtr pVMP, char * pLetter);
void LastPositionOutOfBounds(VowelManagerPtr pVMP);
void FullReset(VowelManagerPtr pVMP);
void UpdateSizeAndString(VowelManagerPtr pVMP, const int strSize, int ** ppStringToSort);
void VowelManager_Destroy(VowelManagerPtr pVMP);

#endif // VOWELMANAGER_H_INCLUDED
