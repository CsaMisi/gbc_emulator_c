#include <assert.h>
#include <stdio.h>
#include "../include/cpu.h"
#include "../include/memory.h"

void test_cpu_init() {
    CPU_T cpu;
    cpu_init(&cpu);
    
    assert(cpu.AF.WORD == 0);
    assert(cpu.BC.WORD == 0);
    assert(cpu.DE.WORD == 0);
    assert(cpu.HL.WORD == 0);
    assert(cpu.SP.WORD == 0);
    assert(cpu.PC.WORD == 0x100); 

    printf("test_cpu_init passed.\n");
}

void test_cpu_step() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    // Load simple program
    mem.MEM_MAIN[0x100] = 0x3E; // LD A, 0x42
    mem.MEM_MAIN[0x101] = 0x42;

    cpu_step(&cpu,&mem);

    assert(cpu.A == 0x42);
    assert(cpu.PC.WORD == 0x102);

    printf("test_cpu_step passed.\n");
}


void test_flag_operations() {
    CPU_T cpu;
    cpu.F = 0;
    
    ZEROFLAG_SET(&cpu);
    assert(IS_ZEROFLAG_SET(&cpu));

    CLEAR_ZEROFLAG(&cpu);
    assert(!IS_ZEROFLAG_SET(&cpu));

    printf("test_flag_operations passed.\n");
}

void test_cpu_interrupt() {
    CPU_T cpu;
    cpu_init(&cpu);

    // Mock an interrupt trigger
    cpu.IME = 1;  // Interrupts enabled
    cpu.PC.WORD = 0x150;
    cpu.SP.WORD = 0xFFFE;

    cpu_interrupt(&cpu, 0x0040);  // V-Blank Interrupt

    assert(cpu.IME == 0);  // IME should be disabled after servicing an interrupt
    assert(cpu.PC.WORD == 0x0040);  // Jump to interrupt vector
    assert(cpu.SP.WORD == 0xFFFC);  // Stack pointer should decrease

    printf("test_cpu_interrupt passed.\n");
}

void test_carry_flag_set() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0xFF;  // Max value
    mem.MEM_MAIN[0x100] = 0xC6; // ADD A, 0x01
    mem.MEM_MAIN[0x101] = 0x01;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x00);  // Overflow wraps around
    assert(IS_CARRYFLAG_SET(&cpu));  // Carry should be set

    printf("test_carry_flag_set passed.\n");
}

void test_carry_flag_clear() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0x10;
    mem.MEM_MAIN[0x100] = 0xC6; // ADD A, 0x05
    mem.MEM_MAIN[0x101] = 0x05;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x15);
    assert(!IS_CARRYFLAG_SET(&cpu)); // Carry should remain cleared

    printf("test_carry_flag_clear passed.\n");
}

void test_half_carry_set() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0x0F;  // Lower nibble full (00001111)
    mem.MEM_MAIN[0x100] = 0xC6; // ADD A, 0x01
    mem.MEM_MAIN[0x101] = 0x01;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x10);
    assert(IS_HALFCARRYFLAG_SET(&cpu));  // Half-Carry should be set

    printf("test_half_carry_set passed.\n");
}

void test_half_carry_clear() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0x10;
    mem.MEM_MAIN[0x100] = 0xC6; // ADD A, 0x02
    mem.MEM_MAIN[0x101] = 0x02;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x12);
    assert(!IS_HALFCARRYFLAG_SET(&cpu)); // Half-Carry should be cleared

    printf("test_half_carry_clear passed.\n");
}

void test_subtract_flag_set() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0x50;
    mem.MEM_MAIN[0x100] = 0xD6; // SUB A, 0x10
    mem.MEM_MAIN[0x101] = 0x10;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x40);
    assert(IS_SUBTRACTFLAG_SET(&cpu));  // Subtract flag should be set

    printf("test_subtract_flag_set passed.\n");
}

void test_subtract_flag_clear() {
    CPU_T cpu;
    MEMORY_T mem;
    cpu_init(&cpu);
    mem_init(&mem);

    cpu.A = 0x50;
    mem.MEM_MAIN[0x100] = 0xC6; // ADD A, 0x10
    mem.MEM_MAIN[0x101] = 0x10;

    cpu_step(&cpu, &mem);

    assert(cpu.A == 0x60);
    assert(!IS_SUBTRACTFLAG_SET(&cpu)); // Subtract flag should be cleared

    printf("test_subtract_flag_clear passed.\n");
}


int main() {
    test_cpu_step();
    test_cpu_interrupt();

    test_carry_flag_set();
    test_carry_flag_clear();

    test_half_carry_set();
    test_half_carry_clear();

    test_subtract_flag_set();
    test_subtract_flag_clear();

    printf("All CPU tests passed!\n");
    return 0;
}

