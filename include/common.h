#ifndef COMMON
#define COMMON
#include "stdint.h"


// Memory Map
#define ROM_START       0x0000
#define ROM_END         0x7FFF
#define VRAM_START      0x8000
#define VRAM_END        0x9FFF
#define EXRAM_START     0xA000  // Cartridge RAM
#define EXRAM_END       0xBFFF
#define WRAM_START      0xC000 
#define WRAM_END        0xDFFF
#define ECHO_RAM_START  0xE000
#define ECHO_RAM_END    0xFDFF
#define OAM_START       0xFE00  // Object Attribute Memory (Sprite Table)
#define OAM_END         0xFE9F
#define UNUSED_START    0xFEA0  // Unused/Restricted Memory
#define UNUSED_END      0xFEFF
#define IO_REGS_START   0xFF00  // I/O Registers
#define IO_REGS_END     0xFF7F
#define HRAM_START      0xFF80  // High RAM
#define HRAM_END        0xFFFE
#define IE_REGISTER     0xFFFF  // Interrupt Enable Register

// I/O ranges
#define JOYPAD_INP      0xFF00
#define SER_TRANS_START 0xFF01
#define SER_TRANS_END   0xFF02
#define TD_START        0xFF04
#define TD_END          0xFF07
#define INTERRUPTS      0xFF10
#define AUDIO_START     0xFF10
#define AUDIO_END       0xFF26
#define WAVE_START      0xFF30
#define WAVE_END        0xFF3F
#define LCD_START       0xFF40
#define LCD_END         0xFF4B
#define VRAM_BANK_SEl   0xFF4F
#define DISABLE_BROM    0xFF50 // set to non-zero to disable boot ROM
#define VRAM_DMA_START  0xFF51
#define VRAM_DMA_END    0xFF55
#define BGOBJ_START     0xFF68 // BG/OBJ Palettes
#define BGOBJ_END       0xFF6B
#define WRAM_BANK_SEL   0xFF70


typedef uint8_t BYTE;
typedef int8_t SIGNED_BYTE;
typedef uint16_t WORD;
typedef int16_t SIGNED_WORD;

#endif 