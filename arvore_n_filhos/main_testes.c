#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvnFilhos.h"
#include "minunit.h"

int tests_run = 0;

static char * teste_criano(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->cod == 1){
		if(a->cod_pai == 0){
			
			if(strcmp(a->nome,"TRI")==0){
				
				if(a->dim[0] == 3.0){
					
					if(a->dim[1] == 2.0){
						
						if(a->prim == NULL){
							if(a->prox == NULL){
								funcionou = 1;
							}
						}
					}
				}
			}
		}
	}
	 mu_assert("[error-criano]", funcionou == 1);
	 return 0;
}


static char * teste_criano_codigo(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->cod == 1){
		funcionou = 1;
	}else{
		printf("expect cod = 1, but cod = %d \n", c);
	}
	 mu_assert("[ERRO - criano_codigo]", funcionou == 1);
	 return 0;
}

static char * teste_criano_codigopai(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->cod_pai == 0){
		funcionou = 1;
	}else{
		printf("expect cod = 0, but cod = %d \n", c);
	}
	 mu_assert("[ERRO - criano_codigo]", funcionou == 1);
	 return 0;
}

static char * teste_criano_nome(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(strcmp(a->nome,n)==0){
		funcionou = 1;
	}else{
		printf("expect nome = TRI, but nome = %s \n", a->nome);
	}
	 mu_assert("[ERRO - criano_nome]", funcionou == 1);
	 return 0;
}

static char * teste_criano_dim1(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->dim[0]==3.0){
		funcionou = 1;
	}else{
		printf("expect dim[0] = 3.0, but dim[0] = %f \n", a->dim[0]);
	}
	 mu_assert("[ERRO - criano_dim1]", funcionou == 1);
	 return 0;
}

static char * teste_criano_dim2(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->dim[1]==2.0){
		funcionou = 1;
	}else{
		printf("expect dim[1] = 2.0, but dim[1] = %f \n", a->dim[1]);
	}
	 mu_assert("[ERRO - criano_dim2]", funcionou == 1);
	 return 0;
}

static char * teste_criano_dim3(){
	/* 1/0/TRI 3 2*/
	int funcionou = 0;
	
	int c = 1;
	int cp = 0;
	char* n = "TRI";
	float d[3] = {3.0,2.0};
	
	ArvnNo* a = arvn_criano(c,cp,n,d);
	if(a->dim[2]==0.0){
		funcionou = 1;
	}else{
		printf("expect dim[2] = 0.0, but dim[2] = %f \n", a->dim[2]);
	}
	 mu_assert("[ERRO - criano_dim3]", funcionou == 1);
	 return 0;
}





static char * all_tests() {
     	mu_run_test(teste_criano_codigo);
     	mu_run_test(teste_criano_codigopai);
     	mu_run_test(teste_criano_nome);
	mu_run_test(teste_criano_dim1);
	mu_run_test(teste_criano_dim2);
	mu_run_test(teste_criano_dim3);
    	mu_run_test(teste_criano);
     
     
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
