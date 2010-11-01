#include <stdio.h>
#include <assert.h>

#include "lexer.h"

/* Funciones auxiliares */
bstring getsym(Lexer *l);
bstring expect(Lexer *l, char* token);


/* Partes de un programa */
bool program(Lexer *l);



/* Obtener el siguiente simbolo (palabra reservada) */
bstring getsym(Lexer *l){

  /* PRE */
  assert(l != NULL);
    
  lexer_skip_to(l, "d" "p" "e" "--" );
  lexer_next(l, "d" "p" "e" "--");
  
  return lexer_item(l);
}


bstring expect(Lexer *l, char* token){
 
  /* PRE */
  assert(l != NULL);
  assert(token != NULL);
  
  lexer_next(l, token);

  return lexer_item(l);
}


bool program(Lexer *l){
  bstring sym = NULL;
  
  
  sym = getsym(l);
  while (!biseq(bfromcstr("e"), sym)){
  
    if (biseq(bfromcstr("p"), sym)){
      /* Leimos un pulso */
      bstring pulse_number = NULL;
      bstring pulse_id = NULL;
      
      pulse_id = expect(l, "0123456789");
      if (biseqcstr(pulse_id, "")) return 0; 
      
      expect(l, "(");
      if (biseqcstr(pulse_id, "")) return 0; 
      
      pulse_number = expect(l, "0123456789");
      if (biseqcstr(pulse_id, "")) return 0; 
      
      expect(l, ")");
      if (biseqcstr(pulse_id, "")) return 0; 
      
      
      printf("Se leyo el pulso: P%s con el valor %s\n",
            pulse_id->data, pulse_number->data);
    }
    
    if (biseq(bfromcstr("d"), sym)){
      /* Lei un delay */
      bstring delay_id = NULL;
      
      delay_id = expect(l, "0123456789");
      if (biseqcstr(delay_id, "")) return 0; 
      
      
      printf("Se leyó el delay D%s\n", delay_id->data);
    }
    
    if (biseq(bfromcstr("--"), sym)){
      /* Lei un delay */
      bstring delay_id = NULL;
      
      delay_id = expect(l, ALPHANUMERIC " " ".");
      if (biseqcstr(delay_id, "")) return 0; 
      
      
      printf("Se leyó el comentario: %s\n", delay_id->data);
    }
    
  sym = getsym(l);
  }

  return 1;
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
  if (program(l)) printf("\nSintacticamente correcto\n");
  else printf("Errores de sintaxis\n");



  return 0;
}