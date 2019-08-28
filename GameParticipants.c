#ifndef GAMEPARTICIPANTS_C_INCLUDED
#define GAMEPARTICIPANTS_C_INCLUDED
#include "GameParticipants.h"
#include "Player.h"
#include "Cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct GameParticipants
{
    // The player first class abstract data type.
    PlayerPtr m_pPlayer;

    // The cpu first class abstract data type.
    CpuPtr m_pCpu;

    // Number to indicate turn control.
    int m_turn;
};

// Decide the turn player based on the turn variable inside the structure.
static char GetInputFromCurrentTurnParticipant(GameParticipantsPtr gpp)
{
    // Use ternary operator (since participants are binary anyway) to get input.
    return (gpp->m_turn == 0) ? Player_Update(gpp->m_pPlayer) : Cpu_Update(gpp->m_pCpu);
}

GameParticipantsPtr GP_Init(char * pString)
{
    // Allocate memory for pointer.
    GameParticipantsPtr gp = malloc(sizeof * gp);

    // Check if not valid, return NULL if that's the case.
    if(!gp)
    {
        return NULL;
    }

    /// The turn variable is used to hold whoever's turn it currently is. It's binary, player is 0, cpu is 1, so keep switching between the 2 to alternate turns.
    gp->m_turn = 1;
    // We'll randomly get a starting turn here.
    // gp->m_turn = (rand() % 2) + 0;

    // If not, proceed to rest of operations. Allocate memory for the Player structure.
    gp->m_pPlayer = Player_Init();

    // Allocate memory for the Cpu structure.
    gp->m_pCpu = Cpu_Init();

    // If the cpu goes first, set the string.
    if(gp->m_turn == 1)
    {
        GP_SetStringForCpu(gp, pString);
    }

    // Return the pointer.
    return gp;
}

void GP_SetStringForCpu(GameParticipantsPtr gpp, char * pString)
{
    // During initialization of GP interface, it's not necessary to initialize cpu with string because we don't know if it'll be taking it's turn anyway.
    Cpu_SetString(gpp->m_pCpu, pString);
}

char GP_Update(GameParticipantsPtr gpp)
{
    // Easily return which competitor or participant has their turn with following function.
    return GetInputFromCurrentTurnParticipant(gpp);
}

// Simply switch the turn variable to 0 to indicate the player turn.
static void ChangeToPlayerTurn(GameParticipantsPtr gpp)
{
    gpp->m_turn = 0;
}

// Simply switch the turn variable to 1 to indicate the cpu turn.
static void ChangeToCpuTurn(GameParticipantsPtr gpp)
{
    gpp->m_turn = 1;
}

void GP_SwitchParticipants(GameParticipantsPtr gpp)
{
    // Use ternary operator (since participants are binary anyway) to get input.
    (gpp->m_turn == 0) ? ChangeToCpuTurn(gpp) : ChangeToPlayerTurn(gpp);
}

void GP_AwardPoints(GameParticipantsPtr gpp, const int points)
{
    // Use ternary operator (since participants are binary anyway) to award points.
    (gpp->m_turn == 0) ? Player_IncreasePoints(gpp->m_pPlayer, points) : Cpu_IncreasePoints(gpp->m_pCpu, points);
}

int GP_GameWinner(GameParticipantsPtr gpp, const int pointsRequiredToWin)
{
    // Check if either participant has reached the required points then exit the game.
    int plyrPoints = Player_GetPoints(gpp->m_pPlayer);
    int cpuPoints = Cpu_GetPoints(gpp->m_pCpu);

    // If statement check.
    if(plyrPoints >= pointsRequiredToWin)
    {
        printf("Player you have won the game with %d points! You are the football master!\n", plyrPoints);
        return true;
    }

    else if(cpuPoints >= pointsRequiredToWin)
    {
        printf("Cpu has won the game with %d points! The computer is football master!\n", cpuPoints);
        return true;
    }

    return false;
}

void GP_DisplayPoints(GameParticipantsPtr gpp, const int pointsToWin)
{
    // Display the points needed to win.
    printf("\n\n~~~~~ Points needed to win the match: %d ~~~~~\n", pointsToWin);

    // Display player and cpu points.
    printf("\n||||| Player points: %d ||||| \n", Player_GetPoints(gpp->m_pPlayer));
    printf("||||| Cpu points: %d ||||| \n", Cpu_GetPoints(gpp->m_pCpu));
}

void GP_IncreaseCpuCurrentGuesses(GameParticipantsPtr gpp)
{
    // This is only required of our Cpu because of the algorithm it uses to guess, so make sure the cpu is taking it's turn.
    if(gpp->m_turn == 1)
    {
        Cpu_IncreaseCpuCurrentGuesses(gpp->m_pCpu);
    }
}

// In order for the cpu to have their turn, it needs data set up. Do that here.
void GP_SetCpuData(GameParticipantsPtr gpp, char * pString)
{
    // This is only required of our Cpu because of the algorithm it uses to guess, so make sure the cpu is taking it's turn.
    if(gpp->m_turn == 1)
    {
        Cpu_SetCpuData(gpp->m_pCpu, pString);
    }
}

void GP_Destroy(GameParticipantsPtr gpp)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!gpp)
    {
        return;
    }

    Cpu_Destroy(gpp->m_pCpu);
    Player_Destroy(gpp->m_pPlayer);

    free(gpp);
    gpp = NULL;
}

#endif // GAMEPARTICIPANTS_C_INCLUDED
