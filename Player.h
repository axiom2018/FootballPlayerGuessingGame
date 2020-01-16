#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

/** Reasoning for this interface:

Use the abstract data type to create an interface for the player of the game so we can carry out certain operations on the player.


                                                                                Interface variables:

1) Reasoning for PlayerPtr:

Standard part of the abstract data type in c is to have a typedef structure in the header file.


                                                                                Interface functions:

1) Reasoning for Player_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for Player_Update:

Allow the player to give us input regarding their guess to what letter(s) are in the footballers name.


3) Reasoning for Player_IncreasePoints:

Give player more points for guessing footballer correctly.


4) Reasoning for Player_GetPoints:

Return the players points.


5) Reasoning for Player_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

*/

typedef struct Player * PlayerPtr;

PlayerPtr Player_Init();
char Player_Update(PlayerPtr player);
void Player_IncreasePoints(PlayerPtr player, const int points);
int Player_GetPoints(PlayerPtr player);
void Player_Destroy(PlayerPtr player);

#endif // PLAYER_H_INCLUDED
