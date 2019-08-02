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

#endif
