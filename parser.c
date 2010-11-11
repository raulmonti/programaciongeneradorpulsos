#include <stdio.h>
#include <assert.h>

#include "lexer.h"

#define SPACE   " \t"
#define NEWLINE "\n"
#define LPAR    "("
#define RPAR    ")"
#define EQL     "="

/* La notación: 
 * <token>+ : la ocurrencia de al menos una palabra <token> 
 * <token>* : 0 o mas ocurrencia de la palabra <token>
 */


/* DECLARACIÓN DE FASES: */

/* Leer: "begin <space>+ of <space>+ phases <space>* <newline>+" */
bool read_begin_of_phase(Lexer *l);

/* Leer: "ph<digit> <space>+ = <space>+ <digit> {<space>+ <digit>} <space>* <newline>+" */
bool read_phase(Lexer *l);

/* Leer: "end <space>+ of <space>+ phases <space>* <newline>+" */
bool read_end_of_phase(Lexer *l);
/** Redundacia entre éstas dos últimas funciones, mejorar **/




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
    
    if (result)    printf("begin of phases: Correcto\n");
    return result;
}

bool read_end_of_phase(Lexer *l){
#define END  "end"
#define OF     "of"
#define PHASES "phases"

    bool result = 1;
    
    consume_spaces(l);
    result = accept(l, END);
    if (!result){
        printf("Se esperaba <end>\n");
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
    
    if (result)    printf("end of phases: Correcto\n");    
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

    if (result)    printf("phases: Correcto\n");
    return result;
    
}



bool phase_declaration(Lexer *l){
	bool read_begin = 1;	
	bool read_phases = 1;
	bool read_end = 1;
	bool result = 1;
	
	read_begin = read_begin_of_phase(l);
	if (!read_begin){
		result = 0;
	}
	
	if (result){

		do{
			read_phases = read_phase(l);
		}while(read_phases == 1);
		
	}
	
	read_end = read_end_of_phase(l);
	
	result = read_begin && read_end;
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
  if (phase_declaration(l)){
  		printf("Correctamente sintactico\n");
  	}else{
  		printf("Incorrectamente sintactico\n");
  	}
  



  return 0;
}









