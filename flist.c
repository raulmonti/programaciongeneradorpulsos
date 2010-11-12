#include <stdio.h>
#include "flist.h"
#include <assert.h>
#include <stdlib.h>

typedef struct t_cell *cell;


struct t_cell{
    float value;
    cell next;
    cell prev;
};


struct t_flist{
    cell actual;
    cell head;
    cell tail;
    int size;
};


flist flist_create (void){
    flist fl = NULL;
    fl = calloc(1,sizeof(struct t_flist));
    assert(fl != NULL);

    fl->actual = NULL;
    fl->head = NULL;
    fl->size = 0;
   
    return fl;
}


flist flist_destroy (flist fl){

    cell aux = NULL;
    
    assert(fl != NULL);
   
    aux = fl->tail->prev;
    
    while(aux != NULL){
        free(aux->next);
        aux = aux->prev;
    }
    
    free(fl->head);
    free(fl);
    fl = NULL;
    
    return fl;
}


void flist_add (flist fl, float f){
 
    cell c = NULL, aux = NULL;
    
    c = calloc(1, sizeof(struct t_cell));
    c->value = f;
    c->next = NULL;
    
    aux = fl->actual;
    if (aux != NULL){
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = c;
    }else{
        fl->actual = c;
        fl->head = c;
    }
    
    c->prev = aux;
    fl->tail = c;
    fl->size++;
}
 
        
   

float flist_next (flist fl){
    
    float result = 0;
    
    assert(fl != NULL);
    assert(fl->size > 0);
    
    result = fl->actual->value;
    
    fl->actual = fl->actual->next;
    if(fl->actual == NULL)
        fl->actual = fl->head;
        
    return result;
}






