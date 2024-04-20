/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[3]; 
atomic_int atom_0_r3_2; 
atomic_int atom_0_r7_1; 
atomic_int atom_1_r3_2; 
atomic_int atom_1_r7_1; 
atomic_int atom_2_r3_2; 
atomic_int atom_2_r7_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  int v5_r7 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v36 = (v2_r3 == 2);
  atomic_store_explicit(&atom_0_r3_2, v36, memory_order_seq_cst);
  int v37 = (v5_r7 == 1);
  atomic_store_explicit(&atom_0_r7_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r4 = v7_r3 ^ v7_r3;
  atomic_store_explicit(&vars[2+v8_r4], 1, memory_order_seq_cst);
  int v10_r7 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v38 = (v7_r3 == 2);
  atomic_store_explicit(&atom_1_r3_2, v38, memory_order_seq_cst);
  int v39 = (v10_r7 == 1);
  atomic_store_explicit(&atom_1_r7_1, v39, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r4 = v12_r3 ^ v12_r3;
  atomic_store_explicit(&vars[0+v13_r4], 1, memory_order_seq_cst);
  int v15_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v40 = (v12_r3 == 2);
  atomic_store_explicit(&atom_2_r3_2, v40, memory_order_seq_cst);
  int v41 = (v15_r7 == 1);
  atomic_store_explicit(&atom_2_r7_1, v41, memory_order_seq_cst);
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

  return 0;
}
