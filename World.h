#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

/* Reasoning for this interface:

Use the first class abstract data type to create an interface for the world of the game so we can carry out critical operations to run the game.


                                                                                Interface variables:

1) Reasoning for WorldPtr:

Standard part of the abstract data type in c is to have a typedef struct in the header file.


                                                                                Interface functions:

1) Reasoning for World_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for Update:

Allow the World to go through the motions of managing the player and cpu in a single function and make the main.c file very simple and easy.


3) Reasoning for World_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

 */

typedef struct World * WorldPtr;

WorldPtr World_Init();
void UpdateWorld(WorldPtr world);
void ClearScreen(WorldPtr world);
void World_Destroy(WorldPtr world);

#endif // WORLD_H_INCLUDED
