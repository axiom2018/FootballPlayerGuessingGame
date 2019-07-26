#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

/* Reasoning for this interface:

Use the abstract data type to create an interface for the cpu of the game so we can carry out certain operations on the cpu.


                                                                                Interface variables:

1) Reasoning for CpuPtr:

Standard part of the abstract data type in c is to have a typedef struct in the header file.


                                                                                Interface functions:

1) Reasoning for Cpu_Init:

Standard part of the abstract data type in c is to have a function to initialize the pointer.


2) Reasoning for Cpu_Update:

Allow the cpu to give us input regarding their guess to what letter(s) are in the footballers name.


3) Reasoning for Cpu_Destroy:

Standard part of the abstract data type in c is to have a function to destroy the pointer to prevent memory leakage.

 */

typedef struct Cpu * CpuPtr;

CpuPtr Cpu_Init();
void Cpu_Update(CpuPtr cpu);
void Cpu_Destroy(CpuPtr cpu);

#endif // CPU_H_INCLUDED
