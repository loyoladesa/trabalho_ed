/* Teste de Histórico de Versões de arquivo no Github
    Escrita de bons commits  */


typedef struct listaNo TLNO;
typedef struct lista TLG;

struct listaNo {
  void* info;
  TLNO* prox;
};

struct lista{
  TLNO* prim;
  int(*cmp)(void* chave,void* info);
};


TLG* l_cria(int(*cb)(void* chave,void* info)){
	TLG* a = (TLG*)malloc(sizeof(TLG));
	a->prim = NULL;
	a->cmp = cb;
	return a;

}



void l_insere(TLG* l, void* info){

        TLNO* n = (TLNO*)malloc(sizeof(TLNO));
        n->info = info;
        n->prox = l->prim;
        l->prim = n;

}


int l_percorre(TLG* l,int(*cb)(void*info,void*dado),void*dado){
  for(TLNO* p = l->prim;p!=NULL;p=p->prox){
    int r = cb(p->info,dado);
    if(r!=0)return r;
  }
  return 0;
}

int l_imprime(TLG* l,int(*cb)(void*info,int dado),int dado){
  for(TLNO* p = l->prim;p!=NULL;p=p->prox){
    int r = cb(p->info,dado);
    if(r!=0)return r;
  }
  return 0;
}

void* l_retira(TLG* l){
  if (l == NULL)return NULL;
  TLNO* ant = NULL;
  TLNO* p = l->prim;

  l->prim = p->prox;
  return p->info;
}
void l_libera(TLG* l){
    TLNO* p = l->prim;
    while(p!=NULL){
        TLNO* t = p->prox;
        free(p);
        p = t;
    }
    free(l);

}
