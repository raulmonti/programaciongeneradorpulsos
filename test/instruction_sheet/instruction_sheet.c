#include "instruction_sheet.h"
#include <stdlib.h>
#include <stdio.h>

struct inst_sheet_s {
    GList* instruction_list;
    GList* phase_list;
};

instruction_sheet instruction_sheet_create(void){
    instruction_sheet inst_sheet = calloc(1, sizeof(struct inst_sheet_s));
    inst_sheet->instruction_list = g_list_alloc();
    inst_sheet->phase_list = g_list_alloc();

    return inst_sheet;

}

instruction_sheet instruction_sheet_destroy(instruction_sheet inst_sheet){

    if (inst_sheet != NULL){
    
        while (g_list_length(inst_sheet->instruction_list) != 0){
             inst_sheet->instruction_list = instruction_destroy(g_list_nth_data(inst_sheet->instruction_list, 0));
        }

        while (g_list_length(inst_sheet->phase_list) != 0){
             inst_sheet->instruction_list = phase_destroy(g_list_nth_data(inst_sheet->instruction_list, 0));
        }

        free(inst_sheet);
        inst_sheet = NULL;
    }

    return inst_sheet;
    
}

void instruction_sheet_add_phase(instruction_sheet inst_sheet, phase ph){
    assert(inst_sheet != NULL);
    
    inst_sheet->g_list_append(phase_list, ph);
}

void instruction_sheet_add_instruction(instruction_sheet inst_sheet, instruction inst){
    assert(inst_sheet != NULL);

    inst_sheet->g_list_append(inst_sheet, inst);
}

void instruction_print(instruction_sheet inst_sheet){

    if(inst_sheet != NULL){    

        printf("Instruction Sheet\n");
        int i = 0;

        while(i<g_list_length(inst_sheet->instruction_list)){
            instruction_print(g_list_nth_data(inst_sheet->instruction_list, i));
        }

        i = 0;

        while(i<g_list_length(inst_sheet->phase_list)){
            phase_print(g_list_nth_data(inst_sheet->phase_list, i));
        }
    }

}
