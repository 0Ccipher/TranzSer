void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v5_r5 = v4_r3 ^ v4_r3;
  int v6_r5 = v5_r5 + 1;
  atomic_store_explicit(&vars[2], v6_r5, memory_order_seq_cst);
  int v18 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v18, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v8_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v13_r7 = v12_r5 ^ v12_r5;
  int v14_r7 = v13_r7 + 1;
  atomic_store_explicit(&vars[0], v14_r7, memory_order_seq_cst);
  int v19 = (v8_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v19, memory_order_seq_cst);
    end;
return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);

  int v15 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v16 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v17_conj = v15 & v16;
  if (v17_conj == 1) assert(0);
  return 0;
}
