#include "../include/cpu.h"
#include <stdint.h>

void cpu_init(CPU_T *self){
    self->AF.WORD = 0x01B0;
    self->BC.WORD = 0x0013;
    self->DE.WORD = 0x00D8;
    self->HL.WORD = 0x014D;
    self->SP.WORD = 0xFFFE;
    self->PC.WORD = 0x0100;  // Program starts at 0x0100
    
    self->IME = 1;      // Interrupts enabled
    self->halted = 0;
    self->stopped = 0;
    self->cycles_left = 0;
}

void cpu_step(CPU_T *self){
    
}