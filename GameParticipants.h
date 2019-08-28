#ifndef GAMEPARTICIPANTS_H_INCLUDED
#define GAMEPARTICIPANTS_H_INCLUDED

/** Reasoning for this interface:

Have one central place to control the player and cpu.

                                                                                Interface variables:

1) Reasoning for GameParticipantsPtr:

Standard part of the abstract data type in c is to have a typedef struct in the header file.


                                                                                Interface functions:

1) Reasoning for GP_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for GP_SetStringForCpu:

This helps initialize the cpu with a string only when the time is right.


3) Reasoning for GP_Update:

Update the participants when we need input from them.


4) Reasoning for GP_SwitchParticipants:

When it's another participants turn, switch to the other one.


5) Reasoning for GP_AwardPoints:

Each word of course has a set of points to be won, this function will allow us to hand the points over.


6) Reasoning for GP_GameWinner:

Once either participant has reached the minimum score to win, they will win.


7) Reasoning for GP_DisplayPoints:

Show the scores and who is close to winning to present some urgency.


8) Reasoning for GP_IncreaseCpuCurrentGuesses:

Once the cpu gets past n amount of guesses (let's say 3), then the more advanced part of the algorithm starts.


9) Reasoning for GP_SetCpuData:

In order for the cpu to properly take it's turn, we must set it with the string due to it's algorithm.


10) Reasoning for GP_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.


*/

typedef struct GameParticipants * GameParticipantsPtr;

GameParticipantsPtr GP_Init(char * pString);
void GP_SetStringForCpu(GameParticipantsPtr gpp, char * pString);
char GP_Update(GameParticipantsPtr gpp);
void GP_SwitchParticipants(GameParticipantsPtr gpp);
void GP_AwardPoints(GameParticipantsPtr gpp, const int points);
int GP_GameWinner(GameParticipantsPtr gpp, const int pointsRequiredToWin);
void GP_DisplayPoints(GameParticipantsPtr gpp, const int pointsToWin);
void GP_IncreaseCpuCurrentGuesses(GameParticipantsPtr gpp);
void GP_SetCpuData(GameParticipantsPtr gpp, char * pString);
void GP_Destroy(GameParticipantsPtr gpp);

#endif // GAMEPARTICIPANTS_H_INCLUDED
