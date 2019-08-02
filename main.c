#include <stdint.h>
#include <stdio.h>
#include "inst.h"

void print_bin(uint32_t v, int bit_len) {
    for(int i=bit_len;i>0;i--){
       printf("%d", (v&(1<<(i-1)))>>(i-1));
    }
}

int main(){
    uint32_t test = 0b1111110000011111000111110000000; 
    struct r_type *r = (struct r_type *)&test;

    print_bin(r->funct7, 6);
    printf("\n");
    print_bin(r->opcode, 6);
    printf("\n");
    printf("%X\n", r->funct7);
    printf("%X\n", r->opcode);
}
