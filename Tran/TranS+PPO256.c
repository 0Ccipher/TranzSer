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
  atomic_store_explicit(&vars[1+v5_r4], 1, memory_order_seq_cst);
  int v25 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v25, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v7_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v11_r4 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v12_r5 = v11_r4 ^ v11_r4;
  atomic_store_explicit(&vars[2+v12_r5], 1, memory_order_seq_cst);
  int v26 = (v7_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v26, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v14_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v18_r4 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v19_cmpeq = (v18_r4 == v18_r4);
  if (v19_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v27 = (v14_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v27, memory_order_seq_cst);
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

  int v20 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v23_conj = v21 & v22;
  int v24_conj = v20 & v23_conj;
  if (v24_conj == 1) assert(0);
  return 0;
}
