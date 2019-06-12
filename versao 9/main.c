/*
   Trabalho de Estrura de Dados 2019-1
	 Alunos:
	 				Sidney Loyola de Sá
				  Bruno Vínicios Cunha de Sá

	  O programa solicita o nome do arquivo a ser aberto.
		Após a leitura do arquivo a arvore generica esta montada e pronta para ser explorada pelo usuario através do menu.
		As seguintes funcionalidades foram implementadas:
		(a) buscar figuras geométricas, por meio de um código único; 
		(b) imprimir informações relevantes, tanto da árvore, quanto das figuras, incluindo-se sua área;
	  (c) inserir novas figuras; 
	  (d) retirar figuras, passando seus descendentes para outro pai; 
	  (e) destruir a árvore; e 
	  (f) alterar as dimensões de figuras;
    (g) transformar a árvore genérica numa árvore binária de busca balanceada, baseando-se no código único;
		(h) converter a árvore genérica numa árvore B, baseando-se no código único;

		OBSERVAÇÕES :
		1- Após conversão nas demais estruturas a nova estrutura fica valendo para a utilização do usuario.
		2 - A busca da figura quando utilizando a arvore b esta desabilitada, pois as figuras que ficam no nó raiz estao dando problema.
		3 - Na arvore AVL quando a raiz e removida, ocorre um bug.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arv_gen.h"
#include "figura.h"
#include "arv_avl.h"
#include "arv_b.h"
#include "lista.h"




static void menu(){
      printf("\e[H\e[2J");
      printf("\n###### MENU ###### \n");
      printf("Escolha uma opção abaixo: \n");
      printf("1 - BUSCAR FIGURA \n");
      printf("2 - IMPRIMIR ARVORE \n");
      printf("3 - INSERIR FIGURA \n");
      printf("4 - REMOVER FIGURA \n");
      printf("5 - DESTRUIR ARVORE \n");
      printf("6 - ALTERAR FIGURA \n");
      printf("7 - TRANSFORMAR EM ARVORE BINARIA BALANCEADA \n");
      printf("8 - TRANSFORMAR EM ARVORE B \n");
      printf("0 - SAIR\n");
}

static void saida(){
			char x='a';
			printf("Digite c para continuar\n");
			while(x!='c'){
				scanf("%c", &x);
			}
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
static int cb_imprime(void* info,int dado){
      TFIG* f = (TFIG*)info;
      
      int i;
      for (i = 0; i < dado; i++) printf("   ");
      printf("%d \n",f->cod);
      return 0;
}
static void* cb_chave(void* info){
      TFIG* f = (TFIG*)info;
      int c = f->cod;
      void* chave = &c;
      return chave;
}

static int cb_transformar(void* info,void* dado){
      TFIG* f = (TFIG*)info;
      TAVL* avl =(TAVL*)dado;
      int chave = f->cod;
      avl_insere(avl, &chave, f);
      return 0;
}

static int cb_transformarB(void* info,void* dado){
      TFIG* f = (TFIG*)info;
      TLG* a =(TLG*)dado;  
      int chave = f->cod;
      l_insere(a, f);
      return 0;
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

static void insere_figura_avl(TAVL* a,int cod,int cod_pai,char* nome,float d[3]){
        TFIG* f = (TFIG*)malloc(sizeof(TFIG));
        f->cod = cod;
        f->cod_pai = cod_pai;
        strcpy(f->nome,nome);
        f->dim[0] = d[0];
        f->dim[1] = d[1];
        f->dim[2] = d[2];
        void* chave = &f->cod;
        avl_insere(a,chave,f);
}

int main(void){

  //leitura do arquivo
	char entrada[121];
  printf("Digite o nome do arquivo de entrada: \n");
  scanf("%120s",entrada);
	FILE* fp = fopen(entrada,"rt");

	if(fp==NULL){
		printf("Não foi possível abrir arquivo de entrada. \n");
		return 1;
	}

	char linha[121];
		
  //cria as estruturas a serem utilizadas  
  TAG* a = agen_cria(cmp_cod_figura);
  TAVL* avl = avl_cria(cmp_cod_figura);
  TAB* arvB = Inicializa();
  TLG* l = l_cria(cmp_cod_figura);
	TFIG* f = (TFIG*)malloc(sizeof(TFIG));

  //le as linhas do arquivo
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

//variaveis auxiliares
int estrutura = 1, opcao = 1,destruida = 0;
int cod = 0,cp = 0;
char n[4];
float dim[3];
float v1,v2,v3;
     
//opcao do menu
while(opcao!=0){
          
		menu();
		scanf("%d", &opcao);
          

		switch (opcao) {
						case 1:
                      if(destruida == 0){
															printf("Digite o codigo da figura: \n");
														scanf("%d",&cod);

														if(estrutura == 1){
															while(agen_busca(a, &cod) == NULL){                      
																	nao_existe_figura(&cod);
															}
															f = (TFIG*)agen_busca(a, &cod);
															imprime(f);
														}
														if(estrutura == 2){
															while(avl_busca(avl, &cod) == NULL){                      
																	nao_existe_figura(&cod);
															}
															f = (TFIG*)avl_busca(avl, &cod);
															imprime(f);
														}
														/*
														if(estrutura == 3){
															while(Busca(arvB, cod) == NULL){                      
																	nao_existe_figura(&cod);
															}
															f = (TFIG*)Busca_info(arvB, cod);
															imprime(f);
														}
														*/
														
											}else{
													printf("Arvore foi Destruida\n");
											} 
											saida();
                      break;
              
            case 2:
                
											printf("\n\nARVORE  \n\n");
											if(destruida ==0){
														if(estrutura == 1)agen_percorre(a, cb_imprime, 1);
														if(estrutura == 2)avl_percorre(avl, cb_imprime, 1);
														if(estrutura == 3)Imprime(arvB, 0);
														
											}else{
													printf("Arvore foi Destruida\n");
											}                     
											saida();   
                break;
          		case 3:
                    if(destruida == 0){
													printf("Digite o codigo da figura: \n");
											scanf("%d",&cod);

											if(estrutura == 1){
														while(agen_busca(a, &cod) != NULL){
																ja_existe_figura(&cod);
													  }

													printf("Digite o codigo do Pai: \n");
													scanf("%d",&cp);

													while(agen_busca(a, &cp) == NULL || cp == cod || agen_eh_filho(a, &cod, &cp)){
														if(cp!=cod){
															printf("Não existe figura com esse código. \n");
														}else{
															printf("O código do pai tem de ser diferente do código da figura. \n");
														}
														printf("Digite o codigo do Pai: \n");
														scanf("%d",&cp);
													}
											}

											if(estrutura == 2){
														while(avl_busca(avl, &cod) != NULL){
																ja_existe_figura(&cod);
													}
											}
											if(estrutura == 3){
												while(Busca(arvB, cod) != NULL){                      
                            ja_existe_figura(&cod);
                        }
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
										if(estrutura == 1){
											insere_figura(a,cod,cp,n,dim);
										}
										if(estrutura == 2){
											insere_figura_avl(avl,cod,cp,n,dim);
										}
										if(estrutura == 3){
											TFIG* w = (TFIG*)malloc(sizeof(TFIG));
											w->cod = cod;
											w->cod_pai = cp;
											strcpy(w->nome,n);
											w->dim[0] = dim[0];
											w->dim[1] = dim[1];
											w->dim[2] = dim[2];
											
											arvB = Insere(arvB, w->cod, 2, w);
										}
										printf("Figura Inserida\n");                   

										
										}else{
											printf("Arvore foi Destruida\n");
										}
										saida();
                    break;

          case 4:
									if(destruida == 0){
																	printf("Digite o codigo da figura: \n");
														scanf("%d",&cod);

														if(estrutura == 1){
																	while(agen_busca(a, &cod) == NULL){
																			nao_existe_figura(&cod);
																}

																int p_remover = 1;
																
																printf("Digite o codigo do novo pai dos possíveis filhos ou digite 0 para o programa escolher o novo pai.\n");
																scanf("%d",&cp);
																
																while(p_remover){
																	if(cp == 0){
																		p_remover = 0;
																	}else{
																		if(agen_busca(a, &cp) == NULL){
																				printf("Não existe figura com esse código. \n");     
																				printf("Digite o codigo do novo pai dos possíveis filhos ou digite 0 para o programa escolher o novo pai.\n");
																				scanf("%d",&cp);
																				
																		}else{
																			if(agen_eh_filho(a, &cod, &cp)){
																				printf("O novo pai não poder ser filho do elemento removido \n");
																				printf("Digite o codigo do novo pai dos possíveis filhos ou digite c para continuar.\n");
																				scanf("%d",&cp);
																			}else{
																						p_remover = 0;
																			}
																		
																		}
																	}
																}

																if(cp==0){
																	agen_remover(a, &cod);
																}else{
																	agen_remover_np(a, &cod,&cp);
																}
														}

														if(estrutura == 2){
															while(avl_busca(avl, &cod) == NULL){
																		nao_existe_figura(&cod);
																}
																avl_remover(avl, &cod, cb_chave);
														}
														if(estrutura == 3){
															while(Busca(arvB, cod) == NULL){
																		nao_existe_figura(&cod);
																}
																retira(arvB, cod, 2);
														}
														printf("Figura Removida\n");
													
									}else{
													printf("Arvore foi Destruida\n");
									}                     
									saida();  
              

              break;
          case 5:
              if(destruida == 0){
										agen_libera(a,free);
										avl_libera(avl, free);
										Libera(arvB);
										printf("Arvore Destruida\n");
										destruida = 1;
							}else{
													printf("Arvore foi Destruida\n");
									}   
							
	            saida();
             break;  

          case 6:
							if(destruida == 0){
										printf("Digite o codigo da figura: \n");
										scanf("%d",&cod);

										if(estrutura == 1){
											while(agen_busca(a, &cod) == NULL){
													nao_existe_figura(&cod);
											}
											f = (TFIG*)agen_busca(a, &cod);
										}
										if(estrutura == 2){
											while(avl_busca(avl, &cod) == NULL){
													nao_existe_figura(&cod);
										}
										f = (TFIG*)avl_busca(avl, &cod);
										}
										if(estrutura == 3){
												while(Busca(arvB, cod) == NULL){                      
														nao_existe_figura(&cod);
												}
												f = (TFIG*)Busca_info(arvB, cod);
												imprime(f);
											}
										imprime(f);

										obter_dimensoes(f->nome,dim,&v1,&v2,&v3); 
										
										f->dim[0] = dim[0];
										f->dim[1] = dim[1];
										f->dim[2] = dim[2];
							}else{
													printf("Arvore foi Destruida\n");
									}   
							saida();
              break; 
        	case 7:
              if(destruida == 0){
									agen_percorre_gen(a, cb_transformar, avl);
									avl_percorre(avl, cb_imprime, 1);
									estrutura = 2;
							}
							else{
													printf("Arvore foi Destruida\n");
									}   
							saida();
          break;     

          case 8:
							if(destruida == 0){
									agen_percorre_gen(a, cb_transformarB,l);

									while(l->prim!= NULL){
										TFIG* f = (TFIG*)l_retira(l);
										arvB = Insere(arvB,f->cod,2,f);
									}
									printf("Arvore B\n\n");
									Imprime(arvB, 0);
									estrutura = 3;
							}
							else{
													printf("Arvore foi Destruida\n");
									}   
							saida();
          break;

          
          }   
    }
   
  if(destruida == 0){
		agen_libera(a,free);
		avl_libera(avl, free);
		Libera(arvB);
	}
	fclose(fp);	
  printf("FIM!");
	
	return 0;
	
}