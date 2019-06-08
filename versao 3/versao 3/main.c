#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arv_gen.h"
#include "figura.h"


static void menu(){
  printf("\n###### MENU ###### \n");
          printf("Escolha uma opção abaixo: \n");
          printf("1 - INSERIR FIGURA \n");
          printf("2 - IMPRIMIR ARVORE \n");
          printf("3 - IMPRIMIR FIGURA \n");
          printf("4 - REMOVER FIGURA \n");
          printf("5 - DESTRUIR ARVORE \n");
          printf("0 - SAIR\n");
}
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

  

  

//menu
     int opcao = 1;
     int destruida = 0;
     int cod = 0;
     int cp = 0;
     int insere = 1;
     char x='a';
     char n[4];
     float dim[3];
     float v1,v2,v3;

    while(opcao != 0){
          printf("\e[H\e[2J");
          menu();
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
                        printf("Digite a Base: \n");
                        scanf("%f",&v1);
                        dim[0] = v1;
                        printf("Digite a Altura: \n");
                        scanf("%f",&v2);
                        dim[1] = v2;
                    }

                    if(strcmp(n,"TRA")==0){
                      printf("Digite a Base maior: \n");
                      scanf("%f",&v1);
                      dim[0] = v1;
                      printf("Digite a Base menor: \n");
                      scanf("%f",&v2);
                      dim[1] = v2;
                      printf("Digite a Altura: \n");
                      scanf("%f",&v3);
                      dim[2] = v3;
                    }
                    TFIG* f = (TFIG*)agen_busca(a, &cod);

                    if(f!=NULL){
                      if(f->cod == cod){
                        printf("Figura não Inserida - Já existe esse código\n");
                        insere = 0;
                      }
                        if(cp == 0){
                          printf("Não pode inserir uma figura com pai 0\n");
                          insere = 0;
                        }
                        if(cod == cp){
                          printf("codigo do pai tem de ser diferente do codigo da figura");
                           insere = 0;
                        }
                      
                    }
                    if(insere){
                            insere_figura(a,cod,cp,n,dim);
                            printf("Figura Inserida\n");
                    }

                  x='a';
                  printf("Digite c para continuar\n");
                  while(x!='c'){
                      
                      scanf("%c", &x);
                  }
                    break;
              
          case 2:
            printf("\e[H\e[2J");
            printf("\n\nARVORE  \n\n");
            if(destruida ==0){
                  agen_percorre(a, cb_imprime, 1);
            }else{
                 printf("Ärvore Nula\n");
            }
             
            
            
            x='a';
                  printf("Digite c para continuar\n");
                  while(x!='c'){
                      
                      scanf("%c", &x);
                  }
        
            break;
          case 3:
              printf("Digite o codigo da figura: \n");
              scanf("%d",&cod);
               f = (TFIG*)agen_busca(a, &cod);
              imprime(f);
              x='a';
                  printf("Digite c para continuar\n");
                  while(x!='c'){
                      
                      scanf("%c", &x);
                  }
              break;

          case 4:

              printf("Digite o codigo da figura: \n");

              scanf("%d",&cod);

              agen_remover(a, &cod);

              printf("Figura Removida\n");
             x='a';
                  printf("Digite c para continuar\n");
                  while(x!='c'){
                      
                      scanf("%c", &x);
                  }

              break;
          case 5:
              agen_libera(a, free);
              printf("Arvore Destruida\n");
              destruida = 1;
            x='a';
                  printf("Digite c para continuar\n");
                  while(x!='c'){
                      
                      scanf("%c", &x);
                  }
                         
          }   
    }
   

	fclose(fp);	
  printf("FIM!");
	
	return 0;
	
}