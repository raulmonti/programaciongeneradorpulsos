#include "flist.h"
#include <stdio.h>
#include <assert.h>

int main (void){

    int i = 0;
    flist fl = NULL;
    
    fl = flist_create();
    
    for (i = 0; i < 10; i++){
    
        flist_add(fl,(float)i);
        
    }
    
    printf("Longitud de la lista: %i\n", flist_length(fl));
    printf("Recorremos 2 veces la lista:\n");
    
    flist_print(fl,2);
    
    flist_destroy(fl);

    return 0;
}


