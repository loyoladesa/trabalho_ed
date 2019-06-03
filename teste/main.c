#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_gen.h"
#include "figura.h"

static int* cmp_cod_figura(void* chave,void* info){
	int* cod = chave;
	TFIG* f = (TFIG*)info;
	return (cod - f->cod);
}

int main(void) {
  float d[3] = {3.0,2.0};
  TFIG* f = (TFIG*)malloc(sizeof(TFIG));
  f->cod = 1;
  f->cod_pai = 0;
  strcpy(f->nome, "TRI");

  imprime(f);
  return 0;
}
