
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "figura.h"
#include "lista.h"
#include "arv_gen.h"
#include "arv_bbb.h"
#include "arv_b.h"



static int cb_imprime(void* info){
      TFIG* f = (TFIG*)info;
      printf("%d\n",f->cod);
      return 0;
}

static int cb_fig(void* info){
      TFIG* f = (TFIG*)info;
      imprime(f);
      return 0;
}

static int cmp_cod_figura(void* chave, void* info){
        TFIG* f = (TFIG*)info;
        TFIG* g = (TFIG*)chave;
        return g->cod - f->cod;
}

static int cb_transformar(void* info,void* dado){
      TFIG* f = (TFIG*)info;
      TFIG* novo = (TFIG*)malloc(sizeof(TFIG));
      novo->cod = f->cod;
      novo->cod_pai = f->cod_pai;
      strcpy(novo->nome,f->nome);
      novo->dim[0] = f->dim[0];
      novo->dim[1] = f->dim[1];
      novo->dim[2] = f->dim[2];

      TABBB* abin = (TABBB*)dado;
      TFIG* chave = (TFIG*)malloc(sizeof(TFIG));
      chave->cod = f->cod;
      abin_insere(abin,chave, novo);
      free(chave);
      return 0;
}
static int cb_transformar_tag(void* info,void* dado){
      TFIG* f = (TFIG*)info;
      TFIG* novo = (TFIG*)malloc(sizeof(TFIG));
      novo->cod = f->cod;
      novo->cod_pai = f->cod_pai;
      strcpy(novo->nome,f->nome);
      novo->dim[0] = f->dim[0];
      novo->dim[1] = f->dim[1];
      novo->dim[2] = f->dim[2];

      TAG* agen = (TAG*)dado;
      TFIG* chave = (TFIG*)malloc(sizeof(TFIG));
      chave->cod = f->cod_pai;
      agen_insere(agen,chave,novo);
      free(chave);
      return 0;
}
static int cb_transformar_lista(void* info,void* dado){
      TFIG* f = (TFIG*)info;
      TLG* l =(TLG*)dado;

      l_insere(l, f);
      return 0;
}

static void menu(){
      printf("\e[H\e[2J");
      printf("\n###### MENU ###### \n");
      //printf("Escolha uma opção abaixo: \n");

      printf("1 - IMPRIMIR ARVORE \n");
      printf("2 - BUSCAR FIGURA \n");
      printf("3 - INSERIR FIGURA \n");
      printf("4 - REMOVER FIGURA \n");
      printf("5 - ALTERAR FIGURA \n");
      printf("6 - TRANSFORMAR TAG EM TABBB \n");
      printf("7 - TRANSFORMAR TAG EM TAB \n");
      printf("8 - RECARREGAR ARQUIVO TAG \n");
      printf("9 - DESTRUIR ARVORE \n");


      printf("10 - SAIR\n");
      printf("\n\n");
}

static void obter_dimensoes(char* n,float* dim,float*v1,float*v2,float*v3){
										if(strcmp(n,"QUA")==0){
                      printf("Digite o Lado: \n");
                      scanf("%f",v1);
                      dim[0]=v1[0];

                    }
                    if(strcmp(n,"CIR")==0){
                      printf("Digite o Raio: \n");
                      scanf("%f",v1);
                      dim[0] = v1[0];
                    }
                    if(strcmp(n,"TRI")==0){
                      printf("Digite a Base: \n");
                      scanf("%f",v1);
                      dim[0] = v1[0];
                      printf("Digite a Altura: \n");
                      scanf("%f",v2);
                      dim[1] = v2[0];
                    }
                    if(strcmp(n,"RET")==0){
                        printf("Digite a Base: \n");
                        scanf("%f",v1);
                        dim[0] = v1[0];
                        printf("Digite a Altura: \n");
                        scanf("%f",v2);
                        dim[1] = v2[0];
                    }

                    if(strcmp(n,"TRA")==0){
                      printf("Digite a Base menor: \n");
                      scanf("%f",v1);
                      dim[0] = v1[0];
                      printf("Digite a Base maior: \n");
                      scanf("%f",v2);
                      dim[1] = v2[0];
                      printf("Digite a Altura: \n");
                      scanf("%f",v3);
                      dim[2] = v3[0];
                    }
}

