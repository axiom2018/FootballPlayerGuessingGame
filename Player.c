#ifndef PLAYER_C_INCLUDED
#define PLAYER_C_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include <stdbool.h>

// 2 static variables for the lowercase characters in integer form.
static const int s_lowerBegin = 97;
static const int s_lowerEnd = 122;

// 2 static variables for the uppercase character in integer form.
static const int s_upperBegin = 65;
static const int s_upperEnd = 90;

// Hold the structure for the players points.
struct Player
{
    int m_points;
};

static char GetPlayerInput(PlayerPtr player)
{
    // Set up the character we'll use to return.
    char c = '/';

    // Loop until proper input is received.
    while(true)
    {
        // Prompt for input.
        printf("(Player) Enter input: \n");

        // Collect input.
        c = getchar();

        // Check for a-z or A-Z.
        if((c >= s_lowerBegin && c <= s_lowerEnd) || (c >= s_upperBegin && c <= s_upperEnd))
        {
            // Have to flush the newline character.
            fflush(stdin);

            return c;
        }

        else
        {
            // Demand the player input some valid input because their current input was stupid.
            printf("Bad input! Reenter!\n");

            // Have to flush the newline character.
            fflush(stdin);
        }
    }

    // Return the character.
    return c;
}

PlayerPtr Player_Init()
{
    // Allocate memory for the structure.
    PlayerPtr pPlayer = malloc(sizeof * pPlayer);

    // Check if null.
    if(!pPlayer)
    {
        printf("Player null!\n");
        return NULL;
    }

    else
    {
        // Set points to 0 and choose strategy.
        pPlayer->m_points = 0;
    }

    // Return the player.
    return pPlayer;
}

char Player_Update(PlayerPtr player)
{
    // Just get the player input.
    return GetPlayerInput(player);
}

void Player_IncreasePoints(PlayerPtr player, const int points)
{
    // Update the points and display.
    player->m_points += points;
    printf("Player now has %d points!\n", player->m_points);
}

int Player_GetPoints(PlayerPtr player)
{
    return player->m_points;
}

void Player_Destroy(PlayerPtr player)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!player)
    {
        return;
    }

    // Free all pointers and set to NULL.
    free(player);
    player = NULL;
}

#endif // PLAYER_C_INCLUDED
