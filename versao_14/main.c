
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

      strcpy(novo->nome,f->nome);
      novo->dim[0] = f->dim[0];
      novo->dim[1] = f->dim[1];
      novo->dim[2] = f->dim[2];

      TABBB* abin = (TABBB*)dado;
      TFIG* chave = (TFIG*)malloc(sizeof(TFIG));
      chave->cod = f->cod;
      abin_insere(abin,chave,novo);
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

static int obterFloat(char*label, char* leitura,float* v1){

     int invalido = 1;
     while(invalido){

             printf("%s",label);
             scanf("%s", leitura);
             float teste = atof(leitura);
             if(teste <= 0){
                printf("Opção Inválida \n");

             }else{
                v1[0] = teste;
                invalido = 0;
             }
     }
     return 0;

}

static int obterInt(char*label, char* leitura,int* v1){

     int invalido = 1;
     while(invalido){

             printf("%s",label);
             scanf("%s", leitura);
             int teste = atoi(leitura);
             if(teste <= 0){
                printf("Opção Inválida \n");

             }else{
                v1[0] = teste;
                invalido = 0;
             }
     }
     return 0;

}

static void obter_dimensoes(char* n,float* dim,float*v1,char *leitura){
                    int invalido = 1;

                    if(strcmp(n,"QUA")==0){
                      obterFloat("Digite o Lado:\n",leitura,v1);
                      dim[0] = v1[0];
                    }
                    if(strcmp(n,"CIR")==0){
                      obterFloat("Digite o Raio:\n",leitura,v1);
                      dim[0] = v1[0];
                    }
                    if(strcmp(n,"TRI")==0){
                      obterFloat("Digite a Base:\n",leitura,v1);
                      dim[0] = v1[0];
                      obterFloat("Digite a Altura:\n",leitura,v1);
                      dim[1] = v1[0];
                    }
                    if(strcmp(n,"RET")==0){
                        obterFloat("Digite a Base:\n",leitura,v1);
                        dim[0] = v1[0];
                        obterFloat("Digite a Altura:\n",leitura,v1);
                        dim[1] = v1[0];
                    }

                    if(strcmp(n,"TRA")==0){
                        obterFloat("Digite a Base menor:\n",leitura,v1);
                        dim[0] = v1[0];
                        obterFloat("Digite a Base maior:\n",leitura,v1);
                        dim[1] = v1[0];
                        obterFloat("Digite a Altura:\n",leitura,v1);
                        dim[2] = v1[0];
                    }
}

static int saida(char* leitura,int* opcao){

     int invalido = 1;
     while(invalido){

             printf("\nEscolha uma opção do menu: \n");
             scanf("%s", leitura);
             int teste = atoi(leitura);
             if(teste == 0 || teste < 0 || teste >10){
                printf("Opção Inválida \n");

             }else{
                opcao[0] = teste;
                invalido = 0;
             }
     }

     return 0;

}

