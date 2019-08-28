#ifndef WORLD_C_INCLUDED
#define WORLD_C_INCLUDED
#include "World.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DisplayString.h"
#include "GameParticipants.h"
#include <windows.h>

// Simply the amount of points needed to win the game.
static const int s_pointsToWin = 3000;

// We must know what size we'd like to give each string. No footballer I've ever known has a name longer than 40 characters.
static const int s_maxNameSize = 40;

// Indicate how many strings we'll be using in the game when we allocate memory.
static const int s_maxStrings = 30;

struct World
{
    // The game participants will hold the player and cpu structure "objects".
    GameParticipantsPtr m_pGameParticipants;

    // The display string first class abstract data type.
    DisplayStringPtr m_pDisplayString;

    // Array of strings using double pointer.
    char ** m_ppNames;
};

// Function to help us get a random string in the double pointer inside the structure.
char * GetRandomString(WorldPtr world)
{
    // Get the random number of what string to begin with.
    int num = (rand() % s_maxStrings) + 0;

    // Return that entry in the array.
    return world->m_ppNames[num];
}

WorldPtr World_Init()
{
    // Allocate memory for the World structure.
    WorldPtr pPointer = malloc(sizeof * pPointer);

    // Allocate memory for the double pointer, the main string container in the game.
    pPointer->m_ppNames = malloc(s_maxStrings * sizeof(char*));

    // Loop and allocate memory for each string, leaving space for a null terminating character.
    for(int i = 0; i < s_maxStrings; ++i)
    {
        // Allocate memory for each individual pointer.
        pPointer->m_ppNames[i] = malloc((s_maxNameSize + 1) * sizeof(char));
    }

    /** Manually assign the strings of the footballers in this initialization function. Also to display one, randomly get one and give it to m_pDisplayString.
    This system might look uneasy to manage but it actually is.

    To add in strings:

    Step 1 - Scroll up and increment s_maxStrings definition to however many you please.

    Step 2 - Make sure all those strings are entered in below.

    Example: If you want 5 strings, set s_maxStrings to 5, then from index 0 to 4. */
    pPointer->m_ppNames[0] = "Lionel Messi";
    pPointer->m_ppNames[1] = "Gareth Bale";
    pPointer->m_ppNames[2] = "Didier Drogba";
    pPointer->m_ppNames[3] = "Andres Iniesta";
    pPointer->m_ppNames[4] = "John Terry";
    pPointer->m_ppNames[5] = "Cristiano Ronaldo";
    pPointer->m_ppNames[6] = "David De Gea";
    pPointer->m_ppNames[7] = "Ashley Cole";
    pPointer->m_ppNames[8] = "Eden Hazard";
    pPointer->m_ppNames[9] = "Paul Pogba";
    pPointer->m_ppNames[10] = "Michael Essien";
    pPointer->m_ppNames[11] = "Thierry Henry";
    pPointer->m_ppNames[12] = "Bastian Schweinsteiger";
    pPointer->m_ppNames[13] = "Pierre Emerick Aubameyang";
    pPointer->m_ppNames[14] = "Mesut Ozil";

    pPointer->m_ppNames[15] = "Marcus Rashford";
    pPointer->m_ppNames[16] = "Ngolo Kante";
    pPointer->m_ppNames[17] = "Ronaldinho";
    pPointer->m_ppNames[18] = "Gerard Pique";
    pPointer->m_ppNames[19] = "Samuel Etoo";
    pPointer->m_ppNames[20] = "David Beckham";
    pPointer->m_ppNames[21] = "Petr Cech";
    pPointer->m_ppNames[22] = "Nemanja Matic";
    pPointer->m_ppNames[23] = "Alexandre Lacazette";
    pPointer->m_ppNames[24] = "Raheem Sterling";
    pPointer->m_ppNames[25] = "Sergio Aguero";
    pPointer->m_ppNames[26] = "Kevin De Bruyne";
    pPointer->m_ppNames[27] = "Robert Lewandowski";
    pPointer->m_ppNames[28] = "Manuel Neuer";
    pPointer->m_ppNames[29] = "Christian Pulisic";

    // Get a random string from the bunch we have.
    char * pRandomStr = GetRandomString(pPointer);

    // Allocate memory for the DisplayString structure.
    pPointer->m_pDisplayString = DS_Init(pRandomStr);

    // Allocate memory for the GameParticipants structure.
    pPointer->m_pGameParticipants = GP_Init(pRandomStr);

    // Return the pointer to be assigned.
    return pPointer;
}

