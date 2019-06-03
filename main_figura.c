#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arv_gen.h"
#include "minunit.h"
#include "figura.h"


static int cmp_cod_figura(void* chave,void* info){
	int cod =(int*) chave;
	fig* f = (fig*)info;
	return (cod - f->cod);
}

static int insere_figura(ArvGen* a, int cod,int cod_pai,char nome[121],float dim[3]){
	fig* f = (fig*)malloc(sizeof(fig));
	f->cod = cod;
	f->cod_pai = cod_pai;
	strcpy(f->nome,nome);
	for(int i=0;i<3;i++){
		f->dim[i] = dim[i];
	}
	if(f->cod == f->cod_pai) return 0;
	fig* jaExiste = (fig*)agen_busca(a,f->cod);
	if(jaExiste != NULL) return 1;
	fig* pai = (fig*)agen_busca(a,f->cod_pai);
	if(pai == NULL && a->raiz!= NULL){
		return 2;
	}
	agen_insere(a,f->cod_pai,f);

	return 3;
}

int main(void){
	ArvGen* a = agen_cria(cmp_cod_figura);
	float d[3] = {3.0,2.0};
	int inseriu = insere_figura(a,1,0,"TRI",d);
	

	
	fig* raiz = (fig*)agen_busca(a,1);

	printf("--Figura--\n");
	printf("Código = %d\n",raiz->cod);
	printf("Pai = %d\n",raiz->cod_pai);
	printf("Figura = %s\n",raiz->nome);

	
	return 0;
	
}
