void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[2]; 
atomic_int atom_0_r3_2; 
atomic_int atom_0_r7_1; 
atomic_int atom_1_r3_2; 
atomic_int atom_1_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  int v5_r7 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v25 = (v2_r3 == 2);
  atomic_store_explicit(&atom_0_r3_2, v25, memory_order_seq_cst);
  int v26 = (v5_r7 == 1);
  atomic_store_explicit(&atom_0_r7_1, v26, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r4 = v7_r3 ^ v7_r3;
  int v9_r4 = v8_r4 + 1;
  atomic_store_explicit(&vars[0], v9_r4, memory_order_seq_cst);
  int v11_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v27 = (v7_r3 == 2);
  atomic_store_explicit(&atom_1_r3_2, v27, memory_order_seq_cst);
  int v28 = (v11_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v28, memory_order_seq_cst);
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

  int v12 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v13 = (v12 == 2);
  int v14 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v15 = (v14 == 2);
  int v16 = atomic_load_explicit(&atom_0_r3_2, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_0_r7_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_1_r3_2, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v20_conj = v18 & v19;
  int v21_conj = v17 & v20_conj;
  int v22_conj = v16 & v21_conj;
  int v23_conj = v15 & v22_conj;
  int v24_conj = v13 & v23_conj;
  if (v24_conj == 1) assert(0);
  return 0;
}
