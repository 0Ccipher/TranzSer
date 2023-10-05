/* Copyright (C) 2018 Magnus Lång and Tuan Phong Ngo
 * This benchmark is part of SWSC */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>

atomic_int vars[3]; 
atomic_int x,y,z;
void *t0(void *arg){
  atomic_store_explicit(&x, 2, memory_order_seq_cst);

  atomic_store_explicit(&y, 1, memory_order_seq_cst);
  return NULL;
}

void *t1(void *arg){
  atomic_store_explicit(&y, 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&y, memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&z, memory_order_seq_cst);
  atomic_store_explicit(&x, 1, memory_order_seq_cst);
  printf("y: %d , z: %d",v2_r3,v6_r5);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  // int v8 = atomic_load_explicit(&x, memory_order_seq_cst);
  // int v9 = (v8 == 2);
  // int v10 = atomic_load_explicit(&y, memory_order_seq_cst);
  // int v11 = (v10 == 2);
  // int v12_conj = v9 & v11;
  // if (v12_conj == 1) assert(0);
  printf("\n");
  return 0;
}