static int saida(char* leitura){

    printf("\nEscolha uma opção do menu: \n");
    scanf("%s", leitura);
    return atoi(leitura);

}
static void obter_codigo(int* cod){
    printf("Digite o codigo da figura: \n");
    scanf("%d",cod);
}
static void nao_existe_figura(int* cod){
	printf("Não existe figura com esse código. \n");
    printf("Digite o codigo da Figura: \n");
    scanf("%d",cod);
}

static void ja_existe_figura(int*cod){
			printf("Já existe figura com esse código. \n");
			printf("Digite o codigo da figura: \n");
			scanf("%d",cod);
}

int main()
{
    //leitura do arquivo
	char entrada[121];
	char linha[121];


    //cria as estruturas
    TAG* agen = agen_cria(cmp_cod_figura);
    TABBB* abin;
    TAB* a  = Inicializa();
    TLG* l = l_cria(cmp_cod_figura);
    TFIG* g = (TFIG*)malloc(sizeof(TFIG));
    TFIG* f = (TFIG*)malloc(sizeof(TFIG));
     //variaveis auxiliares
    int cod, cp,destruida = 0, opcao = 25,estrutura = 1;
    char n[4],leitura[1];
    float v1,v2,v3;
    float dim[3];


    //printf("Digite o nome do arquivo de entrada: \n");
    //scanf("%120s",entrada);
	FILE* fp = fopen("arquivo.txt","rt");

	if(fp==NULL){
		printf("Não foi possível abrir arquivo de entrada. \n");
		return 1;
	}

    //le as linhas do arquivo
	while(fgets(linha,121,fp)){
          int num = sscanf(linha,"%d/%d/%s%f%f%f",&cod,&cp,n,&v1,&v2,&v3);
          if(num>0){

              dim[0]= v1;
              dim[1]= v2;
              dim[2]= v3;

              f = (TFIG*)malloc(sizeof(TFIG));
              f->cod = cod;
              f->cod_pai = cp;
              strcpy(f->nome,n);
              f->dim[0] = dim[0];
              f->dim[1] = dim[1];
              f->dim[2] = dim[2];
              g->cod = cp;

              agen_insere(agen,g,f);
          }
	}

 //opcao do menu
 while(opcao!=10){

         menu();
		switch (opcao) {

		    case 1:
                if(destruida){
                    printf("A estrutura já foi destruida. \n");
                }else {
                        if(estrutura == 1)agen_imprime(agen,cb_imprime);
                        if(estrutura == 2)abin_imprime(abin,cb_imprime);
                        if(estrutura == 3){
                             printf("#####   ARVORE TAB  ######\n\n");
                             Imprime(a,0,cb_imprime);
                        }
                }

		        break;
            case 2:
		        if(destruida){
                    printf("A estrutura já foi destruida. \n");
		        }else{
                    obter_codigo(&cod);
                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                    if(estrutura == 1){
                        while(agen_busca(agen,g)==NULL){
                            nao_existe_figura(&cod);
                            g->cod = cod;
                        }
                        f = (TFIG*)agen_busca(agen,g);
                        imprime(f);
                    }
                    if(estrutura == 2){
                        while(abin_busca(abin,g)==NULL){
                            nao_existe_figura(&cod);
                            g->cod = cod;
                        }
                        f = (TFIG*)abin_busca(abin,g);
                        imprime(f);
                    }
                    if(estrutura == 3){
                        while(Busca(a, g,cmp_cod_figura) == NULL){
                            nao_existe_figura(&cod);
                            g->cod = cod;
                        }
                        buscar_chave(a,0,g,cmp_cod_figura,cb_fig);
                    }
		        }
		        break;
		    case 3:
		        if(destruida){
                        printf("A estrutura já foi destruída.\n");
		        }else{
                    obter_codigo(&cod);

                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                    if(estrutura == 1){
                        while(agen_busca(agen, g) != NULL){
                            ja_existe_figura(&cod);
                            g->cod = cod;
                        }
                        printf("Digite o código do Pai: \n");
                        scanf("%d",&cp);
                        g->cod = cp;
                        while(agen_busca(agen,g)==NULL || cp == cod){
                            if(cp==cod){
                                printf("O código do pai tem de ser diferente do código da figura.");
                            }else{
                                printf("Não existe figura com esse código");
                            }
                             printf("Digite o código do Pai: \n");
                             scanf("%d",&cp);
                             g->cod = cp;
                        }
                        printf("Digite a figura: \n");
                        scanf("%s",n);

                        int p_figura = 1;

                        while(p_figura){
                              if(strcmp(n,"QUA")==0 || strcmp(n,"CIR")==0 || strcmp(n,"TRI")==0 || strcmp(n,"RET")==0 || strcmp(n,"TRA")==0){
                                p_figura = 0;
                              }else{
                                printf("Figura Inválida. As figuras válidas são:\n");
                                printf("CIR, QUA, TRI, RET e TRA\n");
                                printf("Digite a figura: \n");
                                scanf("%s",n);
                              }
                        }

                        obter_dimensoes(n,dim,&v1,&v2,&v3);
                        f = (TFIG*)malloc(sizeof(TFIG));
                        f->cod = cod;
                        f->cod_pai = cp;
                        strcpy(f->nome,n);
                        f->dim[0] = dim[0];
                        f->dim[1] = dim[1];
                        f->dim[2] = dim[2];

                        agen_insere(agen,g,f);
                    }
                    if(estrutura == 2){
                        while(abin_busca(abin, g) != NULL){
                            ja_existe_figura(&cod);
                            g->cod = cod;
                        }
                        printf("Digite a figura: \n");
                            scanf("%s",n);

                            int p_figura = 1;

                            while(p_figura){
                                  if(strcmp(n,"QUA")==0 || strcmp(n,"CIR")==0 || strcmp(n,"TRI")==0 || strcmp(n,"RET")==0 || strcmp(n,"TRA")==0){
                                    p_figura = 0;
                                  }else{
                                    printf("Figura Inválida. As figuras válidas são:\n");
                                    printf("CIR, QUA, TRI, RET e TRA\n");
                                    printf("Digite a figura: \n");
                                    scanf("%s",n);
                                  }
                            }
                            obter_dimensoes(n,dim,&v1,&v2,&v3);

                            f = (TFIG*)malloc(sizeof(TFIG));
                            f->cod = cod;
                            f->cod_pai = cp;
                            strcpy(f->nome,n);
                            f->dim[0] = dim[0];
                            f->dim[1] = dim[1];
                            f->dim[2] = dim[2];
                            abin_insere(abin,g,f);

                    }
                    if(estrutura == 3){

                            while(Busca(a, g,cmp_cod_figura) != NULL){
                                ja_existe_figura(&cod);
                                g->cod = cod;
                            }
                            printf("Digite a figura: \n");
                            scanf("%s",n);

                            int p_figura = 1;

                            while(p_figura){
                                  if(strcmp(n,"QUA")==0 || strcmp(n,"CIR")==0 || strcmp(n,"TRI")==0 || strcmp(n,"RET")==0 || strcmp(n,"TRA")==0){
                                    p_figura = 0;
                                  }else{
                                    printf("Figura Inválida. As figuras válidas são:\n");
                                    printf("CIR, QUA, TRI, RET e TRA\n");
                                    printf("Digite a figura: \n");
                                    scanf("%s",n);
                                  }
                            }
                            obter_dimensoes(n,dim,&v1,&v2,&v3);

                              strcpy(g->nome,n);
                              g->dim[0] = dim[0];
                              g->dim[1] = dim[1];
                              g->dim[2] = dim[2];

                              a = Insere(a,g,2,cmp_cod_figura);
                    }


                      printf("Figura Inserida! \n");
		        }

		        break;
		    case 4:
		        if(destruida){
                    printf("A estrutura já foi destruída.\n");
		        }else{
                    obter_codigo(&cod);
                    g->cod = cod;

                    if(estrutura == 1){
                        while(agen_busca(agen,g) == NULL){
                            nao_existe_figura(&cod);
                             g->cod = cod;
                        }

                        int p_remover = 1;

                        printf("Digite o codigo do novo pai dos possíveis filhos ou digite 0 para o programa escolher o novo pai.\n");
                        scanf("%d",&cp);
                        g->cod = cp;

                        while(p_remover){
                            if(cp == 0){
                                p_remover = 0;
                            }else{
                                if(agen_busca(agen, g) == NULL){
                                        printf("Não existe figura com esse código. \n");
                                        printf("Digite o codigo do novo pai dos possíveis filhos ou digite 0 para o programa escolher o novo pai.\n");
                                        scanf("%d",&cp);
                                        g->cod = cp;

                                }else{
                                    f = (TFIG*)malloc(sizeof(TFIG));
                                    f->cod = cod;
                                    if(agen_eh_filho(agen, g, f)){
                                        printf("O novo pai não poder ser filho do elemento removido \n");
                                        printf("Digite o codigo do novo pai dos possíveis filhos ou digite 0 para o programa escolher o novo pai.\n");
                                        scanf("%d",&cp);
                                        g->cod = cp;
                                    }else{
                                        p_remover = 0;
                                    }

                                }
                            }
                        }

                        if(cp==0){
                            g->cod = cod;
                            agen_remover(agen, g);
                        }else{
                            f = (TFIG*)malloc(sizeof(TFIG));
                            f->cod = cod;
                            agen_remover_np(agen, f,g);
                        }
                    }
                    if(estrutura == 2){
                        while(abin_busca(abin, g) == NULL){
                                    nao_existe_figura(&cod);
                                    g->cod = cod;
                            }
                            abin_remover(abin,g);
                    }
                    if(estrutura == 3){
                        while(Busca(a, g,cmp_cod_figura) == NULL){
                        nao_existe_figura(&cod);
                        g->cod = cod;
                    }
                    retira(a,g,2,cmp_cod_figura);
                    }
                    printf("Figura Removida! \n");
		        }
		        break;

		    case 5:
                if(destruida){
                    printf("A estrutura já foi destruída. \n");
                }else{
                    obter_codigo(&cod);
                    g->cod = cod;

                       if(estrutura == 1){
                            while(agen_busca(agen,g)==NULL){
                                nao_existe_figura(&cod);
                                g->cod = cod;
                            }
                            f = (TFIG*)agen_busca(agen,g);
                            imprime(f);
                            obter_dimensoes(f->nome,dim,&v1,&v2,&v3);

                                f->dim[0] = dim[0];
                                f->dim[1] = dim[1];
                                f->dim[2] = dim[2];

                       }
                       if(estrutura == 2){
                            while(abin_busca(abin,g)==NULL){
                                nao_existe_figura(&cod);
                                g->cod = cod;
                            }
                            f = (TFIG*)abin_busca(abin,g);
                            imprime(f);
                            obter_dimensoes(f->nome,dim,&v1,&v2,&v3);

                                f->dim[0] = dim[0];
                                f->dim[1] = dim[1];
                                f->dim[2] = dim[2];

                       }
                       if(estrutura == 3){
                            g = (TFIG*)malloc(sizeof(TFIG));
                            g->cod = cod;
                            buscar_chave(a,0,g,cmp_cod_figura,cb_fig);
                            g = (TFIG*)Busca_info(a,g,cmp_cod_figura);
                            printf("%s \n",g->nome);
                            obter_dimensoes(g->nome,dim,&v1,&v2,&v3);

                            g->dim[0] = dim[0];
                            g->dim[1] = dim[1];
                            g->dim[2] = dim[2];
                    }
                    printf("Figura Alterada! \n");
                }
		        break;
            case 6:
                if(destruida){
                    printf("A estrutura já foi destruida. \n");
                }
                else{
                    if(estrutura == 2 || estrutura == 3){
                        printf("Recarregue a TAG para completar esta operação.\n");
                    }else{
                        abin = abin_cria(cmp_cod_figura);
                        agen_percorre_gen(agen, cb_transformar, abin);
                        abin_imprime(abin,cb_imprime);
                        estrutura = 2;
                        agen_libera(agen,free);
                    }
                }
                break;
            case 7:
                if(destruida){
                    printf("A estrutura já foi destruida. \n");
                }else{
                    if(estrutura == 2 || estrutura == 3){
                        printf("Recarregue a TAG para completar esta operação.\n");
                    }else{

                        agen_percorre_gen(agen, cb_transformar_lista,l);

                        while(l->prim!= NULL){
                              f = (TFIG*)l_retira(l);

                              TFIG* novo = (TFIG*)malloc(sizeof(TFIG));
                              novo->cod = f->cod;
                              novo->cod_pai = f->cod_pai;
                              strcpy(novo->nome,f->nome);
                              novo->dim[0] = f->dim[0];
                              novo->dim[1] = f->dim[1];
                              novo->dim[2] = f->dim[2];

                              a = Insere(a,novo,2,cmp_cod_figura);
                              free(f);
                        }

                        printf("#####   ARVORE TAB  ######\n\n");
                        Imprime(a,0,cb_imprime);
                        estrutura = 3;
                        //agen_libera(agen,free);
                        //l_libera(l);
                    }
                }
                break;
            case 8:
                    if(!destruida){
                        if(estrutura == 1)agen_libera(agen,free);
                        if(estrutura == 2)abin_libera(abin,free);
                        if(estrutura == 3)Libera(a);
                    }

                    agen = agen_cria(cmp_cod_figura);

                    //printf("Digite o nome do arquivo de entrada: \n");
                    //scanf("%120s",entrada);
                    fp = fopen("arquivo.txt","rt");

                    if(fp==NULL){
                        printf("Não foi possível abrir arquivo de entrada. \n");
                        return 1;
                    }

                    //le as linhas do arquivo
                    while(fgets(linha,121,fp)){
                          int num = sscanf(linha,"%d/%d/%s%f%f%f",&cod,&cp,n,&v1,&v2,&v3);
                          if(num>0){

                              dim[0]= v1;
                              dim[1]= v2;
                              dim[2]= v3;

                              f = (TFIG*)malloc(sizeof(TFIG));
                              f->cod = cod;
                              f->cod_pai = cp;
                              strcpy(f->nome,n);
                              f->dim[0] = dim[0];
                              f->dim[1] = dim[1];
                              f->dim[2] = dim[2];
                              g->cod = cp;

                              agen_insere(agen,g,f);
                          }
                    }
                    agen_imprime(agen,cb_imprime);

                    estrutura = 1;
                    if(destruida)destruida = 0;


                break;
            case 9:
                if(destruida){
                    printf("A estrutura já foi destruida. \n");
                }else{
                    if(estrutura == 1)agen_libera(agen,free);
                    if(estrutura == 2)abin_libera(abin,free);
                    if(estrutura == 3)Libera(a);


                    printf("Arvore Destruida\n");
                    destruida = 1;
                }

		        break;
		}

         int invalido = 1;
         while(invalido){

                 int teste = saida(leitura);
                 if(teste == 0 || teste < 0 || teste >10){
                    printf("Opção Inválida \n");

                 }else{
                    opcao = teste;
                    invalido = 0;
                 }
         }

 }





    if(!destruida){
        if(estrutura == 1)agen_libera(agen,free);
        if(estrutura == 2)abin_libera(abin,free);
        if(estrutura == 3)Libera(a);
    }
    return 0;
}
