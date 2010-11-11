#include <stdio.h>
#include <assert.h>

#include "lexer.h"

#define SPACE   " \t"
#define NEWLINE "\n"
#define LPAR    "("
#define RPAR    ")"
#define EQL     "="



/* Leer: "begin <space>+ of <space>+ phases <space>+ <newline>+" */
bool read_begin_of_phase(Lexer *l);

/* Leer: "ph<digit> <space>+ = <space>+ <digit> {<space>+ <digit>} <space>+ <newline>" */
bool read_phase(Lexer *l);





/* Funciones auxiliares */
bstring getsym(Lexer *l);

/* Devuelve '' si no es lo que esperas, de lo contrario algo no vacio */
bstring expect(Lexer *l, char* token);
bool consume_spaces(Lexer *l);
bool accept(Lexer *l, char* token);


/* Sintaxis un programa */
bool program(Lexer *l);
bool phase_declaration(Lexer *l);


/* Obtener el siguiente simbolo (palabra reservada) */
bstring getsym(Lexer *l){

  /* PRE */
  assert(l != NULL);
  
  lexer_skip_to(l, LOWER);
  lexer_next(l, LOWER);
  
  return lexer_item(l);

}


bstring expect(Lexer *l, char* token){
    bstring result = NULL;

    /* PRE */
    assert(l != NULL);
    assert(token != NULL);

    lexer_next(l, token);
    result = lexer_item(l);
    
    return result;

}


bool consume_spaces(Lexer *l){
    assert (l != NULL);
    lexer_skip(l, SPACE);
    return 1;
}


bool accept(Lexer *l, char* token){
    bool result = 0;
    bstring item = NULL;
    
    assert(l != NULL);
    lexer_next(l, token);
    item = lexer_item(l);    
    result = biseqcstr(item, token);
    bdestroy(item);
    
    return result;

}

bool read_begin_of_phase(Lexer *l){
#define BEGIN  "begin"
#define OF     "of"
#define PHASES "phases"

    bool result = 1;
    
    consume_spaces(l);
    result = accept(l, BEGIN);
    if (!result){
        printf("Se esperaba <begin>\n");
        result = 0;
    }
    
    if (result){
        consume_spaces(l);
        if (!accept(l, OF)){
            printf("Se esperaba <of>");
            result = 0;
        }
    }
    
    if (result){
        consume_spaces(l);
        if (!accept(l, PHASES)){
            printf("Se esperaba <phases>");
            result = 0;
        }
    }
    
    if (result){
        bstring newlines = NULL;
        consume_spaces(l);
        newlines = expect(l, NEWLINE);
        if (biseqcstr(newlines, "")){
        	printf("Se esperaba <newline>");
        	result = 0;
        }
        bdestroy(newlines);
    }
    
    return result;
}

bool read_phase(Lexer *l){
#define PH "ph"    
    
    bool result = 0;
    
    result = accept(l, PH);
    if (result){
        bstring pulse_id = NULL;
        
        pulse_id = expect(l, DIGIT);
        if (biseqcstr(pulse_id, "")){
            printf("Se esperaba <pulse_id>");
            result = 0;
        }
        printf("Se leyó el pulse_id: %s\n", pulse_id-> data);
        bdestroy(pulse_id);
    }


    if (result){
        consume_spaces(l);
        result = accept(l, EQL);
        if (!result){
            printf("Se esperaba < = >");
            result = 0;
        }
    }
    
    if (result){
        bstring pulse_value = NULL;
        bstring newlines = NULL;
        bool endline = false;
        
        do {
            consume_spaces(l);
            pulse_value = expect(l, DIGIT);
            if (biseqcstr(pulse_value, "")){
                printf("Se esperaba <pulse_value>");
                result = 0;
            }
            printf("Se leyó el pulse_value: %s\n", pulse_value-> data);
            bdestroy(pulse_value);
            consume_spaces(l);
            newlines = expect(l, NEWLINE);
            endline = !biseqcstr(newlines, "");
            bdestroy(newlines);
            if (result != 0 && endline){
            	/* Si leí al menos un pulsevalue y llegué al NEWLINE entonces es correcto */
            	result = 1;
            	break;
            }
        }while(result != 0);
    
    }

    return result;
    
}



