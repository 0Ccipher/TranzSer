void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r4_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v5_cmpeq = (v4_r3 == v4_r3);
  if (v5_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v24 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v24, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v10_cmpeq = (v9_r3 == v9_r3);
  if (v10_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v25 = (v7_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v25, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v12_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  int v16_r4 = atomic_load_explicit(&vars[0+v13_r3], memory_order_seq_cst);
  int v26 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v26, memory_order_seq_cst);
  int v27 = (v16_r4 == 0);
  atomic_store_explicit(&atom_3_r4_0, v27, memory_order_seq_cst);
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

  int v17 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_3_r4_0, memory_order_seq_cst);
  int v21_conj = v19 & v20;
  int v22_conj = v18 & v21_conj;
  int v23_conj = v17 & v22_conj;
  if (v23_conj == 1) assert(0);
  return 0;
}
