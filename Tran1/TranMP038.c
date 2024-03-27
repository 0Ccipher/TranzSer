/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_2_r4_0; 
atomic_int atom_3_r5_0; 
atomic_int atom_4_r3_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  atomic_store_explicit(&vars[2+v6_r3], 1, memory_order_seq_cst);
  int v33 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v8_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = v8_r1 ^ v8_r1;
  int v12_r4 = atomic_load_explicit(&vars[3+v9_r3], memory_order_seq_cst);
  int v34 = (v8_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v34, memory_order_seq_cst);
  int v35 = (v12_r4 == 0);
  atomic_store_explicit(&atom_2_r4_0, v35, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v15_r4 = v14_r3 ^ v14_r3;
  int v18_r5 = atomic_load_explicit(&vars[0+v15_r4], memory_order_seq_cst);
  int v36 = (v18_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v36, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v20_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v37 = (v20_r3 == 1);
  atomic_store_explicit(&atom_4_r3_1, v37, memory_order_seq_cst);
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
  int v23 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_2_r4_0, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_3_r5_0, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_4_r3_1, memory_order_seq_cst);
  int v28_conj = v26 & v27;
  int v29_conj = v25 & v28_conj;
  int v30_conj = v24 & v29_conj;
  int v31_conj = v23 & v30_conj;
  int v32_conj = v22 & v31_conj;
  if (v32_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
