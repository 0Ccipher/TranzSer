/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_0_r1_1; 
atomic_int atom_0_r6_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r5_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v5_r6 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r7 = v5_r6 ^ v5_r6;
  int v7_r7 = v6_r7 + 1;
  atomic_store_explicit(&vars[2], v7_r7, memory_order_seq_cst);
  int v22 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v22, memory_order_seq_cst);
  int v23 = (v5_r6 == 1);
  atomic_store_explicit(&atom_0_r6_1, v23, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v9_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = v9_r1 ^ v9_r1;
  int v11_r3 = v10_r3 + 1;
  atomic_store_explicit(&vars[3], v11_r3, memory_order_seq_cst);
  int v13_r5 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r6 = v13_r5 ^ v13_r5;
  atomic_store_explicit(&vars[0+v14_r6], 1, memory_order_seq_cst);
  int v24 = (v9_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v24, memory_order_seq_cst);
  int v25 = (v13_r5 == 1);
  atomic_store_explicit(&atom_1_r5_1, v25, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);

   int res = 0;
 begin;
  int v15 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v16 = atomic_load_explicit(&atom_0_r6_1, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_1_r5_1, memory_order_seq_cst);
  int v19_conj = v17 & v18;
  int v20_conj = v16 & v19_conj;
  int v21_conj = v15 & v20_conj;
  if (v21_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
