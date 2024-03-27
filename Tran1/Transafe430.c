/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[8]; 
atomic_int atom_3_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[6], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[6], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[7], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v2_r1 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[0], v4_r3, memory_order_seq_cst);
  int v15 = (v2_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v15, memory_order_seq_cst);
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

   int res = 0;
 begin;
  int v5 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v6 = (v5 == 2);
  int v7 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v8 = (v7 == 2);
  int v9 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v10 = (v9 == 2);
  int v11 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v12_conj = v10 & v11;
  int v13_conj = v8 & v12_conj;
  int v14_conj = v6 & v13_conj;
  if (v14_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
