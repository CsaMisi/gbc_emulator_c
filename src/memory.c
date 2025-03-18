#include "../include/memory.h"
#include "../include/common.h"

void mem_init(MEMORY_T *self) {
    // Initialize memory to 0xFF (Game Boy behavior)
    for (int i = 0; i < MEMORY_MAX; i++) {
        self->MEM_MAIN[i] = 0xFF;
    }

    // Set initial memory bank pointers
    self->current_rom_bank = self->rom_bank_ptr;
    self->current_wram_bank = &self->MEM_MAIN[WRAM_START];
    self->current_vram_bank = &self->MEM_MAIN[VRAM_START];
}

// Byte Read
BYTE MEM_READ_BYTE(MEMORY_T *self, WORD addr) {
    if (!IsValidAddress(addr)) {
        return 0xFF;
    }

    if (addr.WORD >= VRAM_START && addr.WORD <= VRAM_END) {
        return self->current_vram_bank[addr.WORD - VRAM_START];
    }

    if (addr.WORD >= WRAM_START && addr.WORD <= 0xCFFF) {
        return self->MEM_MAIN[addr.WORD];
    }
    if (addr.WORD >= 0xD000 && addr.WORD <= 0xDFFF) {
        return self->current_wram_bank[addr.WORD - 0xD000];
    }

    return self->MEM_MAIN[addr.WORD];
}

// Byte Write
void MEM_WRITE(MEMORY_T *self, WORD addr, BYTE value) {
    if (!IsValidAddress(addr)) {
        return;
    }

    if (addr.WORD >= VRAM_START && addr.WORD <= VRAM_END) {
        self->current_vram_bank[addr.WORD - VRAM_START] = value;
        return;
    }

    if (addr.WORD >= WRAM_START && addr.WORD <= 0xCFFF) {
        self->MEM_MAIN[addr.WORD] = value;
        return;
    }
    if (addr.WORD >= 0xD000 && addr.WORD <= 0xDFFF) {
        self->current_wram_bank[addr.WORD - 0xD000] = value;
        return;
    }

    self->MEM_MAIN[addr.WORD] = value;
}

// Word Read
WORD MEM_READ_WORD(MEMORY_T *self, WORD addr) {
    if(!IsValidAddress(addr) || !IsValidAddress((WORD){.WORD = addr.WORD + 1}))
        return (WORD){ .WORD = 0xFFFF };
    WORD result;
    result.low = MEM_READ_BYTE(self, (WORD){.WORD = addr.WORD});
    result.high = MEM_READ_BYTE(self, (WORD){.WORD = addr.WORD + 1});
    return result;
}

// Word Write
void MEM_WRITE_WORD(MEMORY_T *self, WORD addr, WORD value) {
    if(!IsValidAddress(addr) || !IsValidAddress((WORD){.WORD = addr.WORD + 1}))
        return;

    MEM_WRITE(self, (WORD) {.WORD = addr.WORD}, value.low);
    MEM_WRITE(self, (WORD){.WORD = addr.WORD + 1}, value.high);
}

