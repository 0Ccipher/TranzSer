/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[3]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r4_0; 
atomic_int atom_2_r3_1; 
atomic_int atom_3_r5_0; 

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
  int v9_r4 = atomic_load_explicit(&vars[2+v6_r3], memory_order_seq_cst);
  int v31 = (v5_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v31, memory_order_seq_cst);
  int v32 = (v9_r4 == 0);
  atomic_store_explicit(&atom_1_r4_0, v32, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v33 = (v11_r3 == 1);
  atomic_store_explicit(&atom_2_r3_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v13_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v14_r4 = v13_r3 ^ v13_r3;
  int v17_r5 = atomic_load_explicit(&vars[0+v14_r4], memory_order_seq_cst);
  int v34 = (v17_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v34, memory_order_seq_cst);
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
