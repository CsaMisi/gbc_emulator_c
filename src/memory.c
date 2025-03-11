#include "../include/memory.h"

BYTE MEM_READ_BYTE(MEMORY_T *self, WORD addr){
    if((addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) //echo disabled on gbc
    || (addr >= UNUSED_START && addr <= UNUSED_END)) 
        return 0xFF;
    else return self->MEM_MAIN[addr];
} 

void MEM_WRITE(MEMORY_T *self, WORD addr, BYTE value){
    if((addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) //echo disabled on gbc
    || (addr >= UNUSED_START && addr <= UNUSED_END))
        return;
    else self->MEM_MAIN[addr] = value;
}