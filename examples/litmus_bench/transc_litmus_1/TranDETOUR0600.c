/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_0_r3_0; 
atomic_int atom_1_r3_2; 
atomic_int atom_1_r4_3; 
atomic_int atom_1_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v16 = (v2_r3 == 0);
  atomic_store_explicit(&atom_0_r3_0, v16, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r4 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r5 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v17 = (v4_r3 == 2);
  atomic_store_explicit(&atom_1_r3_2, v17, memory_order_seq_cst);
  int v18 = (v6_r4 == 3);
  atomic_store_explicit(&atom_1_r4_3, v18, memory_order_seq_cst);
  int v19 = (v8_r5 == 0);
  atomic_store_explicit(&atom_1_r5_0, v19, memory_order_seq_cst);
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
  atomic_store_explicit(&vars[1], 3, memory_order_seq_cst);
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
