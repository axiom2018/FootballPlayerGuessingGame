#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

/** Reasoning for this interface:

Use the abstract data type to create an interface for the cpu of the game so we can carry out certain operations on the cpu.


                                                                                Interface variables:

1) Reasoning for CpuPtr:

Standard part of the abstract data type in c is to have a typedef struct in the header file.


                                                                                Interface functions:

1) Reasoning for Cpu_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for Cpu_SetString:

This is the function called when the cpu is prepared to take it's first turn, string is provided for the algorithm.


3) Reasoning for Cpu_Update:

Allow the cpu to give us input regarding their guess to what letter(s) are in the footballers name.


4) Reasoning for Cpu_IncreasePoints:

Give cpu more points for guessing footballer correctly.


5) Reasoning for Cpu_GetPoints:

Return the cpu's points.


6) Reasoning for Cpu_IncreaseCpuCurrentGuesses:

We'll need this to proceed to the other part of the cpu algorithm. This function itself increases the current amount of correct guesses.


7) Reasoning for Cpu_SetCpuData:

Ready the algorithm for the cpu's turn.


8) Reasoning for Cpu_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

*/

typedef struct Cpu * CpuPtr;

CpuPtr Cpu_Init();
void Cpu_SetString(CpuPtr cpu, char * pString);
char Cpu_Update(CpuPtr cpu);
void Cpu_IncreasePoints(CpuPtr cpu, const int points);
int Cpu_GetPoints(CpuPtr cpu);
void Cpu_IncreaseCpuCurrentGuesses(CpuPtr cpu);
void Cpu_SetCpuData(CpuPtr cpu, char * pString);
void Cpu_Destroy(CpuPtr cpu);

#endif // CPU_H_INCLUDED
