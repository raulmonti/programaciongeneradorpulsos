#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum inst_type {LOOP, ACQUIERE, PULSE, DELAY} Instruction_Type;
typedef struct instruction_s *Instruction;

/****
    *Requiere:
    *Modifica:
    *Retorna:
*****/
Instruction instruction_create(unsigned int id, Instruction_Type t, unsigned int p);

/****
    *Requiere:
    *Modifica:
    *Retorna:
*****/

Instruction instruction_destroy(Instruction inst);

/****
    *Requiere:
    *Modifica:
    *Retorna:
*****/

void instruction_set_duration(Instruction inst, unsigned int d);

/****
    *Requiere:
    *Modifica:
    *Retorna:
*****/

void instruction_print(Instruction inst);

#endif
