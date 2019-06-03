typedef struct figura TFIG;
void imprime(TFIG* f);

struct figura{
	int cod;
	int cod_pai;
	char nome[121];
	float dim[3];
};


void imprime(TFIG* f){
  printf("--Figura--\n");
	printf("Código = %d\n",f->cod);
	printf("Pai = %d\n",f->cod_pai);
	printf("Figura = %s\n",f->nome);
}
