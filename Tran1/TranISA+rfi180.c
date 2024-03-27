/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_0_r3_2; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r5_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  int v18 = (v2_r3 == 2);
  atomic_store_explicit(&atom_0_r3_2, v18, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v7_r3 = v6_r3 + 1;
  atomic_store_explicit(&vars[0], v7_r3, memory_order_seq_cst);
  int v9_r5 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v19 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v19, memory_order_seq_cst);
  int v20 = (v9_r5 == 1);
  atomic_store_explicit(&atom_1_r5_1, v20, memory_order_seq_cst);
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
  int v10 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v11 = (v10 == 2);
  int v12 = atomic_load_explicit(&atom_0_r3_2, memory_order_seq_cst);
  int v13 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v14 = atomic_load_explicit(&atom_1_r5_1, memory_order_seq_cst);
  int v15_conj = v13 & v14;
  int v16_conj = v12 & v15_conj;
  int v17_conj = v11 & v16_conj;
  if (v17_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
