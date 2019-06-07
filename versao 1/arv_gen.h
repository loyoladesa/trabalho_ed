typedef struct  ArvGenNo TNO;
typedef struct  ArvGen TAG;

TAG* agen_cria(int(*cb)(void* chave,void* info));

void agen_insere(TAG* a, void* chave, void* info);

void* agen_busca(TAG* a,void* chave);

void* agen_remover(TAG* a,void* chave);

void insereNo(TNO* pai,TNO* filho);

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
	TAG* a = (TAG*)malloc(sizeof(TAG));
	a->raiz = NULL;
	a->cmp = cb;
	return a;

}

TNO* busca_no(TNO* r,void* chave,int(*cmp)(void* chave,void*info)){
	if(r==NULL){
		 return NULL;
	}else{
    int c = cmp(chave,r->info);

		if(c==0)return r;
		else{
			for(TNO* p = r->filho;p!=NULL;p=p->irmao){
				TNO* q = busca_no(p,chave,cmp);
				if(q!=NULL)return q;
			}
			return NULL;
		}
	}
}


static TNO* insere(TNO* r,void* chave,void* info,int(*cmp)(void* chave,void* info)){
      TNO* filho = (TNO*)malloc(sizeof(TNO));
		  filho->info = info;
		  filho->filho = filho->irmao = NULL;

      if(r==NULL){
        r = filho;    
      }else{
          TNO* pai = busca_no(r,chave,cmp); 
          insereNo(filho,pai);
      } return r;
}




void agen_insere(TAG* a, void* chave, void* info){
	  a->raiz = insere(a->raiz,chave,info,a->cmp)	;
}
    

void* busca(TNO* r,void* chave,int(*cmp)(void* chave, void* info)){
	if(r==NULL){
		 return NULL;
	}else{
    int c = cmp(chave,r->info);

		if(c==0)return r->info;
		else{
			for(TNO* p = r->filho;p!=NULL;p=p->irmao){
				void* q = busca(p,chave,cmp);
				if(q!=NULL)return q;
			}
			return NULL;
		}
	}
}

void* agen_busca(TAG* a,void* chave){

    return busca(a->raiz,chave,a->cmp);   

}

void* remover(TNO* pai,TNO* r,void* chave,int(*cmp)(void* chave, void* info),int p){
  if(r==NULL)return NULL;
  else{
    int c = cmp(chave,r->info);
    if(c==0){
      TNO* removido = r;
      TNO* irmao = removido->irmao;
      TNO* filho = removido->filho;
      if(p==1)pai->irmao = irmao;
      if(p==0)pai->filho = NULL;
      if(irmao!=NULL){
        if(filho!=NULL){
            insereNo(filho,irmao);
            insereNo(irmao,pai);
        }
          
      }else{
          
          insereNo(filho,pai);
          //pai->filho = NULL;
      }
      return removido->info;
    }else{
        remover(r,r->filho,chave,cmp,0);
        remover(r,r->irmao,chave,cmp,1);  
        return NULL;    
    }
  }   
}

void* agen_remover(TAG* a,void* chave){
    if(a->raiz == NULL)return NULL;
    int c = a->cmp(chave,a->raiz->info);
    if(c==0)return NULL;
    return remover(a->raiz,a->raiz->filho,chave,a->cmp,0);
  
}

static int percorre(TNO* r,int(*cb)(void* info, int dado),int dado){
	if(r!=NULL){
		int s = percorre(r->filho,cb,dado+1);
		if(s!=0)return s;
		s = cb(r->info,dado);
		if(s!=0)return s;
		return percorre(r->irmao,cb,dado);
	}
	return 0;
}

int agen_percorre(TAG* a,int(*cb)(void* info,int dado),int dado){
	return percorre(a->raiz,cb,dado);
}

 void insereNo(TNO* filho,TNO* pai){
   TNO* q = NULL;
	for(TNO* p = pai->filho;p!=NULL;p=p->irmao){
				q = p;
	}
  if(q!=NULL){
    q->irmao = filho;
  }else{
    pai->filho = filho;
  }
  
  
}
