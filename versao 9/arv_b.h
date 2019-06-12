const int t = 2;

typedef struct  ArvB TAB;

struct ArvB{
  int nchaves, folha, *chave;
	void**info;
  TAB** filho;
};



TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(int*)malloc(sizeof(int*)*((t*2)-1));
	novo->info =(void**)malloc(sizeof(void*)*((t*2)-1));

  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*t*2);
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
	
  return novo;
}


TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
		free(a->info);
    free(a->filho);
    free(a);    
  }
  return NULL;
}


void Imprime(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->chave[i]);
    }
    Imprime(a->filho[i],andar+1);
  }
}


TAB *Busca(TAB* x, int ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]) i++;
  if(i < x->nchaves && ch == x->chave[i]) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch);
}

void *Busca_info(TAB* x, int ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]) i++;
  if(i < x->nchaves && ch == x->chave[i]) return x->info[i];
  if(x->folha) return resp;
  return Busca_info(x->filho[i], ch);
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
		z->info[j] = y->info[j+t];
	} 
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) {
		x->chave[j] = x->chave[j-1];
		x->info[j] = x->info[j-1];
	}
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
	x->info[i-1] = x->info[t-1];
  return x;
}


TAB *Insere_Nao_Completo(TAB *x, int k, int t,void* info){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k<x->chave[i])){
      x->chave[i+1] = x->chave[i];
			x->info[i+1] = x->info[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
		x->info[i+1] = info;
    return x;
  }
  while((i>=0) && (k<x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k>x->chave[i]) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t,info);
  return x;
}


TAB *Insere(TAB *T, int k, int t,void* info){
  if(Busca(T,k)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
		T->info[0] = info;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t,info);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t,info);
  return T;
}


TAB* remover(TAB* arv, int ch, int t){
  if(!arv) return arv;
  int i;
  
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(i < arv->nchaves && ch == arv->chave[i]){ 
    if(arv->folha){ 
     
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;      
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ 
      
      TAB *y = arv->filho[i];  
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t); 
    
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ 
      
      TAB *y = arv->filho[i+1];  
      while(!y->folha) y = y->filho[0];
      int temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); 
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
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;   
    }   
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ 
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ 
      printf("\nCASO 3A: i menor que nchaves\n");
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
      arv->filho[i] = remover(arv->filho[i], ch, t);
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
      arv->filho[i] = remover(y, ch, t);
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
        arv = remover(arv, ch, t);
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
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, int k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
}
