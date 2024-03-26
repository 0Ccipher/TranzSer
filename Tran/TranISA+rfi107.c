void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[4]; 
atomic_int atom_0_r3_2; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_2_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  int v4_r4 = v3_r4 + 1;
  atomic_store_explicit(&vars[1], v4_r4, memory_order_seq_cst);
  int v29 = (v2_r3 == 2);
  atomic_store_explicit(&atom_0_r3_2, v29, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  atomic_store_explicit(&vars[2+v7_r3], 1, memory_order_seq_cst);
  int v9_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r7 = v9_r6 ^ v9_r6;
  int v11_r7 = v10_r7 + 1;
  atomic_store_explicit(&vars[3], v11_r7, memory_order_seq_cst);
  int v30 = (v6_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v30, memory_order_seq_cst);
  int v31 = (v9_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v13_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  atomic_store_explicit(&vars[0+v14_r3], 1, memory_order_seq_cst);
  int v16_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v32 = (v13_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v32, memory_order_seq_cst);
  int v33 = (v16_r6 == 1);
  atomic_store_explicit(&atom_2_r6_1, v33, memory_order_seq_cst);
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

  int v17 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v18 = (v17 == 2);
  int v19 = atomic_load_explicit(&atom_0_r3_2, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_2_r6_1, memory_order_seq_cst);
  int v24_conj = v22 & v23;
  int v25_conj = v21 & v24_conj;
  int v26_conj = v20 & v25_conj;
  int v27_conj = v19 & v26_conj;
  int v28_conj = v18 & v27_conj;
  if (v28_conj == 1) assert(0);
  return 0;
}
