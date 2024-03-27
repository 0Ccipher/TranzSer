/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[5]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_2_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v27 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v27, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  atomic_store_explicit(&vars[2+v7_r3], 1, memory_order_seq_cst);
  int v9_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r7 = v9_r6 ^ v9_r6;
  int v11_r7 = v10_r7 + 1;
  atomic_store_explicit(&vars[3], v11_r7, memory_order_seq_cst);
  int v28 = (v6_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v28, memory_order_seq_cst);
  int v29 = (v9_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v29, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v13_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  atomic_store_explicit(&vars[4+v14_r3], 1, memory_order_seq_cst);
  int v16_r6 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v17_r7 = v16_r6 ^ v16_r6;
  atomic_store_explicit(&vars[0+v17_r7], 1, memory_order_seq_cst);
  int v30 = (v13_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v30, memory_order_seq_cst);
  int v31 = (v16_r6 == 1);
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
  int v18 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_2_r6_1, memory_order_seq_cst);
  int v23_conj = v21 & v22;
  int v24_conj = v20 & v23_conj;
  int v25_conj = v19 & v24_conj;
  int v26_conj = v18 & v25_conj;
  if (v26_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
