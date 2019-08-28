#ifndef CPU_C_INCLUDED
#define CPU_C_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Cpu.h"
#include "CpuSmartStringGuess.h"

// Keep the points for the cpu and a pointer to the algorithm it needs to make educated guesses.
struct Cpu
{
    int m_points;
    CpuSmartGuessPtr m_pSmartGuess;
};

CpuPtr Cpu_Init()
{
    // Allocate memory for the structure.
    CpuPtr pCpu = malloc(sizeof * pCpu);

    // Check if null.
    if(!pCpu)
    {
        printf("Cpu null!\n");
        return NULL;
    }

    else
    {
        pCpu->m_points = 0;

        /** Initially set to NULL, we don't need to initialize it here because the current string to be guessed is needed for it to BE initialized. We don't know if the
        cpu is the one going first. Delay initialization until it's their turn. */
        pCpu->m_pSmartGuess = NULL;
    }

    // Return the cpu.
    return pCpu;
}

void Cpu_SetString(CpuPtr cpu, char * pString)
{
    // CSGP_Init is the function we use to initially get the pointer and therefore ready the algorithm.
    cpu->m_pSmartGuess = CSGP_Init(pString);
}

char Cpu_Update(CpuPtr cpu)
{
    // Update through cpu smart guess pointer.
    return CSGP_Update(cpu->m_pSmartGuess);
}

void Cpu_IncreasePoints(CpuPtr cpu, const int points)
{
    cpu->m_points += points;
}

int Cpu_GetPoints(CpuPtr cpu)
{
    return cpu->m_points;
}

void Cpu_IncreaseCpuCurrentGuesses(CpuPtr cpu)
{
    // Call the string guess function and increase the minimum needed to continue to the advanced part of the algorithm.
    CSGP_IncreaseCpuCurrentGuesses(cpu->m_pSmartGuess);
}

void Cpu_SetCpuData(CpuPtr cpu, char * pString)
{
    // The pointer was assigned null in the initialization function so check for that and initialize here if need be.
    if(cpu->m_pSmartGuess == NULL)
    {
        cpu->m_pSmartGuess = CSGP_Init(pString);
        return;
    }

    // If it's not null, go ahead and just set the data.
    CSGP_SetData(cpu->m_pSmartGuess, pString);
}

void Cpu_Destroy(CpuPtr cpu)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!cpu)
    {
        return;
    }

    CSGP_Destroy(cpu->m_pSmartGuess);

    free(cpu);
    cpu = NULL;
}

#endif // CPU_C_INCLUDED
