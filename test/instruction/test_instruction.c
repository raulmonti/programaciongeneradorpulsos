#include <stdio.h>
#include "instruction.h"

int main(int argc, char *argv[]){
    Instruction inst = instruction_create(5, LOOP, 12);
    instruction_set_duration(inst, 18);
    instruction_print(inst);
    inst = instruction_destroy(inst);
    
    return 0;
}

