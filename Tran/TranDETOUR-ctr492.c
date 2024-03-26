void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[9]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_cmpeq = (v2_r1 == v2_r1);
  if (v3_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v30 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v30, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r5 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v10_cmpeq = (v9_r5 == v9_r5);
  if (v10_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v31 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v12_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v16_r5 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v17_cmpeq = (v16_r5 == v16_r5);
  if (v17_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[7], 1, memory_order_seq_cst);
  int v32 = (v12_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v32, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v19_r1 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v21_r3 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v22_cmpeq = (v21_r3 == v21_r3);
  if (v22_cmpeq)  goto lbl_LC03; else goto lbl_LC03;
lbl_LC03:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v33 = (v19_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v33, memory_order_seq_cst);
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

  int v23 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v27_conj = v25 & v26;
  int v28_conj = v24 & v27_conj;
  int v29_conj = v23 & v28_conj;
  if (v29_conj == 1) assert(0);
  return 0;
}
