/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_1; 

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
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v7_r7 = v6_r5 ^ v6_r5;
  int v8_r7 = v7_r7 + 1;
  atomic_store_explicit(&vars[3], v8_r7, memory_order_seq_cst);
  int v23 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v23, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v10_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_r5 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v15_r7 = v14_r5 ^ v14_r5;
  int v16_r7 = v15_r7 + 1;
  atomic_store_explicit(&vars[0], v16_r7, memory_order_seq_cst);
  int v24 = (v10_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v24, memory_order_seq_cst);
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
