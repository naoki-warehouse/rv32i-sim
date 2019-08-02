#include <stdint.h>
#include <stdio.h>

#include "utils.h"
#include "inst.h"



static uint8_t get_funct7(uint32_t inst){ return (uint8_t)get_bits(inst,25, 31); }
static uint8_t get_rs2(uint32_t inst){ return (uint8_t)get_bits(inst, 20, 24); }
static uint8_t get_rs1(uint32_t inst){ return (uint8_t)get_bits(inst, 15, 19); }
static uint8_t get_funct3(uint32_t inst){ return (uint8_t)get_bits(inst, 12, 14); }
static uint8_t get_rd(uint32_t inst){ return (uint8_t)get_bits(inst, 7, 11); }
static uint8_t get_opcode(uint32_t inst){ return (uint8_t)get_bits(inst, 0, 6); }
static uint16_t get_imm_11_0(uint32_t inst){ return (uint16_t)get_bits(inst, 20, 31); }
static uint8_t get_imm_11_5(uint32_t inst){ return (uint8_t)get_bits(inst, 25, 31); }
static uint8_t get_imm_4_0(uint32_t inst){ return (uint8_t)get_bits(inst, 7, 11); }
static uint32_t get_imm_31_12(uint32_t inst){ return (uint32_t)get_bits(inst, 12, 31); }

int decode_get_type(uint32_t inst){

}
uint8_t decode_get_opcode(uint32_t inst){
    return get_opcode(inst);
}

void decode_get_r_type(uint32_t inst, struct r_type *r){
}

void decode_get_i_type(uint32_t inst, struct i_type *i){
}

void decode_get_s_type(uint32_t inst, struct s_type *s){
}

void decode_get_u_type(uint32_t inst, struct u_type *u){
}
