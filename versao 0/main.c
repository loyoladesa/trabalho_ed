#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_gen.h"
#include "figura.h"
#include "minunit.h"

int tests_run = 0;

static int cmp_cod_figura(void* chave, void* info){
  
  TFIG* f = (TFIG*)info;
  int* cod = (int*)chave;
  //int x = cod;
  return cod[0] - f->cod;
}

static void insere_figura(TAG* a,int cod,int cod_pai,char* nome,float d[3]){
  TFIG* f = (TFIG*)malloc(sizeof(TFIG));
  f->cod = cod;
  f->cod_pai = cod_pai;
  strcpy(f->nome,nome);
  f->dim[0] = d[0];
  f->dim[1] = d[1];
  f->dim[2] = d[2];
  void* chave = &f->cod_pai;
  agen_insere(a,chave,f);
}

static char * teste_cria(){
	//  1/0/TRI 3 2
  printf("TESTE 1 \n");
  int funcionou = 0;
	
	TAG* a = agen_cria(cmp_cod_figura);

	if(a->raiz == NULL){
		funcionou = 1;
	}else{
		esperava_string("Valor Nulo","Raiz");
	}
	 mu_assert("[ERRO - criano]", funcionou == 1);
	 return 0;
}

static char * teste_insere_figura(){
	//  1/0/TRI 3 2
  printf("TESTE 2 \n");
  int funcionou = 0;
	
	TAG* a = agen_cria(cmp_cod_figura);
	TFIG* f = (TFIG*)malloc(sizeof(TFIG));
	f->cod = 1;
	f->cod_pai = 0;
	strcpy(f->nome,"TRI");
	f->dim[0]=3.0;
	f->dim[1]=2.0;
	int* chave = &f->cod_pai;
	agen_insere(a,chave,f);
	
	TFIG* g = (TFIG*)a->raiz->info;
	
	
	 mu_assert("[ERRO - insere_figura]", g->cod == 1);
	 
	 return 0;
}

static char* teste_busca(){
  printf("TESTE 3 \n");
  
  TAG* a = (TAG*)malloc(sizeof(TAG));
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  int cod = 1;
  void* chave = &cod;
  
  TFIG* f = agen_busca(a,chave);
  
  mu_assert("[ERRO_BUSCA",f->cod == 1);
  
}

static char * all_tests() {
     	mu_run_test(teste_cria);
     	mu_run_test(teste_insere_figura);
     	mu_run_test(teste_busca);
     	     
     return 0;
 }

int main(void){
	char *result = all_tests();
     	if (result != 0) {
         	printf("%s\n", result);
     	}
     	else {
         	printf("ALL TESTS PASSED\n");
     	}
     	printf("Tests run: %d\n", tests_run);
 ;
}