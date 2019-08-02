#ifndef INST_H
#define INST_H
#include <stdint.h>
struct r_type {
    uint8_t funct7 :6;
    uint8_t rs2 :5;
    uint8_t rs1 :5;
    uint8_t funct3 :3;
    uint8_t rd :5;
    uint8_t opcode :7;
};

struct i_type {
    uint16_t imm :12;
    uint8_t rs1 :5;
    uint8_t funct3 :3;
    uint8_t rd :5;
    uint8_t opcode :7;
};

struct s_type {
    uint16_t imm_u :7;
    uint8_t rs1 :5;
    uint8_t rs2 :5;
    uint8_t funct3 :3;
    uint8_t imm_l :5;
    uint8_t opcode :7;
};

struct u_type {
    uint32_t imm :20;
    uint8_t rd :5;
    uint8_t opcode :7;
};

enum inst_opcode {
    OP_IMM = 0b0010011,
    OP_LUI = 0b0110111,
    OP_AUIPC = 0b0010111,
    OP_OP = 0b0110011,
    OP_JAL = 0b1101111,
    OP_JALR = 0b1100111,
    OP_BRANCH = 0b1100011,
    OP_LOAD = 0b0000011,
    OP_STORE = 0b0100011,
    OP_MISC_MEM = 0b0001111,
    OP_SYSTEM = 0b1110011,
};

#endif
