/* file: minunit.h */
 #define mu_assert(message, test)  do { if (!(test)) return message;   } while (0)

 #define mu_run_test(test)  do {  char *message = test();    tests_run++;   if (message) return message;     } while (0)
 extern int tests_run;

void esperava_int(int ve,int vr);
void esperava_string(char* ve,char* vr);

void esperava_int(int ve,int vr){
  printf("Valor Esperado = %d , Valor Real = %d. \n",ve,vr);
}


void esperava_string(char* ve,char* vr){
  printf("Valor Esperado = %s , Valor Real = %s. \n",ve,vr);
}