// Function makes sure to handle the event of if the current string was guessed.
static bool StringGuessCompleted(WorldPtr world)
{
    // Did a participant actually guess the footballer correctly?
    if(DS_GuessCompleted(world->m_pDisplayString))
    {
        // Reward the turn player with the points they scored by guessing the footballers name correctly.
        GP_AwardPoints(world->m_pGameParticipants, DS_GetPoints(world->m_pDisplayString));

        // Check if someone won the game here since they correctly guessed a string.
        if(GP_GameWinner(world->m_pGameParticipants, s_pointsToWin))
        {
            return true;
        }

        // If so, do full reset.
        DS_Reset(world->m_pDisplayString);

        // Assign a new string.
        DS_AssignString(world->m_pDisplayString, GetRandomString(world));

        // Flip participants here.
        GP_SwitchParticipants(world->m_pGameParticipants);

        // Only IF it's the cpu's turn, we set it up so it can do it's thing.
        GP_SetCpuData(world->m_pGameParticipants, DS_GetString(world->m_pDisplayString));
    }

    return false;
}

// Refresh the screen by clearing it, showing the hidden string and tries left.
static void RefreshScreen(WorldPtr world)
{
    // Clear screen.
    World_ClearScreen(world);

    // Display the string.
    DS_ShowHiddenString(world->m_pDisplayString);

    // Display how many tries left.
    DS_DisplayTriesLeft(world->m_pDisplayString);
}

// Check if there are any attempts left
static bool AttemptsLeft(WorldPtr world)
{
    // Check if we have no tries left for participant.
    if(!DS_CanParticipantContinue(world->m_pDisplayString))
    {
        // Display what the string was before we get a new one.
        printf("String was %s!\n", DS_GetString(world->m_pDisplayString));

        // If we hit 0, reset the system in display string. Then switch the participants.
        DS_Reset(world->m_pDisplayString);

        // Assign a new string.
        DS_AssignString(world->m_pDisplayString, GetRandomString(world));

        // Flip participants here.
        GP_SwitchParticipants(world->m_pGameParticipants);

        // Only IF it's the cpu's turn, we set it up so it can do it's thing.
        GP_SetCpuData(world->m_pGameParticipants, DS_GetString(world->m_pDisplayString));

        return true;
    }

    return false;
}

// Of course process input from either participant.
static bool ProcessInput(WorldPtr world)
{
    // Get input from the player or cpu.
    char result = GP_Update(world->m_pGameParticipants);

    // Check if that input was already entered. If so, return true.
    if(DS_CharAlreadyEntered(world->m_pDisplayString, result))
    {
        return true;
    }

    // Check to see if that entered key was valid regarding the current string.
    bool input = DS_CheckStringForMatchingChar(world->m_pDisplayString, result);

    // Cross check the input with the string. If false, turn participant didn't find a match, therefore decrement their try attempts. Or if good, increase the guesses.
    if(input)
    {
        GP_IncreaseCpuCurrentGuesses(world->m_pGameParticipants);
    }

    else
    {
        DS_DecrementTriesLeft(world->m_pDisplayString);
    }

    return false;
}

void World_Update(WorldPtr world)
{
    // Run the game loop as long as neither participant has reached the score to win.
    while(true)
    {
        // Check if the string was guessed and break if it was.
        if(StringGuessCompleted(world))
        {
            break;
        }

        // Refresh the screen.
        RefreshScreen(world);

        // If they ran out of guesses, process that then continue.
        if(AttemptsLeft(world))
        {
            continue;
        }

        // Place player and cpu scores here.
        GP_DisplayPoints(world->m_pGameParticipants, s_pointsToWin);

        // Display the word points here.
        DS_DisplayPointsForName(world->m_pDisplayString);

        // Receive input, continue if input was already entered before.
        if(ProcessInput(world))
        {
            continue;
        }

        World_ClearScreen(world);

        // Reshow hidden string.
        DS_ShowHiddenString(world->m_pDisplayString);
    }
}

void World_ClearScreen(WorldPtr world)
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
    DS_Destroy(world->m_pDisplayString);
    GP_Destroy(world->m_pGameParticipants);

    // Be careful for any memory issues here!
    for(int i = 0; i < s_maxStrings; ++i)
    {
        free(world->m_ppNames[i]);
        world->m_ppNames[i] = NULL;
    }

    free(world->m_ppNames);
    world->m_ppNames = NULL;

    free(world);
    world = NULL;
}

#endif // WORLD_C_INCLUDED
