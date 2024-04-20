/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_1_r1_2; 
atomic_int atom_3_r1_2; 

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
  int v4_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_r4 = v4_r3 ^ v4_r3;
  int v6_r4 = v5_r4 + 1;
  atomic_store_explicit(&vars[1], v6_r4, memory_order_seq_cst);
  int v24 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v24, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v8_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v12_r4 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v13_r5 = v12_r4 ^ v12_r4;
  int v14_r5 = v13_r5 + 1;
  atomic_store_explicit(&vars[0], v14_r5, memory_order_seq_cst);
  int v25 = (v8_r1 == 2);
  atomic_store_explicit(&atom_3_r1_2, v25, memory_order_seq_cst);
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
