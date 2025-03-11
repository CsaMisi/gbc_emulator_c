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

void mem_init(struct MEMORY *self);

static BYTE MEM_READ_BYTE(MEMORY_T *self, WORD addr) {
    // Echo RAM is ignored on GBC
    if ((addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) ||
        (addr >= UNUSED_START && addr <= UNUSED_END)) {
        return 0xFF;
    }

    if (addr >= VRAM_START && addr <= VRAM_END) {
        return self->current_vram_bank[addr - VRAM_START];
    }

    if (addr >= WRAM_START && addr <= 0xCFFF) {
        return self->MEM_MAIN[addr];
    }
    if (addr >= 0xD000 && addr <= 0xDFFF) {
        return self->current_wram_bank[addr - 0xD000]; // Banked WRAM
    }

    return self->MEM_MAIN[addr]; // Default
}

static void MEM_WRITE(MEMORY_T *self, WORD addr, BYTE value) {
    // Ignore writes to restricted memory
    if ((addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) ||
        (addr >= UNUSED_START && addr <= UNUSED_END)) {
        return;
    }

    // VRAM Banking
    if (addr >= VRAM_START && addr <= VRAM_END) {
        self->current_vram_bank[addr - VRAM_START] = value;
        return;
    }

    // WRAM Banking
    if (addr >= WRAM_START && addr <= 0xCFFF) {
        self->MEM_MAIN[addr] = value; // Always WRAM Bank 0
        return;
    }
    if (addr >= 0xD000 && addr <= 0xDFFF) {
        self->current_wram_bank[addr - 0xD000] = value; // Banked WRAM
        return;
    }

    self->MEM_MAIN[addr] = value;
}

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
