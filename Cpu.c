#ifndef CPU_C_INCLUDED
#define CPU_C_INCLUDED
#include "Cpu.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc and free.

struct Cpu
{
    int m_score;
    // Pointer to type of control system here for future use.
};

CpuPtr Cpu_Init()
{
    // Allocate memory for the structure.
    CpuPtr pPointer = malloc(sizeof * pPointer);

    // Check if null.
    if(!pPointer)
    {
        printf("Cpu null!\n");
        return NULL;
    }

    // Return the cpu.
    return pPointer;
}

void Cpu_Update(CpuPtr cpu)
{

}

void Cpu_Destroy(CpuPtr cpu)
{
    // Can't free/delete a pointer that's already null, check for that, return if that's the case.
    if(!cpu)
    {
        return;
    }

    // Delete.
    printf("Cleaning the cpu!\n");
    free(cpu);
}

#endif // CPU_C_INCLUDED
