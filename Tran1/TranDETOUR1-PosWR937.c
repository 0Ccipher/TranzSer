/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_2; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r8_0; 

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
  atomic_store_explicit(&vars[2+v6_r3], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v37 = (v5_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v8_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = v8_r1 ^ v8_r1;
  atomic_store_explicit(&vars[3+v9_r3], 1, memory_order_seq_cst);
  int v38 = (v8_r1 == 2);
  atomic_store_explicit(&atom_2_r1_2, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v11_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_r3 = v11_r1 ^ v11_r1;
  atomic_store_explicit(&vars[4+v12_r3], 1, memory_order_seq_cst);
  int v39 = (v11_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v39, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v14_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v15_r3 = v14_r1 ^ v14_r1;
  atomic_store_explicit(&vars[5+v15_r3], 1, memory_order_seq_cst);
  int v17_r6 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v18_r7 = v17_r6 ^ v17_r6;
  int v21_r8 = atomic_load_explicit(&vars[0+v18_r7], memory_order_seq_cst);
  int v40 = (v14_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v40, memory_order_seq_cst);
  int v41 = (v21_r8 == 0);
  atomic_store_explicit(&atom_4_r8_0, v41, memory_order_seq_cst);
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
  int v22 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v23 = (v22 == 2);
  int v24 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v25 = (v24 == 2);
  int v26 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_2_r1_2, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_4_r8_0, memory_order_seq_cst);
  int v31_conj = v29 & v30;
  int v32_conj = v28 & v31_conj;
  int v33_conj = v27 & v32_conj;
  int v34_conj = v26 & v33_conj;
  int v35_conj = v25 & v34_conj;
  int v36_conj = v23 & v35_conj;
  if (v36_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
