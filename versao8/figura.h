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

  if(strcmp(f->nome,"QUA")==0){
    printf("Lado = %.2f\n",f->dim[0]);
    printf("Area = %.2f\n",(f->dim[0]*f->dim[0]));
  
  }
  if(strcmp(f->nome,"CIR")==0){
    printf("Raio = %.2f\n",f->dim[0]);
    printf("Area = %.2f\n",f->dim[0]*3.141598*f->dim[0]);
  
  }
  
  if(strcmp(f->nome,"TRI")==0){
    printf("Base = %.2f\n",f->dim[0]);
    printf("Altura = %.2f\n",f->dim[1]);
    printf("Area = %.2f\n",(f->dim[0]*f->dim[1])/2);
  
  }
  if(strcmp(f->nome,"RET")==0){
    printf("Base = %.2f\n",f->dim[0]);
    printf("Altura = %.2f\n",f->dim[1]);
    printf("Area = %.2f\n",(f->dim[0]*f->dim[1]));
  
  }

  if(strcmp(f->nome,"TRA")==0){
    printf("Base Menor = %.2f\n",f->dim[0]);
    printf("Base Maior = %.2f\n",f->dim[1]);
    printf("Altura = %.2f\n",f->dim[2]);
    printf("Area = %.2f\n",(f->dim[0]+f->dim[1])*f->dim[2]/2);
  
  }
  printf("--------\n\n");
  

}