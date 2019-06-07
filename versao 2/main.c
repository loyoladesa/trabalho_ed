#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arv_gen.h"
#include "figura.h"

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


int main(void){

  //char entrada[121];
 // printf("Digite o nome do arquivo de entrada: \n");
  //scanf("%120s",entrada);
	FILE* fp = fopen("arquivo.txt","rt");

	if(fp==NULL){
		printf("Não foi possível abrir arquivo de entrada. \n");
		return 1;
	}

	char linha[121];
		
  TAG* a = agen_cria(cmp_cod_figura);

	while(fgets(linha,121,fp)){
		int cod;
    int cod_pai;
    char nome[4];
		float v1,v2,v3;
    float d[3];

		int n = sscanf(linha,"%d/%d/%s%f%f%f",&cod,&cod_pai,nome,&v1,&v2,&v3);

    if(n>0){
			d[0]= v1;
      d[1]= v2;
      d[2]= v3;

      insere_figura(a, cod, cod_pai, nome, d);
		}
	}

    printf("Arquivo Lido com Sucesso! \n");

  

  int escolha = 0;

//menu
    int opcao = 1;
     int cod = 0;
     int cp = 0;
     char n[4];
     float dim[3];
     float v1,v2,v3;
    while(opcao != 0){
          printf("\n###### MENU ###### \n");
          printf("Escolha uma opção abaixo: \n");
          printf("1 - INSERIR FIGURA \n2 - IMPRIMIR ARVORE \n3 - IMPRIMIR FIGURA \n4 - REMOVER FIGURA0 - SAIR\n");
          scanf("%d", &opcao);
          switch (opcao) {
          case 1:
              printf("Digite o codigo da figura: \n");
              scanf("%d",&cod);
              printf("Digite o codigo do Pai: \n");
              scanf("%d",&cp);
              printf("Digite a figura: \n");
              scanf("%s",n);

              if(strcmp(n,"QUA")==0){
                printf("Digite o Lado: \n");
                scanf("%f",&v1);
                dim[0]=v1;
              
              }
              if(strcmp(n,"CIR")==0){
                printf("Digite o Raio: \n");
                scanf("%f",&v1);
                dim[0] = v1;
              
              }
              
              if(strcmp(n,"TRI")==0){
                printf("Digite a Base: \n");
                scanf("%f",&v1);
                dim[0] = v1;
                printf("Digite a Altura: \n");
                scanf("%f",&v2);
                dim[1] = v2;


              }
              if(strcmp(n,"RET")==0){

              }

              if(strcmp(n,"TRA")==0){
              }
              
              insere_figura(a,cod,cp,n,dim);
              break;
              
          case 2:
            printf("\n\nARVORE  \n\n");
            agen_percorre(a, cb_imprime, 1);
            
            break;
          case 3:
              printf("Digite o codigo da figura: \n");
              scanf("%d",&cod);
              TFIG* f = (TFIG*)agen_busca(a, &cod);
              imprime(f);
              break;
                      case 4:

              printf("Digite o codigo da figura: \n");

              scanf("%d",&cod);

              agen_remover(a, &cod);

              break;
                            
          }
    }
   

	fclose(fp);	
  printf("FIM!");
	
	return 0;
	
}