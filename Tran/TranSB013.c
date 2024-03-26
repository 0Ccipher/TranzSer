void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_0_r3_0; 
atomic_int atom_1_r6_0; 
atomic_int atom_2_r6_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v20 = (v2_r3 == 0);
  atomic_store_explicit(&atom_0_r3_0, v20, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v5_r5 = v4_r3 ^ v4_r3;
  int v8_r6 = atomic_load_explicit(&vars[3+v5_r5], memory_order_seq_cst);
  int v21 = (v8_r6 == 0);
  atomic_store_explicit(&atom_1_r6_0, v21, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v11_r5 = v10_r3 ^ v10_r3;
  int v14_r6 = atomic_load_explicit(&vars[0+v11_r5], memory_order_seq_cst);
  int v22 = (v14_r6 == 0);
  atomic_store_explicit(&atom_2_r6_0, v22, memory_order_seq_cst);
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

  int v15 = atomic_load_explicit(&atom_0_r3_0, memory_order_seq_cst);
  int v16 = atomic_load_explicit(&atom_1_r6_0, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_2_r6_0, memory_order_seq_cst);
  int v18_conj = v16 & v17;
  int v19_conj = v15 & v18_conj;
  if (v19_conj == 1) assert(0);
  return 0;
}
