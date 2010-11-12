#include <stdio.h>
#include <assert.h>

#include "lexer.h"

#define SPACE   " \t"
#define NEWLINE "\n"
#define LPAR    "("
#define RPAR    ")"
#define EQL     "="

/* 
 * La notación: 
 * <token>+ : la ocurrencia de al menos una palabra <token> 
 * <token>* : 0 o mas ocurrencia de la palabra <token>
 *
 */



bool phase_declaration(Lexer *l);
bool program(Lexer *l);



/* HOJA DE PULSOS: 
 * 
 * Sintaxis:
 *
 */


/* Funciones auxiliares */
bstring getsym(Lexer *l);

/* Devuelve '' si no es lo que esperas, de lo contrario algo no vacio */
bstring expect(Lexer *l, char* token);
bool consume_spaces(Lexer *l);
bool accept(Lexer *l, char* token);


/* Sintaxis un programa */
bool program(Lexer *l);



/* Obtener el siguiente simbolo (palabra reservada) */
bstring getsym(Lexer *l){

  /* PRE */
  assert(l != NULL);
  
  lexer_skip_to(l, LOWER);
  lexer_next(l, LOWER "_");
  
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


bool phase_declaration(Lexer *l){
	bool result = 0;
	bstring sym = NULL;

	assert(l != NULL);
	
	result = 1;
	sym = getsym(l);
	
	if (!biseqcstr(sym, "declare_phases")){
		printf("Entre con el valor: %s\n", sym->data);
		result = 0;
	}
	
	if (result){
		bstring newlines = NULL;
		newlines = expect(l, "\n");
		if (biseqcstr(sym, "")){
			printf("Se esperaba <newline>\n");
			result = 0;			
		}
	}
	
	if (result){
		bstring ph_id = NULL;
		bstring equal = NULL;
		bstring ph_value = NULL;
		bstring newline = NULL;		
		
		
		sym = getsym(l);
		while(biseqcstr(sym, "ph")){
			ph_id = expect(l, DIGIT);
			if(biseqcstr(ph_id, "")){
				printf("Se esperaba <ph_id>\n");
				result = 0;			
			}
			
			consume_spaces(l);
			equal = expect(l, "=");
			if(!biseqcstr(equal, "=")){
				printf("Se esperaba <=>\n");
				result = 0;			
			}
			
			do{
				consume_spaces(l);
				ph_value = expect(l, DIGIT);
				if (biseqcstr(ph_value, "")){
					printf("Se esperaba <ph_value>\n");
					result = 0;								
				}
				printf("ph_value: %s\n", ph_value->data);
				consume_spaces(l);
				newline = expect(l, "\n");
				if (!biseqcstr(newline, "") && result != 0){
					break;
				}		
			}while(result);	
			sym = getsym(l);
		}
	}
	
	if (result){
		if (!biseqcstr(sym, "end_phases")){
			result = 0;
		}
	}
	
	return result;	
}

bool program(Lexer *l){
	bool result = 0;
	bstring sym = NULL;

	assert(l != NULL);

	result = 1;	
	sym = getsym(l);
	
	if (!biseqcstr(sym, "program")){
		printf("Se esperaba program\n");
		result = 0;
	}
	
	sym = getsym(l);
	while (result && !biseqcstr(sym, "end_program")) {
		if(result){
			
			if (biseqcstr(sym, "p")){
				bstring pulse_id = NULL;
			
				pulse_id = expect(l, DIGIT);
				if (biseqcstr(pulse_id, "")){
					printf("Se esperaba <pulse_id>");
					result = 0;
				}
				printf("Se leyó el pulse_id:%s\n", pulse_id->data);
			
				if(result){
					bstring lpar = NULL;
					lpar = expect(l, "(");
					if (!biseqcstr(lpar, "(")){
						result = 0;
						printf("Se esperaba <(>");
					}
				}
			
				if(result){
					bstring ph = NULL;
					ph = expect(l, "ph");
					if (!biseqcstr(ph, "ph")){
						result = 0;
						printf("Se esperaba <ph>");
					}
				}
			
				if(result){
					bstring ph_value = NULL;
					ph_value = expect(l, DIGIT);
					if (biseqcstr(ph_value, "")){
						result = 0;
						printf("Se esperaba <ph_value>");
					}
					printf("Se leyó el value: %s\n", ph_value->data);
				}
			
				if(result){
					bstring rpar = NULL;
					rpar = expect(l, ")");
					if (!biseqcstr(rpar, ")")){
						result = 0;
						printf("Se esperaba <)>");
					}
				}
		
				if(result){
					bstring newline = NULL;
                    consume_spaces(l);
					newline = expect(l, "\n");
					if (biseqcstr(newline, "")){
						result = 0;
						printf("Se esperaba <newline>");
					}
				}
			}
	
			
			if (biseqcstr(sym, "d")){
				bstring delay_id = NULL;
				bstring newline = NULL;
				
				delay_id = expect(l, DIGIT);
				if (biseqcstr(delay_id, "")){
						result = 0;
						printf("Se esperaba <delay_id>");
				}
				printf("Se leyó el delay id: %s\n", delay_id->data);
				consume_spaces(l);
				newline = expect(l, "\n");
				if(biseqcstr(newline, "")){
						result = 0;
						printf("Se esperaba <newline>");
				}
           }

           if (!biseqcstr(sym, "d") && !biseqcstr(sym, "p")){
             result = 0; 
             printf("Simbolo no reconocido\n");
           }

		}
    sym = getsym(l);
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
  if (phase_declaration(l)){
  		printf("PHASES: Correctamente sintactico\n");
  	}else{
  		printf("PHASES: Incorrectamente sintactico\n");
  	}
  
  if (program(l)){
  		printf("PROGRAM: Correctamente sintactico\n");
  	}else{
  		printf("PROGRAM: Incorrectamente sintactico\n");
  	}



  return 0;
}









