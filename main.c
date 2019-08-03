#include <stdint.h>
#include <stdio.h>
#include "inst.h"
#include "decode.h"
#include "cpu.h"
#include "utils.h"

void print_bin(uint32_t v, int bit_len) {
    for(int i=bit_len;i>0;i--){
       printf("%d", (v&(1<<(i-1)))>>(i-1));
    }
}

void init_cpu(struct cpu *cpu) {
    for(int i=0;i<32;i++){
        cpu->reg[i] = 0;
    }
    cpu->pc = 0;
    for(int i=0;i<CPU_MEM_SIZE;i++){
        cpu->mem[i] = 0;
    }
}

int main(){
    struct cpu cpu;
    init_cpu(&cpu);
    uint32_t inst = 0xfff08013;

    switch(decode_get_opcode(inst)){
        case OP_IMM:
            printf("OP_IMM\n");
            struct i_type i_inst;
            decode_get_i_type(inst, &i_inst);
            uint32_t imm = decode_get_i_imm(inst);
            uint8_t shamt = get_bits(imm, 0, 4);
            int32_t rs1_s = (int32_t)cpu.reg[i_inst.rs1];
            switch(i_inst.funct3){
                case FUNCT3_ADDI:
                    printf("ADDI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1] + imm;
                    break;
                case FUNCT3_SLTI:
                    printf("SLTI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    int32_t imm_s = (int32_t)imm;
                    if(rs1_s < imm_s) {
                        cpu.reg[i_inst.rd] = 1;
                    }else{
                        cpu.reg[i_inst.rd] = 0;
                    }
                    break;
                case FUNCT3_SLTIU:
                    printf("SLTIU: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    if(cpu.reg[i_inst.rs1] < imm){
                        cpu.reg[i_inst.rd] = 1;
                    }else{
                        cpu.reg[i_inst.rd] = 0;
                    }
                    break;
                case FUNCT3_ANDI:
                    printf("ANDI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1]&imm;
                    break;
                case FUNCT3_ORI:
                    printf("ORI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1]|imm;
                    break;
                case FUNCT3_XORI:
                    printf("XORI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1]^imm;
                    break;
                case FUNCT3_SLLI:
                    if(get_bits(imm, 5, 11) != 0b0000000) break;
                    printf("SLLI: shamt:%d rs1:%d, rd:%d\n", shamt, i_inst.rs1, i_inst.rd);
                    cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1]<<shamt;
                    break;
                case FUNCT3_SRL:
                    if(get_bits(imm, 5, 11) == 0b0000000){
                        //SRLI
                        printf("SRLI: shamt:%d rs1:%d, rd:%d\n", shamt, i_inst.rs1, i_inst.rd);
                        cpu.reg[i_inst.rd] = cpu.reg[i_inst.rs1]>>shamt;
                    }else if(get_bits(imm, 5, 11) != 0b0100000){
                        //SRAI
                        printf("SRAI: shamt:%d rs1:%d, rd:%d\n", shamt, i_inst.rs1, i_inst.rd);
                        cpu.reg[i_inst.rd] = rs1_s>>shamt;
                    }
                    break;
                default:
                    printf("Not Implemented!\n");
            }
            break;
        case OP_LUI:
            printf("OP_LUI\n");
            struct u_type u_inst;
            decode_get_u_type(inst, &u_inst);
            uint32_t imm = decode_get_u_imm(inst);
            cpu.reg[u_inst.rd] = imm;
        case OP_AUIPC:
            printf("OP_AUIPC\n");
            struct u_type u_inst;
            decode_get_u_type(inst, &u_inst);
            uint32_t imm = decode_get_u_imm(inst);
            cpu.reg[u_inst.rd] = cpu.pc + imm;
        default:
            printf("Not Implemented!\n");
    }
}