static int ler_arquivo(FILE* fp,TAG* agen){
     int cod,cp,cont = 0;
     char n[4];
     char linha[121];
     float v1 = -1;
     float v2 = -1;
     float v3 =-1;

     //le as linhas do arquivo
	while(fgets(linha,121,fp)){

          int num = sscanf(linha,"%d/%d/%s%f%f%f",&cod,&cp,n,&v1,&v2,&v3);
          if(num>0){
              TFIG* chave = (TFIG*)malloc(sizeof(TFIG));
              chave->cod = cod;
              if(agen_busca(agen, chave) == NULL){
                if(cp!=cod){
                   if(cod >=0){
                        if(cp>=0){
                                chave->cod = cp;
                                if(agen_busca(agen, chave) != NULL){
                                    if(strcmp(n,"QUA")==0 || strcmp(n,"CIR")==0 || strcmp(n,"TRI")==0 || strcmp(n,"RET")==0 || strcmp(n,"TRA")==0){
                                            int insere = 0;
                                            if(strcmp(n,"QUA")==0){
                                              if(v1 >= 0){
                                                insere = 1;
                                              }
                                            }
                                            if(strcmp(n,"CIR")==0){
                                              if(v1 >= 0){
                                                    insere = 1;
                                              }
                                            }
                                            if(strcmp(n,"TRI")==0){
                                              if(v1>=0 && v2>=0){
                                                insere = 1;
                                              }
                                            }
                                            if(strcmp(n,"RET")==0){
                                                if(v1>=0 && v2>=0){
                                                insere = 1;
                                              }
                                            }

                                            if(strcmp(n,"TRA")==0){
                                                if(v1>=0 && v2>=0 && v3 >=0){
                                                    insere = 1;
                                                }
                                            }

                                          if(insere){
                                                  TFIG* f = (TFIG*)malloc(sizeof(TFIG));
                                                  f->cod = cod;

                                                  strcpy(f->nome,n);
                                                  f->dim[0] = v1;
                                                  f->dim[1] = v2;
                                                  f->dim[2] = v3;
                                                  chave->cod = cp;
                                                  agen_insere(agen,chave,f);
                                                  cont++;
                                                  free(chave);
                                                  v1 = -1;
                                                  v2 = -1;
                                                  v3 = -1;
                                                  insere = 0;
                                        }
                                    }

                                }else{
                                    if(agen->raiz == NULL){

                                          TFIG* f = (TFIG*)malloc(sizeof(TFIG));
                                          f->cod = cod;
                                          strcpy(f->nome,n);
                                          f->dim[0] = v1;
                                          f->dim[1] = v2;
                                          f->dim[2] = v3;
                                          chave->cod = cp;
                                          agen_insere(agen,chave,f);
                                          cont++;
                                          free(chave);
                                          v1 = -1;
                                          v2 = -1;
                                          v3 = -1;
                                    }
                                }
                        }
                   }
                }

              }
          }
	}
    return cont;
}

