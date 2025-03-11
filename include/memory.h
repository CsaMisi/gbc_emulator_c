#ifndef MEMORY_H
#define MEMORY_H

#include "../include/common.h"
#include "stdint.h"

#define MEMORY_MAX 0x10000

typedef struct MEMORY{
    BYTE MEM_MAIN[MEMORY_MAX];
    BYTE *rom_bank_ptr;
    BYTE *vram_bank_ptr;
    BYTE *cartrige_ram_ptr; // if present
    BYTE *current_rom_bank;
    BYTE *current_vram_bank; 
    BYTE *current_ram_bank;
}MEMORY_T;

#define READ_BYTE(mem, addr) ({ \
    BYTE result; \
    if ((addr) >= 0xE000 && (addr) < 0xFE00) { \
        result = (mem)->memory[(addr) - 0x2000]; \
    } else { \
        result = (mem)->memory[addr]; \
    } \
    result; \
})



//Prototype Functions

#endif // MEMORY_H