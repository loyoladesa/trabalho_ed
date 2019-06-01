typedef struct arvn Arvn;
typedef struct arvnno ArvnNo;
ArvnNo* arvn_criano(int c,int cp,char* n,float* d);
void arvn_insere(ArvnNo* a,ArvnNo* sa);
Arvn* arvn_cria(ArvnNo* r);
void arvn_imprime(Arvn* a);
ArvnNo* arvn_busca(Arvn* a,int c);
void arvn_libera(Arvn*a);

/*
'/': código único, código único do pai (sendo que a raiz tem código do pai igual a zero) e as figuras geométricas, incluindo seu nome;
as dimensões das figuras geométricas obedecerão ao seguinte padrão:
 (a) se a figura for um círculo ou um quadrado, uma única dimensão será informada (ou o raio, ou o lado, respectivamente);
 (b) se a figura for um triângulo ou um retângulo, as duas dimensões informadas serão a base e a altura; e, por fim, 
 (c) se a figura for um trapézio, três dimensões serão informadas, nessa ordem, base menor, base maior e altura;

 Ex:    1/0/TRI 3 2
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

struct arvnno{
  int cod;
  int cod_pai;
  char nome[121];			
  float dim[3];
  ArvnNo* prim;
  ArvnNo* prox;
};

struct arvn{
  ArvnNo* raiz;
};

ArvnNo* arvn_criano(int c,int cp,char* n,float* d){

	ArvnNo* a = (ArvnNo*)malloc(sizeof(ArvnNo));
	a->cod = c;
	a->cod_pai = cp;
	strcpy(a->nome,n);
	for(int i=0;i<3;i++){
		a->dim[i] = d[i];
	}
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

void arvn_insere(ArvnNo* a, ArvnNo* sa){
	sa->prox = a->prim;
	a->prim =sa;
}

Arvn* arvn_cria(ArvnNo* r){
	Arvn* a = (Arvn*)malloc(sizeof(Arvn));
	a->raiz = r;
	return a;
}

static void imprime(ArvnNo* r){

  printf("<%c",r->cod);
  for(ArvnNo* p = r->prim;p!=NULL;p=p->prox){
    imprime(p);
    printf(">");

  }
}

void arvn_imprime(Arvn* a){
  if(a->raiz!=NULL)
  imprime(a->raiz);
}

static ArvnNo* busca(ArvnNo* r, int c){
  if(r->cod == c)return r;
  else{
    for(ArvnNo* p = r->prim;p!= NULL; p=p->prox){
      ArvnNo* q = busca(p,c);
      if(q!=NULL)return q;
    }
    return NULL;
  }
}

ArvnNo* arvn_busca(Arvn*a,int c){
  if(a->raiz == NULL){
    return NULL;
  }else{
    return busca(a->raiz,c);
  }
}

static void libera(ArvnNo* r){
  ArvnNo* p = r->prim;
  while(p!=NULL){
    ArvnNo* t = p->prox;
    libera(p);
    p = t;
  }
  free(r);
}

void arvn_libera(Arvn* a){
  if(a->raiz!=NULL)
  libera(a->raiz);
  free(a);
}

static int altura(ArvnNo* r){
	int hmax = -1;
	for(ArvnNo* p=r->prim;p!=NULL;p=p->prox){
		int h = altura(p);
		if(h>hmax)
		hmax = h;
	}

	return hmax+1;
}

int arvn_altura(Arvn* a){
	if(a->raiz == NULL){
		return -1;
	}else{
		return altura(a->raiz);
	}
}
