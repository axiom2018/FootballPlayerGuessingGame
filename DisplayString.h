#ifndef DISPLAYSTRING_H_INCLUDED
#define DISPLAYSTRING_H_INCLUDED

/** Reasoning for this interface:

The reasoning for this interface is because we'll need one single way to display the string to be guessed. Of course this string will start out with default characters like
"_____ _____" and let's say the string is "Lionel Messi". First I thought about using a state pattern for each individual character in the string but that would slightly
complicate the code unnecessarily and take up more memory if each character had a state. Then I decided maybe we can have a struct with a single character for an entry
in a true and a boolean to control whether it was displayed or not. We'd have to declare a plethora of those structures for every single string, costing us more memory with
each string the player or cpu to guess. This interface makes it easier. It might use memory to allocate space for strings but it DOESN'T need any extra overhead from say
a state pattern or unnecessary structure.


                                                                                Interface variables:

1) Reasoning for DisplayStringPtr:

Standard part of the abstract data type in c is to have a typedef structure in the header file.


                                                                                Interface functions:

1) Reasoning for DS_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer. This will be given a string to set up the game so the participants can
have a string to guess at immediately.


2) Reasoning for DS_AssignString:

We'll have to change strings at some point, that functionality will be here.


3) Reasoning for DS_GetString:

Hand it over to the cpu so it's algorithm gets properly set up.


4) Reasoning for DS_ShowHiddenString:

We need to show the string with the characters they're guessing at to confirm whether they got it or not.


5) Reasoning for DS_CheckStringForMatchingChar:

The DISPLAY string has no characters relating to the real character, however the real string inside the structure in the .c file does have it. We'll loop and
figure out if the passed character is inside the string, and update the index of the display string if indeed that's true.


6) Reasoning for DS_GuessCompleted:

If a participant has completed the task of guessing a word, this function will indicate that.


7) Reasoning for DS_GetPoints:

Each word has a certain amount of points that the participant can win if they guess it correctly.


8) Reasoning for DS_DisplayTriesLeft:

Show how many tries the turn participant has at guessing before their turn is done.


9) Reasoning for DS_CanParticpantContinue:

If the tries are done, their turn is up.


10) Reasoning for DS_DecrementTriesLeft:

If they make a wrong guess, decrement tries.


11) Reasoning for DS_CharAlreadyEntered:

If we have a string like "Thierry Henry" and we already entered the r key, and enter it again, this function will pick up on that. No need to decrement tries.


12) Reasoning for DS_DisplayPointsForName:

Let the player know how many possible points they can win by displaying how many points the word is worth.


13) Reasoning for DS_Reset:

There are quite a few variables that need to go back to their "base" assignments to prepare for the next participants turn to guess.


14) Reasoning for DisplayString_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

 */

typedef struct DisplayString * DisplayStringPtr;

DisplayStringPtr DS_Init(const char * pNameOfFootballPlayer);
void DS_AssignString(DisplayStringPtr ds, const char * pString);
char * DS_GetString(DisplayStringPtr ds);
void DS_ShowHiddenString(DisplayStringPtr ds);
int DS_CheckStringForMatchingChar(DisplayStringPtr ds, const char input);
int DS_GuessCompleted(DisplayStringPtr ds);
int DS_GetPoints(DisplayStringPtr ds);
void DS_DisplayTriesLeft(DisplayStringPtr ds);
int DS_CanParticipantContinue(DisplayStringPtr ds);
void DS_DecrementTriesLeft(DisplayStringPtr ds);
int DS_CharAlreadyEntered(DisplayStringPtr ds, const char input);
void DS_DisplayPointsForName(DisplayStringPtr ds);
void DS_Reset(DisplayStringPtr ds);
void DS_Destroy(DisplayStringPtr ds);

#endif // DISPLAYSTRING_H_INCLUDED
