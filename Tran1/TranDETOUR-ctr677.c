/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[10]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_cmpeq = (v2_r1 == v2_r1);
  if (v3_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v37 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_cmpeq = (v5_r1 == v5_r1);
  if (v6_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v38 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v8_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_cmpeq = (v10_r3 == v10_r3);
  if (v11_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v39 = (v8_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v39, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v13_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  int v17_r4 = atomic_load_explicit(&vars[5+v14_r3], memory_order_seq_cst);
  int v19_r6 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v20_cmpeq = (v19_r6 == v19_r6);
  if (v20_cmpeq)  goto lbl_LC03; else goto lbl_LC03;
lbl_LC03:;
  atomic_store_explicit(&vars[7], 1, memory_order_seq_cst);
  int v40 = (v13_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v40, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v22_r1 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v24_r3 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v26_r5 = atomic_load_explicit(&vars[9], memory_order_seq_cst);
  int v27_cmpeq = (v26_r5 == v26_r5);
  if (v27_cmpeq)  goto lbl_LC04; else goto lbl_LC04;
lbl_LC04:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v41 = (v22_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v41, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 
  pthread_t thr4; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);
  pthread_create(&thr3, NULL , t3, NULL);
  pthread_create(&thr4, NULL , t4, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);
  pthread_join(thr3,NULL);
  pthread_join(thr4,NULL);

   int res = 0;
 begin;
  int v28 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v33_conj = v31 & v32;
  int v34_conj = v30 & v33_conj;
  int v35_conj = v29 & v34_conj;
  int v36_conj = v28 & v35_conj;
  if (v36_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
