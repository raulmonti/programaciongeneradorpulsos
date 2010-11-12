#include "flist.h"
#include <stdio.h>
#include <assert.h>

int main (void){

    int i = 0;
    flist fl = NULL;
    
    fl = flist_create();
    
    for (i = 0; i < 4; i++){
    
        flist_add(fl,(float)i);
        
    }
    
    
    for (i = 0; i < 20; i++){
    
        printf(">> %f\n",flist_next(fl));
        
    }
    
    flist_destroy(fl);

    return 0;
}


