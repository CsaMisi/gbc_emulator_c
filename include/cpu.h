#ifndef CPU_H
#define CPU_H

#include "../include/memory.h"
#include "./common.h"

//Flag bits
#define FLAG_Z (1<<7)
#define FLAG_N (1 << 6)
#define FLAG_H (1 << 5)
#define FLAG_C (1 << 4)


typedef struct CPU{
    /*16 bit registers
    union for access via 8 bit registers*/

    union{ //Accumulator and Flag
        struct{BYTE F, A;};
        WORD AF;
    };

    union{
        struct{BYTE C, B;};
        WORD BC;
    };
    
    union{
        struct{BYTE E, D;};
        WORD DE;
    };

    union{
        struct{BYTE H, L;};
        WORD HL;
    };

    WORD SP; //Stack Pointer
    WORD PC; //Program Counter

    BYTE IME;       // Interrupt Master Enable (1 = enabled, 0 = disabled)
    BYTE halted;    // HALT state
    BYTE stopped;   // STOP state
    BYTE current_opcode;  // Current instruction being executed
    BYTE cycles_left;  // Remaining cycles for current instruction

} CPU_T;

//Prototype FunctionsS
void cpu_init(struct CPU *self);
void cpu_step(struct CPU *self, MEMORY_T *mem);
void cpu_interrupt(struct CPU *self, BYTE interrupt_flag);

#define IS_ZEROFLAG_SET(cpu) ((cpu)->F & FLAG_Z)
#define ZEROFLAG_SET(cpu) ((cpu)->F |= FLAG_Z)
#define CLEAR_ZEROFLAG(cpu) ((cpu)->F &= ~FLAG_Z)

#define IS_CARRYFLAG_SET(cpu) ((cpu)->F & FLAG_C)
#define CARRYFLAG_SET(cpu) ((cpu)->F |= FLAG_C)
#define CLEAR_CARRYFLAG(cpu) ((cpu)->F &= ~FLAG_C)

#define IS_HALFCARRYFLAG_SET(cpu) ((cpu)->F & FLAG_H)
#define SET_HALFCARRYFLAG(cpu) ((cpu)->F |= FLAG_H)
#define CLEAR_HALFCARRYFLAG(cpu) ((cpu)->F &= ~FLAG_H)

#define IS_SUBTRACTFLAG_SET(cpu) ((cpu)->F & FLAG_N)
#define SET_SUBTRACTFLAG(cpu)    ((cpu)->F |= FLAG_N)
#define CLEAR_SUBTRACT_FLAG(cpu)  ((cpu)->F &= ~FLAG_N)

#endif //CPU_H