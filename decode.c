#include <stdint.h>
#include <stdio.h>

#include "inst.h"


static uint8_t get_funct7(uint32_t inst){ return (inst>>25); }
static uint8_t get_rs2(uint32_t inst){ return (inst>>20)&0b11111; }
static uint8_t get_rs1(uint32_t inst){ return (inst>>15)&0b11111; }
static uint8_t get_funct3(uint32_t inst){ return (inst>>12)&0b111; }
static uint8_t get_rd(uint32_t inst){ return (inst>>7)&0b11111; }
static uint8_t get_opcode(uint32_t inst){ return inst&0b1111111; }
static uint16_t get_imm_11_0(uint32_t inst){ return inst>>20; }
static uint8_t get_imm_11_5(uint32_t inst){ return inst>>25; }
static uint8_t get_imm_4_0(uint32_t inst){ return (inst>>7)&0b11111; }
static uint32_t get_imm_31_12(uint32_t inst){ return inst>>12; }

int decode_get_type(uint32_t inst){

}

void decode_get_r_type(uint32_t inst, struct r_type *r){
}

void decode_get_i_type(uint32_t inst, struct i_type *i){
}

void decode_get_s_type(uint32_t inst, struct s_type *s){
}

void decode_get_u_type(uint32_t inst, struct u_type *u){
}
