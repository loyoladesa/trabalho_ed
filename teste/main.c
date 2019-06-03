#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_gen.h"
#include "figura.h"

static int cmp_cod_figura(void* chave,void* info){
	int cod = chave;
	TFIG* f = (TFIG*)info;
	return (cod - f->cod);
}

static int insere_figura(TAG* a, int cod,int cod_pai,char nome[121],float dim[3]){
	TFIG* f = (TFIG*)malloc(sizeof(TFIG));
  f->cod = cod;
  f->cod_pai = cod_pai;
  strcpy(f->nome, nome);
	for(int i=0;i<3;i++){
		f->dim[i] = dim[i];
	}
	
	agen_insere(a,f->cod_pai,f);

	return 3;
}

int main(void) {
  float d[3] = {3.0,2.0};
  TFIG* f = (TFIG*)malloc(sizeof(TFIG));
  f->cod = 1;
  f->cod_pai = 0;
  strcpy(f->nome, "TRI");

  imprime(f);


  TAG* a = agen_cria(cmp_cod_figura);
  int x = insere_figura(a,1,0,"TRI",d);
  if(x==3)printf("sucesso!\n");

  printf("Cod = %d\n",a->raiz->cod);
  printf("fim!\n");
  return 0;
}
