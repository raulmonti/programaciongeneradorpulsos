/* Este tipo representa una fase en el programa. 
 * Las fases pueden tomar diferentes valores 
 * correspondientes a los introducidos con la 
 * función 'phase_add'. (se extraen de manera circular).
 */

#include "phase.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <assert.h>

typedef struct t_tvalue{
    float value;
} *tvalue;


struct t_phase {
    unsigned int id;
    GList *values;
};



phase phase_create(unsigned int id){
 
    phase result = NULL;
    
    result = calloc(1,sizeof(struct t_phase));
    if (result != NULL){
        result->id = id;
    }
#ifdef DEBUG__ON    
    else{
        printf("Error, no se pudo reservar memoria para la phase %i.\n", id);
    }
#endif

    return result;
}



phase phase_destroy(phase p){

    assert(p != NULL);
    
    g_list_free(p->values);
    free(p);
    p = NULL;
    
    return p;
}




/* phase_add: agrega un valor de phase 'degree' a la 
 * lista de valores posibles para la fase p
 */
void phase_add(phase p, int degrees){
    
    int j = 0;
    void * value = NULL;
    assert(p != NULL);
    p->values = g_list_append(p->values, GINT_TO_POINTER(degrees)); 
    assert(p->values != NULL);
    value = g_list_first(p->values);
    j = GPOINTER_TO_INT(value);
    printf(">> %i\n", j);

}



/* phase_next_value: devuelve el siguiente valor de 
 * entre los asignados a la fase p
 */
int phase_next_value(phase p){

    void *next = NULL;
    
    assert(p!=NULL);
    
    next = g_list_next(p->values);
    
    if (next == NULL){
        next = (g_list_first(p->values));
    }
    
    return GPOINTER_TO_INT(next);  
}

