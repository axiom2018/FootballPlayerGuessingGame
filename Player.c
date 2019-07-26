#ifndef PLAYER_C_INCLUDED
#define PLAYER_C_INCLUDED
#include <stdio.h> // printf.
#include <stdlib.h> // malloc and free.
#include "Player.h"

struct Player
{
    int m_score;
    // Pointer to type of control system here for future use.
};

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

    // Return the player.
    return pPlayer;
}

void Player_Update(PlayerPtr player)
{

}

void Player_Destroy(PlayerPtr player)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!player)
    {
        return;
    }

    // Delete.
    printf("Cleaning the player.\n");
    free(player);
}

#endif // PLAYER_C_INCLUDED
