/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_0_r3_2; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_2_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  int v27 = (v2_r3 == 2);
  atomic_store_explicit(&atom_0_r3_2, v27, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  atomic_store_explicit(&vars[2+v6_r3], 1, memory_order_seq_cst);
  int v8_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r7 = v8_r6 ^ v8_r6;
  atomic_store_explicit(&vars[3+v9_r7], 1, memory_order_seq_cst);
  int v28 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v28, memory_order_seq_cst);
  int v29 = (v8_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v29, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v11_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_r3 = v11_r1 ^ v11_r1;
  atomic_store_explicit(&vars[0+v12_r3], 1, memory_order_seq_cst);
  int v14_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v30 = (v11_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v30, memory_order_seq_cst);
  int v31 = (v14_r6 == 1);
  atomic_store_explicit(&atom_2_r6_1, v31, memory_order_seq_cst);
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

   int res = 0;
 begin;
  int v15 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v16 = (v15 == 2);
  int v17 = atomic_load_explicit(&atom_0_r3_2, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_2_r6_1, memory_order_seq_cst);
  int v22_conj = v20 & v21;
  int v23_conj = v19 & v22_conj;
  int v24_conj = v18 & v23_conj;
  int v25_conj = v17 & v24_conj;
  int v26_conj = v16 & v25_conj;
  if (v26_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
