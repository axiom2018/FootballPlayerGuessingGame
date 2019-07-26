#ifndef WORLD_C_INCLUDED
#define WORLD_C_INCLUDED
#include "World.h"
#include <stdio.h> // printf.
#include <stdlib.h> // malloc, free.
#include <stdbool.h> // Boolean.
#include "Player.h" // Create the player to participate in the game.
#include "Cpu.h" // Create the computer to participate in the game.
#include "DisplayString.h" // Create the string displayer to show the string the player and computer are trying to guess.
#include <windows.h> // system("cls").
#include <string.h>
#include <assert.h>

#define NUMBER_OF_STRINGS 3
#define SIZE_OF_STRINGS 4

struct World
{
    // Boolean to keep the game running.
    bool m_gameRunning;

    // The player first class abstract data type.
    PlayerPtr m_pPlayer;

    // The cpu first class abstract data type.
    CpuPtr m_pCpu;

    // The display string first class abstract data type.
    DisplayStringPtr m_pDisplayString;
};

const char * pNameOfFootballer = "Roberto Di Matteo";

WorldPtr World_Init()
{
    // Allocate memory for the World structure.
    WorldPtr pPointer = malloc(sizeof * pPointer);

    // Set the game running to true for the Update function.
    pPointer->m_gameRunning = true;

    // Allocate memory for the Player structure.
    pPointer->m_pPlayer = Player_Init();

    // Allocate memory for the Cpu structure.
    pPointer->m_pCpu = Cpu_Init();

    // Allocate memory for the DisplayString structure.
    pPointer->m_pDisplayString = DisplayString_Init(pNameOfFootballer);

    // Test the ability to reassign a string.
    DisplayString_AssignString(pPointer->m_pDisplayString, "Frank Lampard");

    // Return the pointer to be assigned.
    return pPointer;
}

void UpdateWorld(WorldPtr world)
{
    // Run the game loop as long as the boolean is true.
    while(world->m_gameRunning)
    {
        // Set to false to prevent infinite loop.
        world->m_gameRunning = false;
    }
}

void ClearScreen(WorldPtr world)
{
    system("cls");
}

void World_Destroy(WorldPtr world)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!world)
    {
        return;
    }

    // Delete the pointers inside the structure.
    DisplayString_Destroy(world->m_pDisplayString);
    Cpu_Destroy(world->m_pCpu);
    Player_Destroy(world->m_pPlayer);

    // Then delete pointer passed.
    printf("Cleaning world.\n");
    free(world);
}

#endif // WORLD_C_INCLUDED
