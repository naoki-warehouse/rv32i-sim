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
    uint8_t rs1 :5;
    uint8_t funct3 :3;
    uint8_t rd :5;
    uint8_t opcode :7;
};

struct s_type {
    uint8_t rs1 :5;
    uint8_t rs2 :5;
    uint8_t funct3 :3;
    uint8_t opcode :7;
};

struct b_type {
    uint8_t rs2 :5;
    uint8_t rs1 :5;
    uint8_t funct3 :3;
    uint8_t opcode :7;
};

struct u_type {
    uint8_t rd :5;
    uint8_t opcode :7;
};

struct j_type {
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

enum funct3_opcode {
    FUNCT3_JALR = 0b000,
    FUNCT3_BEQ = 0b000,
    FUNCT3_BNE = 0b001,
    FUNCT3_BLT = 0b100,
    FUNCT3_BGE = 0b101,
    FUNCT3_BLTU = 0b110,
    FUNCT3_BGEU = 0b111,
    FUNCT3_LB = 0b000,
    FUNCT3_LH = 0b001,
    FUNCT3_LW = 0b010,
    FUNCT3_LBU = 0b100,
    FUNCT3_LHU = 0b101,
    FUNCT3_SB = 0b000,
    FUNCT3_SH = 0b001,
    FUNCT3_SW = 0b010,
    FUNCT3_ADDI = 0b000,
    FUNCT3_SLTI = 0b010,
    FUNCT3_SLTIU = 0b011,
    FUNCT3_XORI = 0b100,
    FUNCT3_ORI = 0b110,
    FUNCT3_ANDI = 0b111,
    FUNCT3_SLLI = 0b001,
    FUNCT3_SRI = 0b101,
    FUNCT3_ADD = 0b000,
    FUNCT3_SUB = 0b000,
    FUNCT3_SLL = 0b001,
    FUNCT3_SLT = 0b010,
    FUNCT3_SLTU = 0b011,
    FUNCT3_XOR = 0b100,
    FUNCT3_SRL = 0b101,
    FUNCT3_SRA = 0b101,
    FUNCT3_OR = 0b110,
    FUNCT3_AND = 0b111,
    FUNCT3_FENCE = 0b000,
    FUNCT3_ECALL = 0b000,
    FUNCT3_EBREAK = 0b000
};

enum funct7_opcode {
    FUNCT7_SLLI = 0b0000000,
    FUNCT7_SRLI = 0b0000000,
    FUNCT7_SRAI = 0b0100000,
    FUNCT7_ADD = 0b0000000,
    FUNCT7_SUB = 0b0100000,
    FUNCT7_SLL = 0b0000000,
    FUNCT7_SLT = 0b0000000,
    FUNCT7_SLTU = 0b0000000,
    FUNCT7_XOR = 0b0000000,
    FUNCT7_SRL = 0b0000000,
    FUNCT7_SRA = 0b0100000,
    FUNCT7_OR = 0b0000000,
    FUNCT7_AND = 0b0000000

};
#endif
