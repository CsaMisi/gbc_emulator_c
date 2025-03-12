#ifndef MEMORY_H
#define MEMORY_H

#include "../include/common.h"
#include "stdint.h"

#define MEMORY_MAX 0x10000

typedef struct MEMORY {
    BYTE MEM_MAIN[MEMORY_MAX];
    
    // Banked Memory Pointers
    BYTE *rom_bank_ptr;
    BYTE *wram_bank_ptr;
    BYTE *cartrige_ram_ptr;
    
    // Active Banks
    BYTE *current_rom_bank;
    BYTE *current_wram_bank;
    BYTE *current_vram_bank;
    
    BYTE vram_bank;      // 0 or 1 (Switch via 0xFF4F)
    BYTE wram_bank;      // 1-7 (Switch via 0xFF70, 0 is treated as 1)
    BYTE cartrige_ram_bank; // Active RAM bank (for MBC)
} MEMORY_T;

// Memory Macros
#define MEM_ROM_BANK(mem) ((mem)->rom_bank_ptr)
#define MEM_WRAM_BANK(mem) ((mem)->wram_bank_ptr)
#define MEM_CARTRIGE_RAM(mem) ((mem)->cartrige_ram_ptr)

//prototype functions
void mem_init(MEMORY_T *self);
BYTE MEM_READ_BYTE(MEMORY_T *self, WORD addr);
void MEM_WRITE(MEMORY_T *self, WORD addr, BYTE value);
WORD MEM_READ_WORD(MEMORY_T *self, WORD addr);
void MEM_WRITE_WORD(MEMORY_T *self, WORD addr, WORD value);

static inline void SET_VRAM_BANK(MEMORY_T *mem, BYTE bank) {
    mem->vram_bank = bank & 0x01; // Only 2 VRAM banks (0 or 1)
    mem->current_vram_bank = &mem->MEM_MAIN[VRAM_START + (mem->vram_bank * 0x2000)];
}

static inline void SET_WRAM_BANK(MEMORY_T *mem, BYTE bank) {
    mem->wram_bank = (bank == 0) ? 1 : (bank & 0x07); // WRAM 0 is treated as Bank 1
    mem->current_wram_bank = &mem->MEM_MAIN[0xD000 + ((mem->wram_bank - 1) * 0x1000)];
}

static inline void SET_CARTRIGE_RAM_BANK(MEMORY_T *mem, BYTE bank) {
    mem->cartrige_ram_bank = bank;
    mem->cartrige_ram_ptr = &mem->MEM_MAIN[EXRAM_START + (bank * 0x2000)];
}

#endif // MEMORY_H
