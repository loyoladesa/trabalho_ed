typedef struct arvgenno ArvGenNo;
typedef struct arvgen ArvGen;

ArvGen* agen_cria(int(*cb)(void* chave,void* info));
void agen_insere(ArvGen* a, void* chave, void* info);
void agen_insereNo(ArvGenNo* a,ArvGenNo* sa);

void* agen_busca(ArvGen* a,void* chave);

struct arvgenno{

	void*info;
	ArvGenNo* prim;
	ArvGenNo* prox;

};



struct arvgen{
	ArvGenNo* raiz;
	int(*cmp)(void* chave,void* info);
	
};

ArvGen* agen_cria(int(*cb)(void* chave,void* info)){
	ArvGen* a = (ArvGen*)malloc(sizeof(ArvGen));
	a->raiz = NULL;
	a->cmp = cb;
	return a;

}

/*
static ArvGenNo* insere(ArvGenNo* r,void* chave,void* info,int(*cmp)(void* chave,void* info)){
	if(r==NULL){
		r = (ArvGenNo*)malloc(sizeof(ArvGenNo));
		r->info = info;
		r->prim = r->prox = NULL;
	}else{
		int c = cmp(chave,r->info);
		if(c<0){
			r->prim = insere(r->prim,chave,info,cmp);
		}else{
			r->prox = insere(r->prox,chave,info,cmp);
		}
	}
	return r;
}
*/


void agen_insereNo(ArvGenNo* a,ArvGenNo* sa){
	sa->prox = a->prim;
	a->prim = sa;
}

void agen_insere(ArvGen* a, void* chave, void* info){
	//ArvGenNo* pai = (ArvGenNo*)busca(a->raiz,chave,a->cmp);
	ArvGenNo* pai = NULL;
	ArvGenNo* filho =(ArvGenNo*)malloc(sizeof(ArvGenNo));
	filho->info = info;
	filho->prim = filho->prox = NULL;

	if(pai == NULL){
		a->raiz = filho;
	}else{
		agen_insereNo(pai,filho);
	}
	
}


static void* busca(ArvGenNo* r,void* chave,int(*cmp)(void* chave, void* info)){
	if(r==NULL){
		 return NULL;
	}else{
		int c = cmp(chave,r->info);
		if(c==0)return r;
		else{
			for(ArvGenNo* p = r->prim;p!=NULL;p=p->prox){
				ArvGenNo* q = busca(p,chave,cmp);
				if(q!=NULL)return q;
			}
			return NULL;
		}
	}
}

void* agen_busca(ArvGen* a,void* chave){
	return busca(a->raiz,chave,a->cmp);
}

/*
static int percorre(ArvGenNo* r,int(*cb)(void* info, void* dado),void* dado){
	if(r!=NULL){
		int s = percorre(r->esq,cb,dado);
		if(s!=0)return s;
		s = cb(r->info,dado);
		if(s!=0)return s;
		return percorre(r->dir,cb,dado);
	}
	return 0;
}

int agen_percorre(ArvGen* a,int(*cb)(void* info,void* dado),void* dado){
	return percorre(a->raiz,cb,dado);
}



static void libera(ArvGenNo* r,void(*cb)(void*)){
	if(r!= NULL){
		libera(r->prim,cb);
		libera(r->prox,cb);
		cb(r->info);
		free(r);
	}
}

void agen_libera(ArvGen*a, void(*cb)(void*)){
	libera(a->raiz,cb);
	free(a);
}

*/


