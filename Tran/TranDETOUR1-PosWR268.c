void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[4]; 
atomic_int atom_0_r5_0; 
atomic_int atom_1_r7_1; 
atomic_int atom_2_r5_0; 
atomic_int atom_3_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  int v6_r5 = atomic_load_explicit(&vars[1+v3_r4], memory_order_seq_cst);
  int v34 = (v6_r5 == 0);
  atomic_store_explicit(&atom_0_r5_0, v34, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v8_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r4 = v8_r3 ^ v8_r3;
  atomic_store_explicit(&vars[2+v9_r4], 1, memory_order_seq_cst);
  int v11_r7 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v35 = (v11_r7 == 1);
  atomic_store_explicit(&atom_1_r7_1, v35, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v13_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v14_r4 = v13_r3 ^ v13_r3;
  int v17_r5 = atomic_load_explicit(&vars[3+v14_r4], memory_order_seq_cst);
  int v36 = (v17_r5 == 0);
  atomic_store_explicit(&atom_2_r5_0, v36, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v19_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v20_r4 = v19_r3 ^ v19_r3;
  int v23_r5 = atomic_load_explicit(&vars[0+v20_r4], memory_order_seq_cst);
  int v37 = (v23_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v37, memory_order_seq_cst);
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

  int v24 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v25 = (v24 == 2);
  int v26 = atomic_load_explicit(&atom_0_r5_0, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_1_r7_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_2_r5_0, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_3_r5_0, memory_order_seq_cst);
  int v30_conj = v28 & v29;
  int v31_conj = v27 & v30_conj;
  int v32_conj = v26 & v31_conj;
  int v33_conj = v25 & v32_conj;
  if (v33_conj == 1) assert(0);
  return 0;
}
