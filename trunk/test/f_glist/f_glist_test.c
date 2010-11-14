#include "f_glist.h"
#include <stdio.h>
#include <assert.h>

int main (void){

    int i = 0;
    f_glist fl = NULL;
    
    fl = f_glist_create();
    
    for (i = 0; i < 10; i++){
    
        f_glist_add(fl,(float)i);
        
    }
    
    printf("Longitud de la lista: %i\n", f_glist_length(fl));
    printf("Recorremos 2 veces la lista:\n");
    
    f_glist_print(fl,2);
    
    f_glist_destroy(fl);

    return 0;
}


