#include "../../phase.h"
#include <stdio.h>
#include <assert.h>

#define LENGTH 10

int main (int argc, char *argv[]){

    int fase_id = 0, i = 0;
    phase new_phase = NULL;
    
    new_phase = phase_create(fase_id);
    
    for (i = 0; i < LENGTH; i++){
        phase_add(new_phase,(float)i);    
    }
        
    for (i = 0; i < 2*LENGTH; i++){
        printf("%f ", phase_next_value(new_phase));
    }
    
    new_phase = phase_destroy(new_phase);
    assert(new_phase != NULL);
         
    return 0;

}



