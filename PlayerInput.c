#ifndef PLAYERINPUT_C_INCLUDED
#define PLAYERINPUT_C_INCLUDED
#include "PlayerInput.h"
#include <stdio.h>
#include <stdbool.h>

//char GetPlayerInput()
//{
//    // Set up the character we'll use to return.
//    char c = '/';
//
//    // Loop until proper input is received.
//    while(true)
//    {
//        // Prompt for input.
//        printf("(Player) Enter input: \n");
//
//        // Collect input.
//        c = getchar();
//
//        // Check for a-z or A-Z.
//        if((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
//        {
//            printf("Proper character entered, it was: %c\n", c);
//
//            // Have to flush the newline character.
//            fflush(stdin);
//
//            return c;
//        }
//
//        else
//        {
//            printf("Bad input! Reenter!\n");
//
//            // Have to flush the newline character.
//            fflush(stdin);
//        }
//    }
//
//    return c;
//}

#endif // PLAYERINPUT_C_INCLUDED
