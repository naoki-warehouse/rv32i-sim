#ifndef CPU_H
#define CPU_H

#define CPU_MEM_SIZE 1024

struct cpu {
    uint32_t reg[32];
    uint32_t pc;
    uint32_t mem[CPU_MEM_SIZE];
};

#endif
