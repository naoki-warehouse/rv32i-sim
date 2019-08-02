#include <stdint.h>
#include <stdio.h>
#include "inst.h"
#include "decode.h"

void print_bin(uint32_t v, int bit_len) {
    for(int i=bit_len;i>0;i--){
       printf("%d", (v&(1<<(i-1)))>>(i-1));
    }
}

int main(){
    uint32_t inst = 0xfff08013;

    switch(decode_get_opcode(inst)){
        case OP_IMM:
            printf("OP_IMM\n");
            int32_t imm = (int32_t)decode_get_i_imm(inst);
            struct i_type i_inst;
            decode_get_i_type(inst, &i_inst);
            switch(i_inst.funct3){
                case FUNCT3_ADDI:
                    printf("ADDI: imm:%d rs1:%d, rd:%d\n", imm, i_inst.rs1, i_inst.rd);
                    break;
                default:
                    printf("Not Implemented!\n");
            }
            break;
        default:
            printf("Not Implemented!\n");
    }
}
