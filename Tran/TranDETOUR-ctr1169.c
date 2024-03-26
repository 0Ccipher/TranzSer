void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[11]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v5_cmpeq = (v4_r3 == v4_r3);
  if (v5_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v40 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v40, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v8_r3 = v7_r1 ^ v7_r1;
  int v11_r4 = atomic_load_explicit(&vars[3+v8_r3], memory_order_seq_cst);
  int v13_r6 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_cmpeq = (v13_r6 == v13_r6);
  if (v14_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v41 = (v7_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v41, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v16_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v17_r3 = v16_r1 ^ v16_r1;
  int v20_r4 = atomic_load_explicit(&vars[6+v17_r3], memory_order_seq_cst);
  int v22_r6 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v23_cmpeq = (v22_r6 == v22_r6);
  if (v23_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[8], 1, memory_order_seq_cst);
  int v42 = (v16_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v42, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v25_r1 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v26_r3 = v25_r1 ^ v25_r1;
  int v29_r4 = atomic_load_explicit(&vars[9+v26_r3], memory_order_seq_cst);
  int v31_r6 = atomic_load_explicit(&vars[10], memory_order_seq_cst);
  int v32_cmpeq = (v31_r6 == v31_r6);
  if (v32_cmpeq)  goto lbl_LC03; else goto lbl_LC03;
lbl_LC03:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v43 = (v25_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v43, memory_order_seq_cst);
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

  int v33 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v34 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v35 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v36 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v37_conj = v35 & v36;
  int v38_conj = v34 & v37_conj;
  int v39_conj = v33 & v38_conj;
  if (v39_conj == 1) assert(0);
  return 0;
}
