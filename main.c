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

    uint32_t imm=0;
    struct i_type i_inst;
    struct u_type u_inst;
    struct r_type r_inst;
    struct j_type j_inst;
    int32_t rs1_s;
    int32_t rs2_s;
    uint8_t shamt;
    switch(decode_get_opcode(inst)){
        case OP_IMM:
            printf("OP_IMM\n");
            decode_get_i_type(inst, &i_inst);
            imm = decode_get_i_imm(inst);
            shamt = get_bits(imm, 0, 4);
            rs1_s = (int32_t)cpu.reg[i_inst.rs1];
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
            pc += 4;
            break;
        case OP_LUI:
            printf("OP_LUI\n");
            decode_get_u_type(inst, &u_inst);
            imm = decode_get_u_imm(inst);
            printf("LUI: imm:%d rd:%d\n", imm, u_inst.rd);
            cpu.reg[u_inst.rd] = imm;
            pc += 4;
            break;
        case OP_AUIPC:
            printf("OP_AUIPC\n");
            decode_get_u_type(inst, &u_inst);
            imm = decode_get_u_imm(inst);
            printf("AUIPC: imm:%d rd:%d\n", imm, u_inst.rd);
            cpu.reg[u_inst.rd] = cpu.pc + imm;
            pc += 4;
            break;
        case OP_OP:
            printf("OP_OP\n");
            decode_get_r_type(inst, &r_inst);
            shamt = get_bits(cpu.reg[r_inst.rs2], 0, 4);
            if(r_inst.funct7 == 0b0000000){
                switch(r_inst.funct3){
                    case FUNCT3_ADD:
                        printf("ADD: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1] + cpu.reg[r_inst.rs2];
                        break;
                    case FUNCT3_SLT:
                        printf("SLT: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        rs1_s = (int32_t)cpu.reg[r_inst.rs1];
                        rs2_s = (int32_t)cpu.reg[r_inst.rs2];
                        if(rs1_s < rs2_s){
                            cpu.reg[r_inst.rd] = 1;
                        }else{
                            cpu.reg[r_inst.rd] = 0;
                        }
                        break;
                    case FUNCT3_SLTU:
                        printf("SLTU: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        if(cpu.reg[r_inst.rs1] < cpu.reg[r_inst.rs2]){
                            cpu.reg[r_inst.rd] = 1;
                        }else{
                            cpu.reg[r_inst.rd] = 1;
                        }
                        break;
                    case FUNCT3_AND:
                        printf("AND: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1]&cpu.reg[r_inst.rs2];
                        break;
                    case FUNCT3_OR:
                        printf("OR: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1]|cpu.reg[r_inst.rs2];
                        break;
                    case FUNCT3_XOR:
                        printf("XOR: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1]^cpu.reg[r_inst.rs2];
                        break;
                    case FUNCT3_SLL:
                        printf("SLL: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1] << shamt;
                        break;
                    case FUNCT3_SRL:
                        printf("SRL: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1] >> shamt;
                        break;
                    default:
                        printf("Not Implemented!\n");
                }
            }else if(r_inst.funct7 == 0b0100000){
                rs1_s = (int32_t)cpu.reg[r_inst.rs1];
                switch(r_inst.funct3){
                    case FUNCT3_SUB:
                        printf("SUB: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = cpu.reg[r_inst.rs1]-cpu.reg[r_inst.rs2];
                        break;
                    case FUNCT3_SRA:
                        printf("SRA: rs1:%d rs2:%d rd:%d\n", r_inst.rs1, r_inst.rs2, r_inst.rd);
                        cpu.reg[r_inst.rd] = rs1_s >> shamt;
                        break;
                    default:
                        printf("Not Implemented!\n");
                }
            }
            pc += 4;
            break;
        case OP_JAL:
            decode_get_j_type(inst, &j_inst);
            imm = decode_get_j_imm(inst);
            printf("JAL: imm:%d rd:%d\n", imm, j_inst.rd);
            cpu.reg[j_inst.rd] = pc+4;
            pc += imm;
            break;
        case OP_JALR:
            decode_get_i_type(inst, &i_inst);
            imm = decode_get_i_imm(inst);
            printf("JALR: imm:%d rs1:%d rd:%d\n", imm, i_inst.rs1, i_inst.rd);
            cpu.reg[i_inst.rd] = pc+4;
            pc += cpu.reg[i_inst.rs1] + imm;
            break;
        case OP_BRANCH:
            break;
        default:
            printf("Not Implemented!\n");
    }
}
