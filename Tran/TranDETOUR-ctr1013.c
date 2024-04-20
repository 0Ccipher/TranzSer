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
atomic_int atom_4_r6_0; 

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
  int v37 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v10_cmpeq = (v9_r3 == v9_r3);
  if (v10_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v38 = (v7_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v12_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  int v16_r4 = atomic_load_explicit(&vars[5+v13_r3], memory_order_seq_cst);
  int v18_r6 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v19_cmpeq = (v18_r6 == v18_r6);
  if (v19_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[7], 1, memory_order_seq_cst);
  int v39 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v39, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v21_r1 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v23_r3 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v24_r5 = v23_r3 ^ v23_r3;
  int v27_r6 = atomic_load_explicit(&vars[0+v24_r5], memory_order_seq_cst);
  int v40 = (v21_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v40, memory_order_seq_cst);
  int v41 = (v27_r6 == 0);
  atomic_store_explicit(&atom_4_r6_0, v41, memory_order_seq_cst);
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
