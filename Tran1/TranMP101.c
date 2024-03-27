/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[3]; 
atomic_int atom_0_r7_1; 
atomic_int atom_1_r7_1; 
atomic_int atom_2_r7_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  int v5_r7 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v30 = (v5_r7 == 1);
  atomic_store_explicit(&atom_0_r7_1, v30, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r4 = v7_r3 ^ v7_r3;
  atomic_store_explicit(&vars[2+v8_r4], 1, memory_order_seq_cst);
  int v10_r7 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v31 = (v10_r7 == 1);
  atomic_store_explicit(&atom_1_r7_1, v31, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r4 = v12_r3 ^ v12_r3;
  atomic_store_explicit(&vars[0+v13_r4], 1, memory_order_seq_cst);
  int v15_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v32 = (v15_r7 == 1);
  atomic_store_explicit(&atom_2_r7_1, v32, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);

   int res = 0;
 begin;
  int v16 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v17 = (v16 == 2);
  int v18 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v19 = (v18 == 2);
  int v20 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v21 = (v20 == 2);
  int v22 = atomic_load_explicit(&atom_0_r7_1, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_1_r7_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_2_r7_1, memory_order_seq_cst);
  int v25_conj = v23 & v24;
  int v26_conj = v22 & v25_conj;
  int v27_conj = v21 & v26_conj;
  int v28_conj = v19 & v27_conj;
  int v29_conj = v17 & v28_conj;
  if (v29_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
