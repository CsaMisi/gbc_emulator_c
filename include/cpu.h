#ifndef CPU_H
#define CPU_H

#include "./common.h"

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

//Prototype Functions
void cpu_init(struct CPU *self);
void cpu_step(struct CPU *self);
void cpu_interrupt(struct CPU *self, BYTE interrupt_flag);

#endif //CPU_H