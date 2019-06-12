
typedef struct  ArvBinNo TBNO;
typedef struct  ArvBin TAVL;

TAVL* avl_cria(int(*cb)(void* chave,void* info));
void avl_insere(TAVL* a, void* chave, void* info);

void* avl_busca(TAVL* a,void* chave);

void* avl_remover(TAVL* a,void* chave,void*(*cb_chave)(void* info));

void avl_libera(TAVL*a, void(*cb)(void*));
int avl_percorre(TAVL* a,int(*cb)(void* info, int dado),int dado);
int avl_percorre_gen(TAVL* a,int(*cb)(void* info, void* dado),void* dado);


struct ArvBinNo{
    void* info;
    TBNO*  esq;
    TBNO*  dir;
    int alt;
};

struct ArvBin{
	TBNO* raiz;
	int(*cmp)(void* chave,void* info);
};

TAVL* avl_cria(int(*cb)(void* chave,void* info)){
  TAVL* a = (TAVL*)malloc(sizeof(TAVL));
  a->raiz = NULL;
  a->cmp = cb;
  return a;
}


void bin_libera(TBNO* t){
    if( t != NULL ){
        bin_libera( t->esq );
        bin_libera( t->dir );
        free( t );
    }
}
void avl_libera(TAVL*a, void(*cb)(void*)){
	bin_libera(a->raiz);
}

TBNO* bin_busca(void* chave, TBNO* t,int(*cmp)(void* chave,void*info) ){
    if( t == NULL ) return NULL;
    if(cmp(chave,t->info)<0 ) return bin_busca( chave, t->esq,cmp );
    if( cmp(chave,t->info)>0 ) return bin_busca( chave, t->dir,cmp );
    return t->info;
}
void* avl_busca(TAVL* a,void* chave){
  return bin_busca(chave,a->raiz,a->cmp);
}

static int calc_alt( TBNO* n ){
    if( n == NULL ) return -1;
    return n->alt;
}


static int max( int l, int r){
    return l > r ? l: r;
}


static TBNO* rot_dir( TBNO* k2 ){
    TBNO* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = max( calc_alt( k2->esq ), calc_alt( k2->dir ) ) + 1;
    k1->alt = max( calc_alt( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}


static TBNO* rot_esq( TBNO* k1 ){
    TBNO* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = max( calc_alt( k1->esq ), calc_alt( k1->dir ) ) + 1;
    k2->alt = max( calc_alt( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}


static TBNO* rot_esq_dir( TBNO* k3 ){
    k3->esq = rot_esq( k3->esq );
    return rot_dir( k3 );
}


static TBNO* rot_dir_esq( TBNO* k1 ){
    k1->dir = rot_dir( k1->dir );
    return rot_esq( k1 );
}



static TBNO* bin_insere(TBNO* t ,void* chave,void* info,int(*cmp)(void* chave,void* info)){
    if( t == NULL ){
        t = (TBNO*)malloc(sizeof(TBNO));
        if( t == NULL ){
            fprintf (stderr, "Out of memory!!! (insere)\n");
            exit(1);
        }
        else{
            t->info = info;
            t->alt = 0;
            t->esq = t->dir = NULL;
            
        }
    }else if( cmp(chave,t->info)<0 ){
       
        t->esq = bin_insere( t->esq,chave,info,cmp );
        if( calc_alt( t->esq ) - calc_alt( t->dir ) == 2 ){
            if( cmp(chave,t->esq->info)<0 ){
                t = rot_dir( t );
            }else{
                t = rot_esq_dir( t );
            }
        }
                
    }else if( cmp(chave,t->info)>0 ){
        
        t->dir = bin_insere(t->dir, chave,info,cmp );
        if( calc_alt( t->dir ) - calc_alt( t->esq ) == 2 ){
            if( cmp(chave,t->dir->info)>0 ){
                t = rot_esq( t );
            }else{
              t = rot_dir_esq( t );
            }
        }
                
    }
    
    t->alt = max( calc_alt( t->esq ), calc_alt( t->dir ) ) + 1;
    return t;
}

void avl_insere(TAVL* a, void* chave, void* info){
   a->raiz = bin_insere(a->raiz,chave,info,a->cmp);
}





int calc_alt_retira(TBNO *T){
    int lh,rh;
    if(T==NULL) return(0);
    if(T->esq==NULL) lh=0;
    else lh=1+T->esq->alt;
    if(T->dir==NULL) rh=0;
    else rh=1+T->dir->alt;
    if(lh>rh) return(lh);
    return(rh);
}


int FB(TBNO *T){
    int lh,rh;
    if(T==NULL) return(0);
    if(T->esq==NULL) lh=0;
    else lh=1+T->esq->alt;
    if(T->dir==NULL) rh=0;
    else rh=1+T->dir->alt;
    return(lh-rh);
}






TBNO * bin_retira(void* chave, TBNO *T,int(*cmp)(void* chave,void*info),void*(*cb_chave)(void* info)){       
    TBNO *p;
    if(T==NULL)
        return NULL;
    else
        if( cmp(chave,T->info)>0){
            T->dir=bin_retira(chave,T->dir,cmp,cb_chave);
            if(FB(T)==2){
                if(FB(T->esq)>=0){
                    T=rot_dir(T);
                }
                else{
                    T=rot_esq_dir(T);
                }
            }
        }
        else
            if(cmp(chave,T->info)<0){
                    T->esq=bin_retira(chave,T->esq,cmp,cb_chave);
                    if(FB(T)==-2){
                        if(FB(T->dir)<=0){
                            T=rot_esq(T);
                        }
                        else{
                            T=rot_dir_esq(T);
                        }
                    }
            }
            else{
                //info to be deleted is found
                  if(T->esq != NULL){
                      p=T->esq;
                      while(p->dir != NULL) p=p->dir;

                      T->info=p->info;
		      int m =(int) cb_chave(p->info);

                      void* ch =  &m;
                  
                      T->esq=bin_retira(ch, T->esq,cmp,cb_chave);
                      if(FB(T)== -2){
                        if(FB(T->dir)<=0){
                            T=rot_esq(T);
                        }
                        else{
                            T=rot_dir_esq(T);
                        }
                      }
                  }
                  else{
                      TBNO *x = T;
                      T = T->dir;
                      free(x);
                      return(T);
                  }
            }
    T->alt=calc_alt_retira(T);
    return(T);
}

void* avl_remover(TAVL* a,void* chave,void*(*cb_chave)(void* info)){
  return bin_retira(chave,a->raiz,a->cmp,cb_chave);
}
static int min( int l, int r){
    return l < r ? l: r;
}

static int bin_percorre(TBNO* r,int(*cb)(void* info, int dado),int dado){
	if(r!=NULL){
		int s = bin_percorre(r->esq,cb,dado+1);
		if(s!=0)return s;
		s = cb(r->info,dado);
		if(s!=0)return s;
		return bin_percorre(r->dir,cb,dado+1);
	}
	return 0;
}
int avl_percorre(TAVL* a,int(*cb)(void* info, int dado),int dado){
  return bin_percorre(a->raiz,cb,dado);
}

static int bin_percorre_gen(TBNO* r,int(*cb)(void* info, void* dado),void* dado){
	if(r!=NULL){
		int s = bin_percorre_gen(r->esq,cb,dado);
		if(s!=0)return s;
		s = cb(r->info,dado);
		if(s!=0)return s;
		return bin_percorre_gen(r->dir,cb,dado);
	}
	return 0;
}
int avl_percorre_gen(TAVL* a,int(*cb)(void* info, void* dado),void* dado){
  return bin_percorre_gen(a->raiz,cb,dado);
}



