#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst



#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;


void * thr1(void *arg){
    return NULL;
}
void * thr2(void *arg){
    return NULL;
}
void * thr3(void *arg){
    return NULL;
}

void * thr4(void *arg){
    return NULL;
}

int main() {
    pthread_t t1,t2,t3,t4;

    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);
    pthread_create(&t4,NULL,thr4,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
   // printf("----------------------------------------------\n");
    return 0;
}
