
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
void __VERIFIER_Transaction_abort();

// void __VERIFIER_Transaction_begin() {};
// void __VERIFIER_Transaction_end() {};

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 
#define abort __VERIFIER_Transaction_abort()

#define N 2

char arr[10][10] = { "abc", "def" };

typedef struct {
    char str[10][10];
    int size;
} Database;

Database d;
_Atomic(Database *) db;

void initializeDatabase() {
    begin;
    sprintf(d.str[0], "%s",arr[0]);
    sprintf(d.str[1], "%s" ,arr[1]);
    d.size = 2;
    db = ATOMIC_VAR_INIT(&d);
    end;
}

void *modifyElement1(void *arg) {
      begin;
    Database *t = atomic_load_explicit(&db, memory_order_seq_cst);
    if(!t) {
      printf("Aborted \n");
      abort;
      return NULL;
    }
    if(t && t->str[0])
    printf("Thread 1 - Before: %s\n", t->str[0]);
    else
    printf("null1\n");
    if(t &&  t->str[1])
    sprintf(t->str[1], "%s" ,"thr1");
    else
    printf("null2\n");
    if(t && t->str[1])
    printf("Thread 1 - After: %s\n", t->str[1]);
    else
    printf("null3\n");
    sprintf(t->str[2], "%s" , "two");
     if(t)
    atomic_store_explicit(&db, t, memory_order_seq_cst);
    else
    printf("null4\n");
    end;
    return NULL;
}

void *modifyElement2(void *arg) {
       begin;
    Database *t = atomic_load_explicit(&db, memory_order_seq_cst);
    if(!t) {
      printf("Aborted \n");
      abort;
      return NULL;
    }
    if(t && t->str[1])
    printf("Thread 1 - Before: %s\n", t->str[1]);
    else
    printf("null1\n");
    if(t &&  t->str[0])
    sprintf(t->str[0], "%s" ,"thr1");
    else
    printf("null2\n");
    if(t && t->str[0])
    printf("Thread 1 - After: %s\n", t->str[0]);
    else
    printf("null3\n");
    sprintf(t->str[2], "%s" , "two");
     if(t)
    atomic_store_explicit(&db, t, memory_order_seq_cst);
    else
    printf("null4\n");
    end;
    return NULL;
}

int main() {
    initializeDatabase();

    pthread_t t1[N], t2[N];

      for(int i= 0 ; i < N ; i++){
            pthread_create(&t1[i], NULL, modifyElement1, NULL);
            pthread_create(&t2[i], NULL, modifyElement2, NULL);

      }
    
      for(int i= 0 ; i < N ; i++){
            pthread_join(t1[i], NULL);
            pthread_join(t2[i], NULL);
      }
    
    printf("------------finish------------\n");
    return 0;
}