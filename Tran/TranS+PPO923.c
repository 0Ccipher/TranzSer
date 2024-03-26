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
  atomic_store_explicit(&vars[2+v5_r5], 1, memory_order_seq_cst);
  int v16 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v16, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v12_cmpeq = (v11_r5 == v11_r5);
  if (v12_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v17 = (v7_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v17, memory_order_seq_cst);
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

  int v13 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v14 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v15_conj = v13 & v14;
  if (v15_conj == 1) assert(0);
  return 0;
}
