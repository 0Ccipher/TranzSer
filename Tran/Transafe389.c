void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[3]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_r4 = v4_r3 ^ v4_r3;
  int v6_r4 = v5_r4 + 1;
  atomic_store_explicit(&vars[1], v6_r4, memory_order_seq_cst);
  int v24 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v24, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v8_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v11_r4 = v10_r3 ^ v10_r3;
  int v12_r4 = v11_r4 + 1;
  atomic_store_explicit(&vars[2], v12_r4, memory_order_seq_cst);
  int v25 = (v8_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v25, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v14_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v17_r4 = v16_r3 ^ v16_r3;
  int v18_r4 = v17_r4 + 1;
  atomic_store_explicit(&vars[0], v18_r4, memory_order_seq_cst);
  int v26 = (v14_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v26, memory_order_seq_cst);
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

  int v19 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v22_conj = v20 & v21;
  int v23_conj = v19 & v22_conj;
  if (v23_conj == 1) assert(0);
  return 0;
}
