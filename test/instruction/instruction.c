#include "instruction.h"
#include <stdlib.h>
#include <stdio.h>

struct instruction_s{
    uint id;
    Instruction_Type type;
    uint parameter;
    uint duration;
};

Instruction instruction_create(unsigned int id, Instruction_Type t, unsigned int p){
    Instruction inst = calloc(1, sizeof(struct instruction_s));
    inst->id = id;
    inst-> type = t;
    inst-> parameter = p;
    inst-> duration = 0;

    return inst;
}


Instruction instruction_destroy(Instruction inst){
    free(inst);
    inst = NULL;
    return inst;
}


void instruction_set_duration(Instruction inst, unsigned int d){
    inst->duration = d;
}

void instruction_print(Instruction inst){
    printf("Instruction:\n");
    printf("            id: %u\n", inst->id);
    printf("            type: %u\n", inst->type);
    printf("            parameter: %u\n", inst->parameter);
    printf("            duration: %u\n", inst->duration);
    printf("\n");    
}
