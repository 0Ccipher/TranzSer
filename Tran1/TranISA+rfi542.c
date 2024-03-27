/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[5]; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r5_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r6_1; 

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
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v35 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v35, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v7_r3 = v6_r3 + 1;
  atomic_store_explicit(&vars[2], v7_r3, memory_order_seq_cst);
  int v36 = (v5_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v36, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v9_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = v9_r1 ^ v9_r1;
  int v11_r3 = v10_r3 + 1;
  atomic_store_explicit(&vars[3], v11_r3, memory_order_seq_cst);
  int v13_r5 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r6 = v13_r5 ^ v13_r5;
  int v15_r6 = v14_r6 + 1;
  atomic_store_explicit(&vars[4], v15_r6, memory_order_seq_cst);
  int v37 = (v9_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v37, memory_order_seq_cst);
  int v38 = (v13_r5 == 1);
  atomic_store_explicit(&atom_3_r5_1, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v17_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v18_r3 = v17_r1 ^ v17_r1;
  atomic_store_explicit(&vars[0+v18_r3], 1, memory_order_seq_cst);
  int v20_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v39 = (v17_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v39, memory_order_seq_cst);
  int v40 = (v20_r6 == 1);
  atomic_store_explicit(&atom_4_r6_1, v40, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 
  pthread_t thr4; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);
  pthread_create(&thr3, NULL , t3, NULL);
  pthread_create(&thr4, NULL , t4, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);
  pthread_join(thr3,NULL);
  pthread_join(thr4,NULL);

   int res = 0;
 begin;
  int v21 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v22 = (v21 == 2);
  int v23 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_3_r5_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_4_r6_1, memory_order_seq_cst);
  int v29_conj = v27 & v28;
  int v30_conj = v26 & v29_conj;
  int v31_conj = v25 & v30_conj;
  int v32_conj = v24 & v31_conj;
  int v33_conj = v23 & v32_conj;
  int v34_conj = v22 & v33_conj;
  if (v34_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