bool phase_declaration(Lexer *l){
#define BEGIN  "begin"
#define OF     "of"
#define PHASES "phases"
    
    
    bool result = 1;
    bstring sym = NULL;
    
    /* PRE: */
    assert(l != NULL);
    
    
    /* Parseo de "begin of phases\n" MODULARIZAR!!! */
    sym = getsym(l);
    if (!biseqcstr(sym, BEGIN)){
        printf("Se esperaba <begin>\n");
        result = 0;
    }
    bdestroy(sym);
    
    if (result){
        bstring spaces = NULL;
        
        spaces = expect(l, SPACE);
        if (biseqcstr(spaces, "")){
            printf("Se esperaba <space>\n");
            result = 0;
        }
        bdestroy(spaces);
    }
    
    if (result){
        bstring of = NULL;
        
        of = getsym(l);
        if (!biseqcstr(of, OF)){
            printf("Se esperaba <of>\n");
            result = 0;
        }
        bdestroy(of);
    }
    
    if (result){
        bstring spaces = NULL;
        
        spaces = expect(l, SPACE);
        if (biseqcstr(spaces, "")){
            printf("Se esperaba <space>\n");
            result = 0;
        }
        bdestroy(spaces);
    }
    
    if (result){
        bstring phases = NULL;
        
        phases = getsym(l);
        if (!biseqcstr(phases, PHASES)){
            printf("Se esperaba <phases>\n");
            result = 0;
        }
        bdestroy(phases);
    }
    
    if (result){
        bstring spaces = NULL;
        
        spaces = expect(l, SPACE);
        /* Consumir espacios */
        bdestroy(spaces);
    }
    
    if (result){
        bstring newline = NULL;
        
        newline = expect(l, NEWLINE);
        if (!biseqcstr(newline, NEWLINE)){
            printf("Se esperaba <newline>\n");
            result = 0;
        }
        bdestroy(newline);
    }
    
    /* Parseo de phases: ph<digit> = <digit> {, <digit>} '\n' */
    sym = getsym(l);
    if (!biseqcstr(sym, "ph")){
        printf("Se esperaba <ph>\n");
        result = 0;
    }
    bdestroy(sym);
    
    if (result){
        bstring pulse_id = NULL;
        
        pulse_id = expect(l, DIGIT);
        if (biseqcstr(pulse_id, "")){
            printf("Se esperaba <pulse_id>\n");
            result = 0;
        }
        bdestroy(pulse_id);
        consume_spaces(l);
    }
    
    if (result){
        bstring eql = NULL;
        
        eql = expect(l, EQL);
        if (!biseqcstr(eql, EQL)){
            printf("Se esperaba < = >\n");
            result = 0;
        }
        bdestroy(eql);
        consume_spaces(l);
    }
    
    if (result){
        bstring phase = NULL;
        do {
            phase = expect(l, DIGIT);
            if (biseqcstr(phase, "")){
                printf("Se esperaba < phase_number >\n");
                result = 0;
            }
            printf("Fase leida: %s\n", phase->data);
            bdestroy(phase);
            consume_spaces(l);
        }while (result != 0 && !accept(l, "\n"));
        
    }
    
    
    
    
    
    return result;

}




int main(void){
  FILE *file = NULL;
  Lexer *l = NULL;
  
  
  file = fopen("sintaxis_ejemplo", "r");
  if (file == NULL){
    printf("El archivo no existe\n");
    return 1;
  }
  
  l = lexer_new(file);
  
  
  /* Inicio de parseo */
  if (read_begin_of_phase(l)){
    printf("Sintacticamente correcto BEGIN OF PHASES\n");
  }else{
    printf("Sintacticamente INcorrecto BEGIN OF PHASES\n");
  }
  
  if (read_phase(l)){
    printf("Sintacticamente correcto PHASES\n");
  }else{
    printf("Sintacticamente INcorrecto PHASES\n");
  }



  return 0;
}









