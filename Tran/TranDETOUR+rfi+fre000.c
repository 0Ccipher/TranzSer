void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[2]; 
atomic_int atom_0_r3_1; 
atomic_int atom_1_r5_0; 
atomic_int atom_2_r3_1; 
atomic_int atom_3_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v30 = (v2_r3 == 1);
  atomic_store_explicit(&atom_0_r3_1, v30, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_r4 = v4_r3 ^ v4_r3;
  int v8_r5 = atomic_load_explicit(&vars[1+v5_r4], memory_order_seq_cst);
  int v31 = (v8_r5 == 0);
  atomic_store_explicit(&atom_1_r5_0, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v32 = (v10_r3 == 1);
  atomic_store_explicit(&atom_2_r3_1, v32, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v13_r4 = v12_r3 ^ v12_r3;
  int v16_r5 = atomic_load_explicit(&vars[0+v13_r4], memory_order_seq_cst);
  int v33 = (v16_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v33, memory_order_seq_cst);
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

  int v17 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v18 = (v17 == 2);
  int v19 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v20 = (v19 == 2);
  int v21 = atomic_load_explicit(&atom_0_r3_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_1_r5_0, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_2_r3_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_3_r5_0, memory_order_seq_cst);
  int v25_conj = v23 & v24;
  int v26_conj = v22 & v25_conj;
  int v27_conj = v21 & v26_conj;
  int v28_conj = v20 & v27_conj;
  int v29_conj = v18 & v28_conj;
  if (v29_conj == 1) assert(0);
  return 0;
}
