/* Copyright (C) 2018 Magnus Lång and Tuan Phong Ngo
 * This benchmark is part of SWSC */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

// atomic_int vars[2]; 
atomic_int x,y,z;
atomic_int atom_2_r4_3; 
atomic_int atom_2_r1_1; 

void *t0(void *arg){
  atomic_store_explicit(&x, 4, memory_order_seq_cst);
  atomic_store_explicit(&y, 1, memory_order_seq_cst);
  return NULL;
}

void *t1(void *arg){
  atomic_store_explicit(&y, 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&x, memory_order_seq_cst);
  atomic_store_explicit(&x, 1, memory_order_seq_cst);
//   atomic_store_explicit(&x, 3, memory_order_seq_cst);
  return NULL;
}

void *t2(void *arg){
  int v4_r1 = atomic_load_explicit(&x, memory_order_seq_cst);
  atomic_store_explicit(&x, 2, memory_order_seq_cst);
//   int v6_r4 = atomic_load_explicit(&x, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

//   atomic_init(&y, 0);
//   atomic_init(&x, 0);
//   atomic_init(&atom_2_r4_3, 0);
//   atomic_init(&atom_2_r1_1, 0);

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

//   int v7 = atomic_load_explicit(&y, memory_order_seq_cst);
//   int v8 = (v7 == 2);
//   int v9 = atomic_load_explicit(&x, memory_order_seq_cst);
//   int v10 = (v9 == 4);
//   int v11 = atomic_load_explicit(&atom_2_r4_3, memory_order_seq_cst);
//   int v12 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
//   int v13_conj = v11 & v12;
//   int v14_conj = v10 & v13_conj;
//   int v15_conj = v8 & v14_conj;
//   if (v15_conj == 1) assert(0);
//   return 0;
}
