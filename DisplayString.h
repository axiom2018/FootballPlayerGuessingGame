#ifndef DISPLAYSTRING_H_INCLUDED
#define DISPLAYSTRING_H_INCLUDED

/* Reasoning for this interface:

The reasoning for this interface is because we'll need one single way to display the string to be guessed. Of course this string will start out with default characters like
"_____ _____" and let's say the string is "Lionel Messi". First I thought about using a state pattern for each individual character in the string but that would slightly
complicate the code unnecessarily and take up more memory if each character had a state. Then I decided maybe we can have a struct with a single character for an entry
in a true and a boolean to control whether it was displayed or not. We'd have to declare a plethora of those structures for every single string, costing us more memory with
each string the player or cpu to guess. This interface makes it easier. It doesn't abuse memory, and also it's one interface to use for all our string displaying needs.

How it works is simple.


                                                                                Interface variables:

1) Reasoning for DisplayStringPtr:

Standard part of the abstract data type in c is to have a typedef structure in the header file.


                                                                                Interface functions:

1) Reasoning for DisplayString_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer. This will be given a string to set up the game so the participants can
have a string to guess at immediately.


2) Reasoning for DisplayString_AssignString:

We'll have to change strings at some point, that functionality will be here.


3) Reasoning for DisplayString_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

 */

 typedef struct DisplayString * DisplayStringPtr;

DisplayStringPtr DisplayString_Init(const char * pNameOfFootballPlayer);
void DisplayString_AssignString(DisplayStringPtr displayString, const char * pString);
void DisplayString_Destroy(DisplayStringPtr displayString);

#endif // DISPLAYSTRING_H_INCLUDED
