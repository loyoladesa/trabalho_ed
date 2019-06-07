#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_gen.h"
#include "figura.h"
#include "minunit.h"

int tests_run = 0;
void esperava_int(int ve,int vr);
void esperava_string(char* ve, char* vr);
void esperava_float(float ve,float vr);

char mensagem[121];
char erro[121];

static int cb_imprime(void* info,int dado){
  TFIG* f = (TFIG*)info;
  
  int i;
  for (i = 0; i < dado; i++) printf("   ");
  printf("%d \n",f->cod);
  return 0;
}

static int cb_contar(void* info,int dado){
  TFIG* f = (TFIG*)info;
    
  return dado++;
}

static int cmp_cod_figura(void* chave, void* info){
  
  TFIG* f = (TFIG*)info;
  int* cod = (int*)chave;
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
  printf("TESTE 1 - teste_cria \n");
  int funcionou = 0;
	
	TAG* a = agen_cria(cmp_cod_figura);

	
  strcpy(mensagem,"[ERRO - criano]");
  esperava_string("Valor Nulo","Raiz");
	mu_assert(erro, a->raiz == NULL);
	return 0;
}

static char * teste_insere_figura(){
	//  1/0/TRI 3 2
  printf("TESTE 2 - teste_insere_figura \n");
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
	
	strcpy(mensagem,"[ERRO - insere_figura]");
  esperava_int(1,g->cod);
	mu_assert(erro, g->cod == 1);
	 
	 return 0;
}

static char* teste_busca(){
  printf("TESTE 3 - teste_busca \n");
  
 TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  int cod = 1;

  void* chave = &cod;
  
  TFIG* f = agen_busca(a,chave);

  strcpy(mensagem,"[ERRO - busca]");
  esperava_int(1,f->cod);

  mu_assert(erro,f->cod == 1);
  return 0;
}

