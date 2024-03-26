void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[3]; 
atomic_int atom_0_r1_2; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_2; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v27 = (v2_r1 == 2);
  atomic_store_explicit(&atom_0_r1_2, v27, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  int v8_r3 = v7_r3 + 1;
  atomic_store_explicit(&vars[2], v8_r3, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v28 = (v6_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v28, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v10_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v11_r3 = v10_r1 ^ v10_r1;
  int v12_r3 = v11_r3 + 1;
  atomic_store_explicit(&vars[0], v12_r3, memory_order_seq_cst);
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v29 = (v10_r1 == 2);
  atomic_store_explicit(&atom_2_r1_2, v29, memory_order_seq_cst);
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

  int v13 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v14 = (v13 == 2);
  int v15 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v16 = (v15 == 2);
  int v17 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v18 = (v17 == 2);
  int v19 = atomic_load_explicit(&atom_0_r1_2, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_2_r1_2, memory_order_seq_cst);
  int v22_conj = v20 & v21;
  int v23_conj = v19 & v22_conj;
  int v24_conj = v18 & v23_conj;
  int v25_conj = v16 & v24_conj;
  int v26_conj = v14 & v25_conj;
  if (v26_conj == 1) assert(0);
  return 0;
}
