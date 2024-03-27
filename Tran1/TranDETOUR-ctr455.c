/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[9]; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r3_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v5_cmpeq = (v4_r3 == v4_r3);
  if (v5_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v33 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v12_cmpeq = (v11_r5 == v11_r5);
  if (v12_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v34 = (v7_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v34, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v14_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v18_r5 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v19_cmpeq = (v18_r5 == v18_r5);
  if (v19_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[8], 1, memory_order_seq_cst);
  int v35 = (v14_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v35, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v21_r1 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v23_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v36 = (v21_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v36, memory_order_seq_cst);
  int v37 = (v23_r3 == 0);
  atomic_store_explicit(&atom_4_r3_0, v37, memory_order_seq_cst);
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
  int v24 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_4_r3_0, memory_order_seq_cst);
  int v29_conj = v27 & v28;
  int v30_conj = v26 & v29_conj;
  int v31_conj = v25 & v30_conj;
  int v32_conj = v24 & v31_conj;
  if (v32_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
