/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[3]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r5_1; 
atomic_int atom_2_r3_2; 
atomic_int atom_2_r6_1; 
atomic_int atom_3_r3_2; 
atomic_int atom_3_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v39 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v39, memory_order_seq_cst);
  int v40 = (v6_r5 == 1);
  atomic_store_explicit(&atom_1_r5_1, v40, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v8_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r4 = v8_r3 ^ v8_r3;
  int v10_r4 = v9_r4 + 1;
  atomic_store_explicit(&vars[2], v10_r4, memory_order_seq_cst);
  int v12_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v41 = (v8_r3 == 2);
  atomic_store_explicit(&atom_2_r3_2, v41, memory_order_seq_cst);
  int v42 = (v12_r6 == 1);
  atomic_store_explicit(&atom_2_r6_1, v42, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v15_r4 = v14_r3 ^ v14_r3;
  int v16_r4 = v15_r4 + 1;
  atomic_store_explicit(&vars[0], v16_r4, memory_order_seq_cst);
  int v18_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v43 = (v14_r3 == 2);
  atomic_store_explicit(&atom_3_r3_2, v43, memory_order_seq_cst);
  int v44 = (v18_r6 == 1);
  atomic_store_explicit(&atom_3_r6_1, v44, memory_order_seq_cst);
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

   int res = 0;
 begin;
  int v19 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v20 = (v19 == 2);
  int v21 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v22 = (v21 == 2);
  int v23 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v24 = (v23 == 2);
  int v25 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_1_r5_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_2_r3_2, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_2_r6_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_3_r3_2, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_3_r6_1, memory_order_seq_cst);
  int v31_conj = v29 & v30;
  int v32_conj = v28 & v31_conj;
  int v33_conj = v27 & v32_conj;
  int v34_conj = v26 & v33_conj;
  int v35_conj = v25 & v34_conj;
  int v36_conj = v24 & v35_conj;
  int v37_conj = v22 & v36_conj;
  int v38_conj = v20 & v37_conj;
  if (v38_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
