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
atomic_int atom_4_r9_0; 

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
  int v3_cmpeq = (v2_r1 == v2_r1);
  if (v3_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v39 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v39, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v9_r4 = atomic_load_explicit(&vars[2+v6_r3], memory_order_seq_cst);
  int v11_r6 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_cmpeq = (v11_r6 == v11_r6);
  if (v12_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v40 = (v5_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v40, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v14_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v17_cmpeq = (v16_r3 == v16_r3);
  if (v17_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[6], 1, memory_order_seq_cst);
  int v41 = (v14_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v41, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v19_r1 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v20_r3 = v19_r1 ^ v19_r1;
  int v23_r4 = atomic_load_explicit(&vars[7+v20_r3], memory_order_seq_cst);
  int v25_r6 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v26_r8 = v25_r6 ^ v25_r6;
  int v29_r9 = atomic_load_explicit(&vars[0+v26_r8], memory_order_seq_cst);
  int v42 = (v19_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v42, memory_order_seq_cst);
  int v43 = (v29_r9 == 0);
  atomic_store_explicit(&atom_4_r9_0, v43, memory_order_seq_cst);
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
