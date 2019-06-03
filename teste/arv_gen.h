typedef struct  ArvGenNo TNO;
typedef struct  ArvGen TAG;

TAG* agen_cria(int(*cb)(void* chave,void* info));
void agen_insere(TAG* a, void* chave, void* info);
void* agen_busca(TAG* a,void* chave);

struct ArvGenNo{

	void*info;
	TNO* filho;
	TNO* irmao;

};

struct ArvGen{
	TNO* raiz;
	int(*cmp)(void* chave,void* info);
	
};

TAG* agen_cria(int(*cb)(void* chave,void* info)){
	TAG* a = (TAG*)malloc(sizeof(ArvGen));
	a->raiz = NULL;
	a->cmp = cb;
	return a;

}

static void insereNo(TNO* a,TNO* sa){
	sa->irmao = a->filho;
	a->filho = sa;
}


static TNO* insere(TNO* r,void* chave,void* info,int(*cmp)(void* chave,void* info)){
	if(r==NULL){
		r = (TNO*)malloc(sizeof(TNO));
		r->info = info;
		r->filho = r->irmao = NULL;
	}else{

    TNO* pai = busca(r,chave,info,cmp);
    TNO* filho = (TNO*)malloc(sizeof(TNO));
    filho->info = info;
		filho->filho = filho->irmao = NULL;

		insereNo(pai,filho);
	}
	return r;
}




void agen_insere(TAG* a, void* chave, void* info){
	//ArvGenNo* pai = (ArvGenNo*)busca(a->raiz,chave,a->cmp);
	insere(a->raiz,chave,info,a->cmp)	;
}


static void* busca(TNO* r,void* chave,int(*cmp)(void* chave, void* info)){
	if(r==NULL){
		 return NULL;
	}else{
		int c = cmp(chave,r->info);
		if(c==0)return r;
		else{
			for(TNO* p = r->filho;p!=NULL;p=p->irmao){
				TNO* q = busca(p,chave,cmp);
				if(q!=NULL)return q;
			}
			return NULL;
		}
	}
}

void* agen_busca(TAG* a,void* chave){
	return busca(a->raiz,chave,a->cmp);
}
