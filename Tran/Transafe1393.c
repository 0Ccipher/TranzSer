/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[7]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r5_0; 
atomic_int atom_2_r7_0; 

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
  int v6_r5 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v25 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v25, memory_order_seq_cst);
  int v26 = (v6_r5 == 0);
  atomic_store_explicit(&atom_1_r5_0, v26, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v8_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v9_r5 = v8_r3 ^ v8_r3;
  int v10_r5 = v9_r5 + 1;
  atomic_store_explicit(&vars[4], v10_r5, memory_order_seq_cst);
  int v12_r7 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v27 = (v12_r7 == 0);
  atomic_store_explicit(&atom_2_r7_0, v27, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v15_r5 = v14_r3 ^ v14_r3;
  int v16_r5 = v15_r5 + 1;
  atomic_store_explicit(&vars[0], v16_r5, memory_order_seq_cst);
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
