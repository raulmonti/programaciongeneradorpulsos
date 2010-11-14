#ifndef FLIST_H
#define FLIST_H

/* MODULO DE LISTA CIRCULAR DE FLOTANTES */


typedef struct t_flist *flist;

flist flist_create (void);

flist flist_destroy (flist fl);

void flist_add (flist fl, float f); 

float flist_next (flist fl);

int flist_length (flist fl);

void flist_print (flist fl, int times);

#endif
