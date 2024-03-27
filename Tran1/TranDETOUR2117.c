/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r5_1; 
atomic_int atom_2_r6_1; 
atomic_int atom_3_r5_0; 
atomic_int atom_4_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
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
  int v40 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v40, memory_order_seq_cst);
  int v41 = (v6_r5 == 1);
  atomic_store_explicit(&atom_1_r5_1, v41, memory_order_seq_cst);
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
  int v18_r5 = atomic_load_explicit(&vars[3+v15_r4], memory_order_seq_cst);
  int v43 = (v18_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v43, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v20_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v21_r4 = v20_r3 ^ v20_r3;
  int v24_r5 = atomic_load_explicit(&vars[0+v21_r4], memory_order_seq_cst);
  int v44 = (v24_r5 == 0);
  atomic_store_explicit(&atom_4_r5_0, v44, memory_order_seq_cst);
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
  int v25 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v26 = (v25 == 2);
  int v27 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v28 = (v27 == 2);
  int v29 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_1_r5_1, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_2_r6_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_3_r5_0, memory_order_seq_cst);
  int v33 = atomic_load_explicit(&atom_4_r5_0, memory_order_seq_cst);
  int v34_conj = v32 & v33;
  int v35_conj = v31 & v34_conj;
  int v36_conj = v30 & v35_conj;
  int v37_conj = v29 & v36_conj;
  int v38_conj = v28 & v37_conj;
  int v39_conj = v26 & v38_conj;
  if (v39_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
