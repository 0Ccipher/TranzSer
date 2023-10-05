#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>

atomic_int x,y,z;

void *t0(void *arg){
  atomic_store_explicit(&x, 2, memory_order_seq_cst);
  // printf(" x1 ");
  int v2_r3 = atomic_load_explicit(&y, memory_order_seq_cst);
  // printf(" Rx1: %d\t",v2_r3);
  return NULL;
}

void *t1(void *arg){
  atomic_store_explicit(&y, 1, memory_order_seq_cst);
  // printf(" y2 ");
//   atomic_store_explicit(&y, 3, memory_order_seq_cst);
  atomic_store_explicit(&x, 1, memory_order_seq_cst);
  // printf(" x2 ");
  int v4_r6 = atomic_load_explicit(&x, memory_order_seq_cst);
  // printf(" Rx2: %d\t",v4_r6);
  return NULL;
}

void *t2(void *arg){
  int v6_r1 = atomic_load_explicit(&y, memory_order_seq_cst);
  // printf(" Ry3: %d\t",v6_r1);
  atomic_store_explicit(&y, 2, memory_order_seq_cst);
  // printf(" y3 ");
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  
  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  printf("End\n");
  return 0;
}
