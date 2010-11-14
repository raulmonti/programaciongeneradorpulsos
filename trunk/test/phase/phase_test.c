#include "phase.h"
#include <stdio.h>
#include <assert.h>

#define LENGTH 10

int main (int argc, char *argv[]){

    int fase_id = 7, i = 0;
    phase new_phase = NULL;
    
    new_phase = phase_create(fase_id);
    
    for (i = 0; i < LENGTH; i++){
        phase_add(new_phase,(float)i);    
    }

    printf("Se imprime 2 veces la lista de fases de id %i \n", phase_id(new_phase));
    phase_print(new_phase,2);
        
    new_phase = phase_destroy(new_phase);
    assert(new_phase == NULL);
         
    return 0;

}



