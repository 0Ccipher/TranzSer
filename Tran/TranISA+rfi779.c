void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r5_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v29 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v29, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v7_r3 = v6_r3 + 1;
  atomic_store_explicit(&vars[2], v7_r3, memory_order_seq_cst);
  int v30 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v30, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v9_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = v9_r1 ^ v9_r1;
  int v11_r3 = v10_r3 + 1;
  atomic_store_explicit(&vars[3], v11_r3, memory_order_seq_cst);
  int v31 = (v9_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v13_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  int v15_r3 = v14_r3 + 1;
  atomic_store_explicit(&vars[4], v15_r3, memory_order_seq_cst);
  int v17_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v18_r6 = v17_r5 ^ v17_r5;
  int v19_r6 = v18_r6 + 1;
  atomic_store_explicit(&vars[0], v19_r6, memory_order_seq_cst);
  int v32 = (v13_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v32, memory_order_seq_cst);
  int v33 = (v17_r5 == 1);
  atomic_store_explicit(&atom_3_r5_1, v33, memory_order_seq_cst);
    end;
return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);
  pthread_create(&thr3, NULL , t3, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);
  pthread_join(thr3,NULL);

  int v20 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_3_r5_1, memory_order_seq_cst);
  int v25_conj = v23 & v24;
  int v26_conj = v22 & v25_conj;
  int v27_conj = v21 & v26_conj;
  int v28_conj = v20 & v27_conj;
  if (v28_conj == 1) assert(0);
  return 0;
}
