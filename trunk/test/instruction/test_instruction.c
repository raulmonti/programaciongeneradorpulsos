#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"

int main(int argc, char *argv[]){
    instruction inst = NULL;
    
    switch(atoi(argv[2])){
        case 0:{  inst = instruction_create(atoi(argv[1]), LOOP, atoi(argv[3]));
                    break;}
        case 1:{  inst = instruction_create(atoi(argv[1]), ACQUIERE, atoi(argv[3]));
                    break;}
        case 2:{  inst = instruction_create(atoi(argv[1]), PULSE, atoi(argv[3]));
                    break;}
        case 3:{  inst = instruction_create(atoi(argv[1]), DELAY, atoi(argv[3]));
                    break;} 
        default:{   printf("Error valor de type no valido\n");
                    printf("USAGE: ./test_instruction <id> <type> <param> <duration>\n");
                    printf("<type> = 0 | 1 | 2 | 3\n");
                    printf("LOOP = 0, ACQUIERE = 1, PULSE = 2, DELAY = 3\n");
                }
    }
    instruction_set_duration(inst, atoi(argv[4]));
    instruction_print(inst);
    inst = instruction_destroy(inst);
    
    return 0;
}

