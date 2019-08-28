#ifndef CPUINPUT_C_INCLUDED
#define CPUINPUT_C_INCLUDED
#include "CpuInput.h"
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define TIMER_DEFAULT 90000000 // A somewhat arbitrary number for the cpu to slow down while it decides otherwise it'll go lightning speed.

// 2 static variables for getting cpu input. Then 2 integers to get the minimum and max lowercase values on the ascii table.
static int s_preTimer = TIMER_DEFAULT;
static int s_postTimer = TIMER_DEFAULT;
static int s_minChar = 97;
static int s_maxChar = 122;

/// eliminate this ALTOGETHER and just smart csgp use the vowels at the beginning. Much easier to be honest.

char GetCpuInput()
{
    // Print message indicating cpu is thinking.
    printf("Cpu deciding what letter to choose...\n");

    // Ready the variable to return outside of loop below.
    char c = '/';

    // A small timer to give the cpu time.
    while(s_preTimer != 0)
    {
        --s_preTimer;
    }

    // Decide what the cpu will choose regarding a character.
    c = (char)(rand() % (s_maxChar - s_minChar + 1)) + s_minChar;

    while(s_postTimer != 0)
    {
        --s_postTimer;
    }

    // Reset the timers.
    s_preTimer = TIMER_DEFAULT;
    s_postTimer = TIMER_DEFAULT;

    // Return the character.
    return c;
}

#endif // CPUINPUT_C_INCLUDED
