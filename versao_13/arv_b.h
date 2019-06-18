const int t = 2;
typedef struct ArvB TAB;

struct ArvB
{
  int nchaves, folha;
  void **chave;
  TAB **filho;
};


TAB *
Cria (int t)
{
  TAB *novo = (TAB *) malloc (sizeof (TAB));
  novo->folha = 1;
  novo->nchaves = 0;
  novo->chave = (void **) malloc (sizeof (void *) * ((t * 2) - 1));

  novo->filho = (TAB **) malloc (sizeof (TAB *) * t * 2);

  int i;
  for (i = 0; i < (t * 2); i++)
    novo->filho[i] = NULL;

  return novo;
}

TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
	free(a->filho);
    free(a);
  }
  return NULL;
}

int ab_conta_nos (TAB* a) {
    if(a){
        int i,j,contu,contf=0;

        for(i=0; i<=a->nchaves-1; i++){
          contf = contf + ab_conta_nos(a->filho[i])+1;
        }
        contu = ab_conta_nos(a->filho[i]);
        return contf+contu;
    }return 0;
}

void Imprime(TAB *a, int andar,int(*cb)(void* info)){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1,cb);
      for(j=0; j<=andar; j++) printf("   ");
      int s = cb(a->chave[i]);
    }
    Imprime(a->filho[i],andar+1,cb);
  }
}



void buscar_chave(TAB *a,int andar,void*ch,int(*cmp)(void*chave,void*info),int(*cb)(void* info)){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      buscar_chave(a->filho[i],andar+1,ch,cmp,cb);
      if(cmp(ch,a->chave[i])==0) {
          int s = cb(a->chave[i]);

      }

    }
    buscar_chave(a->filho[i],andar+1,ch,cmp,cb);
  }
}

TAB *Busca(TAB* x, void* ch, int(*cmp)(void*chave,void*info)){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && cmp(ch,x->chave[i])>0) i++;
  if(i < x->nchaves && cmp(ch,x->chave[i])==0) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch,cmp);
}

void *Busca_info(TAB* x, void* ch, int(*cmp)(void*chave,void*info)){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && cmp(ch,x->chave[i])>0) i++;
  if(i < x->nchaves && cmp(ch,x->chave[i])==0) return x->chave[i];
  if(x->folha) return resp;
  return Busca_info(x->filho[i], ch,cmp);
}

TAB *Inicializa(){
  return NULL;
}

TAB *Divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++){
		z->chave[j] = y->chave[j+t];
  }
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--){
   x->filho[j+1]=x->filho[j];
   }
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) {
		x->chave[j] = x->chave[j-1];

	}
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}

TAB *Insere_Nao_Completo(TAB *x, void*ch, int t,int(*cmp)(void*chave,void*info)){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (cmp(ch,x->chave[i])<0)){

      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = ch;
    x->nchaves++;

    return x;
  }
  while((i>=0) && (cmp(ch,x->chave[i])<0)) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(cmp(ch,x->chave[i])>0) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], ch, t,cmp);
  return x;
}

TAB *Insere(TAB *T, void*ch, int t,int(*cmp)(void*chave,void*info)){
  if(Busca(T,ch,cmp)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = ch;
    T->nchaves=1;

    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,ch,t,cmp);
    return S;
  }
  T = Insere_Nao_Completo(T,ch,t,cmp);
  return T;
}

TAB* remover(TAB* arv, void* ch, int t, int(*cmp)(void*chave,void*info)){
  if(!arv) return arv;
  int i;


  for(i = 0; i<arv->nchaves && cmp(arv->chave[i],ch)<0; i++);

  if(i < arv->nchaves && cmp(ch,arv->chave[i])==0){
    if(arv->folha){

      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){

      TAB *y = arv->filho[i];
      while(!y->folha) y = y->filho[y->nchaves];
      void* temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t,cmp);

      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){

      TAB *y = arv->filho[i+1];
      while(!y->folha) y = y->filho[0];
      void* temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t,cmp);
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C

      TAB *y = arv->filho[i];
      TAB *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;
      int j;
      for(j=0; j<t-1; j++)
        y->chave[t+j] = z->chave[j];
      for(j=0; j<=t; j++)
        y->filho[t+j] = z->filho[j];
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j <= arv->nchaves; j++)
        arv->filho[j] = arv->filho[j+1];
      arv->filho[j] = NULL;
      arv->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t,cmp);
      return arv;
    }
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){

      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];
      y->nchaves++;
      arv->chave[i] = z->chave[0];
      int j;
      for(j=0; j < z->nchaves-1; j++)
        z->chave[j] = z->chave[j+1];

      y->filho[y->nchaves] = z->filho[0];
      for(j=0; j < z->nchaves; j++)
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t,cmp);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){

      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];
      y->filho[0] = z->filho[z->nchaves];
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t,cmp);
      return arv;
    }
    if(!z){
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){

        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t,cmp);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){

        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1];
        else
          z->chave[t-1] = arv->chave[i];
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t,cmp);
        return arv;
      }
    }
  }
  arv->filho[i] = remover(arv->filho[i], ch, t,cmp);
  return arv;
}


TAB* retira(TAB* arv, void* k, int t,int(*cmp)(void*chave,void*info)){
  if(!arv || !Busca(arv, k,cmp)) return arv;
  return remover(arv, k, t,cmp);
}