static char* teste_insere_2_figuras(){
  printf("TESTE 4 - insere_2_figuras \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);

  TFIG* f = (TFIG*)a->raiz->filho->info;

  strcpy(mensagem,"[ERRO - insere_2_figuras]");
  esperava_int(2,f->cod);

  mu_assert(erro,f->cod == 2);
  return 0;
  
}

static char* teste_insere_3_figuras(){
  printf("TESTE 5 - insere_3_figuras \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);
  insere_figura(a,3,2,"QUA",d);

  TFIG* f = (TFIG*)a->raiz->filho->filho->info;

  strcpy(mensagem,"[ERRO - insere_3_figuras]");
  esperava_int(3,f->cod);

  mu_assert(erro,f->cod == 3);
  return 0;
  
}

static char* teste_insere_figura_irmao(){
  printf("TESTE 6 - insere_figura_irmao \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);
  insere_figura(a,3,1,"QUA",d);

  TFIG* f = (TFIG*)a->raiz->filho->irmao->info;

  strcpy(mensagem,"[ERRO - insere_figura_irmao]");
  esperava_int(3,f->cod);

  mu_assert(erro,f->cod == 3);
  return 0;
  
}

static char* teste_busca_5(){
  /*
    1/0/TRI 3 2
2/1/RET 3 3
3/1/TRA 2 3 4
4/1/CIR 4
5/4/QUA 3
6/2/RET 2 2
7/5/TRA 1 2 3
8/5/CIR 2
9/4/QUA 1
10/1/TRI 1 2
  */
  printf("TESTE 7 - teste_busca_5 \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);
  insere_figura(a,3,1,"QUA",d);
  insere_figura(a,4,1,"QUA",d);
  insere_figura(a,5,2,"QUA",d);
  insere_figura(a,6,4,"QUA",d);
  insere_figura(a,7,5,"QUA",d);
  insere_figura(a,8,5,"QUA",d);
  insere_figura(a,9,4,"QUA",d);
  insere_figura(a,10,1,"QUA",d);
  
  agen_percorre(a, cb_imprime, 1);
  

  int z = 5;
  void* chave = &z;

  TFIG* f = (TFIG*)agen_busca(a,chave);

  strcpy(mensagem,"[ERRO - busca_5]");
  esperava_int(5,f->cod);

  mu_assert(erro,f->cod == 5);
  return 0;
  
}


static char* teste_remover_nulo(){
  printf("TESTE 8 - remover_nulo \n");
  TAG* a = agen_cria(cmp_cod_figura);
  
  int z = 2;
  void* chave = &z;

  TFIG* f = (TFIG*)agen_remover(a,chave);

  strcpy(mensagem,"[ERRO - remover_nulo]");
  mu_assert(erro,f == NULL);
  return 0;  
}


static char* teste_remover_raiz(){
  printf("TESTE 9 - remover_raiz \n");
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  
  int z = 1;
  void* chave = &z;

  TFIG* f = (TFIG*)agen_remover(a,chave);

  strcpy(mensagem,"[ERRO - remover_RAIZ]");
  mu_assert(erro,f == NULL);
  return 0;  
}

static char* teste_remover(){
  printf("TESTE 10 - teste_remover \n");
  TAG* a = agen_cria(cmp_cod_figura);
  
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);


   int z = 2;
   void* chave = &z;
   
  TFIG* f = (TFIG*)agen_remover(a,chave);

  agen_percorre(a, cb_imprime, 1);
  
  
  strcpy(mensagem,"[ERRO - remover]");
  esperava_int(2,f->cod==2);
  mu_assert(erro,f->cod == 2);

  return 0;
}

static char* teste_remover_3(){
  printf("TESTE 11 - teste_remover_3\n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3]={3.0,3.2};
  
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"TRI",d);
  insere_figura(a,3,1,"TRI",d);
  
  int z = 3;
  void* chave = &z;

  TFIG* f = (TFIG*)agen_remover(a,chave);
  agen_percorre(a, cb_imprime, 1);
  
  strcpy(mensagem,"[ERRO - remover_3]");
  //esperava_int(3,f->cod);
  mu_assert(erro,f == NULL);

  return 0;
}

static char* teste_insereNo_Nulo(){
  printf("TESTE 12 - teste_insereNo_Nulo \n");
  TNO* filho = NULL;
  TNO* pai = (TNO*)malloc(sizeof(TNO));

  TFIG* f = (TFIG*)malloc(sizeof(TFIG));
  f->cod = 1;
  pai->info = f;
  
 insereNo(filho, pai);
  
  strcpy(mensagem,"[ERRO - insereNo_Nulo]");
  esperava_int(2,f->cod==1);
  mu_assert(erro,pai->filho == NULL);

  return 0;
}

static char* teste_remover_5(){
  
  printf("TESTE 13 - teste_remover_5 \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);
  insere_figura(a,3,1,"QUA",d);
  insere_figura(a,4,1,"QUA",d);
  insere_figura(a,5,2,"QUA",d);
  insere_figura(a,6,4,"QUA",d);
  insere_figura(a,7,5,"QUA",d);
  insere_figura(a,8,5,"QUA",d);
  insere_figura(a,9,4,"QUA",d);
  insere_figura(a,10,1,"QUA",d);
  
  printf("ARVORE ORIGINAL \n");
  agen_percorre(a, cb_imprime, 1);
  

  int z = 5;
  void* chave = &z;   

  TFIG* f = (TFIG*)agen_remover(a,chave);  
  printf("ARVORE REMOVIDA \n");
  agen_percorre(a, cb_imprime, 1);

  strcpy(mensagem,"[ERRO - remover_5]");
  //esperava_int(5,f->cod);

  mu_assert(erro,f == NULL);
  return 0;
  
}

static char* teste_remover_N3(){
  
  printf("TESTE 14 - teste_remover_N3 \n");
  
  TAG* a = agen_cria(cmp_cod_figura);
  float d[3] = {3.0,2.0};
  insere_figura(a,1,0,"TRI",d);
  insere_figura(a,2,1,"QUA",d);
  insere_figura(a,3,1,"QUA",d);
  insere_figura(a,4,1,"QUA",d);
  insere_figura(a,5,2,"QUA",d);
  insere_figura(a,6,4,"QUA",d);
  insere_figura(a,7,5,"QUA",d);
  insere_figura(a,8,5,"QUA",d);
  insere_figura(a,9,4,"QUA",d);
  insere_figura(a,10,1,"QUA",d);
  
  printf("ARVORE ORIGINAL \n");
  agen_percorre(a, cb_imprime, 1);
  

  int z = 3;
  void* chave = &z;   

  TFIG* f = (TFIG*)agen_remover(a,chave);  
  printf("ARVORE REMOVIDA \n");
  agen_percorre(a, cb_imprime, 1);

  strcpy(mensagem,"[ERRO - remover_N3]");
  //esperava_int(5,f->cod);

  mu_assert(erro,f == NULL);
  return 0;
  
}


static char * all_tests() {
     	mu_run_test(teste_cria);
     	mu_run_test(teste_insere_figura);
     	mu_run_test(teste_busca);
      mu_run_test(teste_insere_2_figuras);
      mu_run_test(teste_insere_3_figuras);
      mu_run_test(teste_insere_figura_irmao);
      mu_run_test(teste_busca_5);
      mu_run_test(teste_remover_nulo);
      mu_run_test(teste_remover_raiz);
     	mu_run_test(teste_remover);
      mu_run_test(teste_remover_3);
      mu_run_test(teste_insereNo_Nulo);
      mu_run_test(teste_remover_5);
      mu_run_test(teste_remover_N3);
     	
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

void esperava_int(int ve,int vr){
	 sprintf(erro,"%s -- Valor Esperado =  %d , Valor Real = %d\n",mensagem,ve,vr);
}

void esperava_string(char* ve, char* vr){
	sprintf(erro,"%s -- Valor Esperado =  %s , Valor Real = %s\n",mensagem,ve,vr);
}

void esperava_float(float ve,float vr){
	sprintf(erro,"%s -- Valor Esperado =  %.2f , Valor Real = %.2f\n",mensagem,ve,vr);
}
