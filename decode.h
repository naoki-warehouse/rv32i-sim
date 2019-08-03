#ifndef DECODE_H
#define DECODE_H
uint8_t decode_get_opcode(uint32_t inst);
void decode_get_i_type(uint32_t inst, struct i_type *i);
void decode_get_u_type(uint32_t inst, struct u_type *u);
void decode_get_r_type(uint32_t inst, struct r_type *r);
void decode_get_j_type(uint32_t inst, struct j_type *j);
void decode_get_s_type(uint32_t inst, struct s_type *s);
void decode_get_b_type(uint32_t inst, struct b_type *b);
uint32_t decode_get_i_imm(uint32_t inst);
uint32_t decode_get_b_imm(uint32_t inst);
uint32_t decode_get_u_imm(uint32_t inst);
uint32_t decode_get_j_imm(uint32_t inst);
#endif
