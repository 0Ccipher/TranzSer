/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[8]; 
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
  int v31 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v31, memory_order_seq_cst);
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
  int v32 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v32, memory_order_seq_cst);
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
  int v33 = (v8_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v13_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_cmpeq = (v13_r1 == v13_r1);
  if (v14_cmpeq)  goto lbl_LC03; else goto lbl_LC03;
lbl_LC03:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v34 = (v13_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v34, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v16_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v18_r3 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v20_r5 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v21_cmpeq = (v20_r5 == v20_r5);
  if (v21_cmpeq)  goto lbl_LC04; else goto lbl_LC04;
lbl_LC04:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v35 = (v16_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v35, memory_order_seq_cst);
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

  return 0;
}
