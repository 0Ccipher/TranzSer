void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[8]; 
atomic_int atom_1_r7_0; 
atomic_int atom_2_r7_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v3_r5 = v2_r3 ^ v2_r3;
  int v4_r5 = v3_r5 + 1;
  atomic_store_explicit(&vars[2], v4_r5, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v6_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v7_r5 = v6_r3 ^ v6_r3;
  int v8_r5 = v7_r5 + 1;
  atomic_store_explicit(&vars[4], v8_r5, memory_order_seq_cst);
  int v10_r7 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v23 = (v10_r7 == 0);
  atomic_store_explicit(&atom_1_r7_0, v23, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v13_r5 = v12_r3 ^ v12_r3;
  int v14_r5 = v13_r5 + 1;
  atomic_store_explicit(&vars[7], v14_r5, memory_order_seq_cst);
  int v16_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v24 = (v16_r7 == 0);
  atomic_store_explicit(&atom_2_r7_0, v24, memory_order_seq_cst);
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

  int v17 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v18 = (v17 == 2);
  int v19 = atomic_load_explicit(&atom_1_r7_0, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_2_r7_0, memory_order_seq_cst);
  int v21_conj = v19 & v20;
  int v22_conj = v18 & v21_conj;
  if (v22_conj == 1) assert(0);
  return 0;
}
