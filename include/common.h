#ifndef COMMON
#define COMMON
#include "stdint.h"
#include <stdint.h>
#include "stdbool.h"

enum MemoryMap{
    ROM_START = 0x0000,
    ROM_END = 0x7FFF,
    VRAM_START = 0x8000,
    VRAM_END = 0x9FFF,
    EXRAM_START = 0xA000,  // Cartridge RAM
    EXRAM_END = 0xBFFF,
    WRAM_START = 0xC000,
    WRAM_END = 0xDFFF,
    ECHO_RAM_START = 0xE000,
    ECHO_RAM_END = 0xFDFF,
    OAM_START = 0xFE00,  // Object Attribute Memory (Sprite Table)
    OAM_END = 0xFE9F,
    UNUSED_START = 0xFEA0,  // Unused/Restricted Memory
    UNUSED_END = 0xFEFF,
    IO_REGS_START = 0xFF00,  // I/O Registers
    IO_REGS_END = 0xFF7F,
    HRAM_START = 0xFF80,  // High RAM
    HRAM_END = 0xFFFE,
    IE_REGISTER = 0xFFFF  // Interrupt Enable Register
};

enum IO_Ranges{
    JOYPAD_INP = 0xFF00,
    SER_TRANS_START = 0xFF01,
    SER_TRANS_END = 0xFF02,
    TD_START = 0xFF04,
    TD_END = 0xFF07,
    INTERRUPTS = 0xFF10,
    AUDIO_START = 0xFF10,
    AUDIO_END = 0xFF26,
    WAVE_START = 0xFF30,
    WAVE_END = 0xFF3F,
    LCD_START = 0xFF40,
    LCD_END = 0xFF4B,
    VRAM_BANK_SEL = 0xFF4F,
    DISABLE_BROM = 0xFF50, // set to non-zero to disable boot ROM
    VRAM_DMA_START = 0xFF51,
    VRAM_DMA_END = 0xFF55,
    BGOBJ_START = 0xFF68, // BG/OBJ Palettes
    BGOBJ_END = 0xFF6B,
    WRAM_BANK_SEL = 0xFF70
};

typedef uint8_t BYTE;
typedef int8_t SIGNED_BYTE;
//typedef uint16_t WORD;
//typedef int16_t SIGNED_WORD;
typedef union{
    uint16_t WORD;
    struct{
        BYTE low;
        BYTE high;
    };
}WORD;

typedef union{
    int16_t SIGNED_WORD;
    struct{
        BYTE low;
        BYTE high;
    };
}SIGNED_WORD;



static inline bool IsValidAddress(WORD addr){
    if ((addr.WORD >= ECHO_RAM_START && addr.WORD <= ECHO_RAM_END) ||
        (addr.WORD >= UNUSED_START && addr.WORD <= UNUSED_END)) {
        return false;
    }
    return true;
}

#endif 