int main()
{
    //necessario para leitura do arquivo
	char entrada[121];
	//char linha[121];
    //Estruturas
    TAG* agen = agen_cria(cmp_cod_figura);
    TABBB* abin;
    TAB* a ;
    TLG* l;
    TFIG* g;
    TFIG* f;
     //variaveis auxiliares
    int cod, cp,opcao_2,n_elementos = 0,destruida = 0, opcao = 25,estrutura = 1;
    char n[4],leitura[20];
    float v1,v2,v3;
    float dim[3];


    printf("Digite o nome do arquivo de entrada: \n");
    scanf("%120s",entrada);
	FILE* fp = fopen(entrada,"rt");

	if(fp==NULL){
		printf("Não foi possível abrir arquivo de entrada. \n");
		return 1;
	}

    n_elementos = ler_arquivo(fp,agen);
    printf("Arquivo com %d elementos lidos com sucesso.\n",n_elementos);
    //scanf("%s",leitura);

 //opcao do menu
 while(opcao!=10){

         menu();

		switch (opcao) {

		    case 1:
                if(destruida){
                    printf("A estrutura já foi destruida. \n");
                }else {
                        if(estrutura == 1){
                            agen_imprime(agen,cb_imprime);
                            int e = conta_nos(agen->raiz);
                            printf("#####   ARVORE TAG  ######\n");
                            printf("-----   %d elementos -----\n",e);
                            printf("##########################\n\n");
                        }
                        if(estrutura == 2)abin_imprime(abin,cb_imprime);
                        if(estrutura == 3){

                             int e = ab_conta_nos(a);
                             printf("#####   ARVORE TAB  ######\n\n");
                             printf("-----   %d elementos -----\n",e);
                             printf("##########################\n\n");
                             Imprime(a,0,cb_imprime);
                        }
                }

		        break;
            case 2:
		        if(destruida){
                    printf("A estrutura já foi destruida. \n");
		        }else{
                    obterInt("Digite o codigo da figura: \n",leitura,&cod);
                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                    if(estrutura == 1){
                        while(agen_busca(agen,g)==NULL){
                            obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                            g->cod = cod;
                        }
                        f = (TFIG*)agen_busca(agen,g);
                        imprime(f);
                    }
                    if(estrutura == 2){
                        while(abin_busca(abin,g)==NULL){
                            obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                            g->cod = cod;
                        }
                        f = (TFIG*)abin_busca(abin,g);
                        imprime(f);
                    }
                    if(estrutura == 3){
                        while(Busca(a, g,cmp_cod_figura) == NULL){
                            obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                            g->cod = cod;
                        }
                        buscar_chave(a,0,g,cmp_cod_figura,cb_fig);
                    }
                    free(g);
		        }
		        break;
		    case 3:
		        if(destruida){
                        printf("A estrutura já foi destruída.\n");
		        }else{

                        obterInt("Digite o codigo da figura: \n",leitura,&cod);



                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                    if(estrutura == 1){
                        while(agen_busca(agen, g) != NULL){
                            obterInt("Já existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                            g->cod = cod;
                        }
                        obterInt("Digite o codigo do Pai: \n",leitura,&cp);
                        g->cod = cp;
                        while(agen_busca(agen,g)==NULL || cp == cod){
                            if(cp==cod){
                                printf("O código do pai tem de ser diferente do código da figura.\n");
                            }else{
                                printf("Não existe figura com esse código\n");
                            }
                             obterInt("Digite o codigo do Pai: \n",leitura,&cp);
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

                        obter_dimensoes(n,dim,&v1,leitura);
                        f = (TFIG*)malloc(sizeof(TFIG));
                        f->cod = cod;

                        strcpy(f->nome,n);
                        f->dim[0] = dim[0];
                        f->dim[1] = dim[1];
                        f->dim[2] = dim[2];

                        agen_insere(agen,g,f);
                    }
                    if(estrutura == 2){
                        while(abin_busca(abin, g) != NULL){
                            obterInt("Já existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
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
                            obter_dimensoes(n,dim,&v1,leitura);

                            f = (TFIG*)malloc(sizeof(TFIG));
                            f->cod = cod;

                            strcpy(f->nome,n);
                            f->dim[0] = dim[0];
                            f->dim[1] = dim[1];
                            f->dim[2] = dim[2];
                            abin_insere(abin,g,f);

                    }
                    if(estrutura == 3){

                            while(Busca(a, g,cmp_cod_figura) != NULL){
                                obterInt("Já existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
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
                            obter_dimensoes(n,dim,&v1,leitura);



                            f = (TFIG*)malloc(sizeof(TFIG));
                            f->cod = cod;

                            strcpy(f->nome,n);
                            f->dim[0] = dim[0];
                            f->dim[1] = dim[1];
                            f->dim[2] = dim[2];

                              a = Insere(a,f,2,cmp_cod_figura);
                    }

                      free(g);
                      printf("Figura Inserida! \n");
		        }

		        break;
		    case 4:
		        if(destruida){
                    printf("A estrutura já foi destruída.\n");
		        }else{


                    obterInt("Digite o codigo da figura: \n",leitura,&cod);
                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                    if(estrutura == 1){
                        int verificar = 1;
                        TFIG* w = (TFIG*)agen->raiz->info;
                        int cod_raiz = w->cod;


                        while(verificar){
                            if(agen_busca(agen,g) == NULL){
                                obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                                 g->cod = cod;
                            }else{
                                if(cod == cod_raiz){
                                     printf("A raiz não pode ser removida.\n");
                                     obterInt("Digite o codigo da figura: \n",leitura,&cod);
                                     g->cod = cod;
                                }else{
                                    verificar = 0;
                                }
                            }
                        }
                        /*while(agen_busca(agen,g) == NULL){
                            obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                             g->cod = cod;
                        }

                        while(cod == cod_raiz){
                            printf("A raiz não pode ser removida.");
                            obterInt("Digite o codigo da figura: \n",leitura,&cod);
                             g->cod = cod;
                        }*/

                        int p_remover = 1;
                        opcao_2 = 3;
                        while(opcao_2>2){
                            obterInt("Escolha uma opção abaixo:\n1- Escolher Novo Pai\n2- Deixar o Programa escolher.\n",leitura,&opcao_2);
                        }
                        if(opcao_2 == 1){
                            obterInt("Digite o codigo do novo pai dos possíveis filhos.\n",leitura,&cp);
                            g->cod = cp;

                            while(p_remover){
                                    if(agen_busca(agen, g) == NULL){
                                            obterInt("Não existe figura com esse código. \nDigite o codigo do novo pai dos possíveis filhos ou digite -1 para o programa escolher o novo pai.\n",leitura,&cp);
                                            g->cod = cp;

                                    }else{
                                        f = (TFIG*)malloc(sizeof(TFIG));
                                        f->cod = cod;
                                        if(agen_eh_filho(agen, g, f)){
                                            printf("O novo pai não poder ser filho do elemento removido \n");
                                            obterInt("Digite o codigo do novo pai dos possíveis filhos.\n",leitura,&cp);
                                            g->cod = cp;
                                        }else{
                                            p_remover = 0;
                                        }
                                    }
                            }
                            f = (TFIG*)malloc(sizeof(TFIG));
                            f->cod = cod;
                            agen_remover_np(agen, f,g);
                        }
                        if(opcao_2 == 2){
                            g->cod = cod;
                            agen_remover(agen, g);
                        }

                    }
                    if(estrutura == 2){

                        while(abin_busca(abin, g) == NULL){

                                    obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                                    g->cod = cod;
                            }
                            abin_remover(abin,g);
                    }
                    if(estrutura == 3){

                        while(Busca(a, g,cmp_cod_figura) == NULL){
                            obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                            g->cod = cod;
                        }
                    retira(a,g,2,cmp_cod_figura);
                    }
                    free(g);
                    printf("Figura Removida! \n");
		        }
		        break;

		    case 5:
                if(destruida){
                    printf("A estrutura já foi destruída. \n");
                }else{

                    obterInt("Digite o codigo da figura: \n",leitura,&cod);
                    g = (TFIG*)malloc(sizeof(TFIG));
                    g->cod = cod;

                       if(estrutura == 1){
                            while(agen_busca(agen,g)==NULL){
                                obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                                g->cod = cod;
                            }
                            f = (TFIG*)agen_busca(agen,g);
                            imprime(f);
                            obter_dimensoes(f->nome,dim,&v1,leitura);

                                f->dim[0] = dim[0];
                                f->dim[1] = dim[1];
                                f->dim[2] = dim[2];
                       }
                       if(estrutura == 2){
                            while(abin_busca(abin,g)==NULL){
                                obterInt("Não existe figura com esse código. \nDigite o codigo da figura: \n",leitura,&cod);
                                g->cod = cod;
                            }
                            f = (TFIG*)abin_busca(abin,g);
                            imprime(f);
                            obter_dimensoes(f->nome,dim,&v1,leitura);

                                f->dim[0] = dim[0];
                                f->dim[1] = dim[1];
                                f->dim[2] = dim[2];

                       }
                       if(estrutura == 3){
                            //f = (TFIG*)malloc(sizeof(TFIG));
                            g->cod = cod;
                            buscar_chave(a,0,g,cmp_cod_figura,cb_fig);
                            f = (TFIG*)Busca_info(a,g,cmp_cod_figura);
                            printf("%s \n",f->nome);
                            obter_dimensoes(f->nome,dim,&v1,leitura);

                            f->dim[0] = dim[0];
                            f->dim[1] = dim[1];
                            f->dim[2] = dim[2];
                    }
                    free(g);
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
                        a  = Inicializa();
                        l = l_cria(cmp_cod_figura);
                        agen_percorre_gen(agen, cb_transformar_lista,l);

                        while(l->prim!= NULL){
                              f = (TFIG*)l_retira(l);

                              TFIG* novo = (TFIG*)malloc(sizeof(TFIG));
                              novo->cod = f->cod;

                              strcpy(novo->nome,f->nome);
                              novo->dim[0] = f->dim[0];
                              novo->dim[1] = f->dim[1];
                              novo->dim[2] = f->dim[2];

                              a = Insere(a,novo,2,cmp_cod_figura);
                              free(f);
                        }
                        int e = ab_conta_nos(a);
                        printf("#####   ARVORE TAB  ######\n\n");
                        printf("-----   %d elementos -----\n",e);
                        printf("##########################\n\n");
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
                    entrada[0]='\0';
                    printf("Digite o nome do arquivo de entrada: \n");
                    scanf("%120s",entrada);
                    fp = fopen("arquivo.txt","rt");
                    if(fp==NULL){
                        printf("Não foi possível abrir arquivo de entrada. \n");
                        return 1;
                    }
                    ler_arquivo(fp,agen);
                    printf("Arquivo com %d elementos lidos com sucesso.\n",n_elementos);

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

         saida(leitura,&opcao);

 }
    if(!destruida){
        if(estrutura == 1)agen_libera(agen,free);
        if(estrutura == 2)abin_libera(abin,free);
        if(estrutura == 3)Libera(a);
    }
    return 0;
}

