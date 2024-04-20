/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_2_r6_1; 
atomic_int atom_3_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v33 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v33, memory_order_seq_cst);
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
  atomic_store_explicit(&vars[3+v10_r7], 1, memory_order_seq_cst);
  int v34 = (v6_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v34, memory_order_seq_cst);
  int v35 = (v9_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v35, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v12_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  atomic_store_explicit(&vars[4+v13_r3], 1, memory_order_seq_cst);
  int v15_r6 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v16_r7 = v15_r6 ^ v15_r6;
  int v17_r7 = v16_r7 + 1;
  atomic_store_explicit(&vars[5], v17_r7, memory_order_seq_cst);
  int v36 = (v12_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v36, memory_order_seq_cst);
  int v37 = (v15_r6 == 1);
  atomic_store_explicit(&atom_2_r6_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v19_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v20_r3 = v19_r1 ^ v19_r1;
  int v21_r3 = v20_r3 + 1;
  atomic_store_explicit(&vars[0], v21_r3, memory_order_seq_cst);
  int v38 = (v19_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v38, memory_order_seq_cst);
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

  return 0;
}
