/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[5]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r4_0; 
atomic_int atom_3_r1_2; 
atomic_int atom_4_r1_2; 
atomic_int atom_4_r4_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v9_r4 = atomic_load_explicit(&vars[2+v6_r3], memory_order_seq_cst);
  int v40 = (v5_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v40, memory_order_seq_cst);
  int v41 = (v9_r4 == 0);
  atomic_store_explicit(&atom_1_r4_0, v41, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v12_r4 = v11_r3 ^ v11_r3;
  atomic_store_explicit(&vars[3+v12_r4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v14_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v15_r3 = v14_r1 ^ v14_r1;
  atomic_store_explicit(&vars[4+v15_r3], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[4], 2, memory_order_seq_cst);
  int v42 = (v14_r1 == 2);
  atomic_store_explicit(&atom_3_r1_2, v42, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v17_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v18_r3 = v17_r1 ^ v17_r1;
  int v21_r4 = atomic_load_explicit(&vars[0+v18_r3], memory_order_seq_cst);
  int v43 = (v17_r1 == 2);
  atomic_store_explicit(&atom_4_r1_2, v43, memory_order_seq_cst);
  int v44 = (v21_r4 == 0);
  atomic_store_explicit(&atom_4_r4_0, v44, memory_order_seq_cst);
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
  int v22 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v23 = (v22 == 2);
  int v24 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v25 = (v24 == 2);
  int v26 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v27 = (v26 == 2);
  int v28 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_r4_0, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_3_r1_2, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_4_r1_2, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_4_r4_0, memory_order_seq_cst);
  int v33_conj = v31 & v32;
  int v34_conj = v30 & v33_conj;
  int v35_conj = v29 & v34_conj;
  int v36_conj = v28 & v35_conj;
  int v37_conj = v27 & v36_conj;
  int v38_conj = v25 & v37_conj;
  int v39_conj = v23 & v38_conj;
  if (v39_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
