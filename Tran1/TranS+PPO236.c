/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_2; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v27 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v27, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v28 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v28, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v7_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_cmpeq = (v7_r1 == v7_r1);
  if (v8_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v29 = (v7_r1 == 2);
  atomic_store_explicit(&atom_2_r1_2, v29, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v10_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v11_cmpeq = (v10_r1 == v10_r1);
  if (v11_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v30 = (v10_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v30, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v13_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_cmpeq = (v13_r1 == v13_r1);
  if (v14_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v31 = (v13_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v31, memory_order_seq_cst);
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
  int v15 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v16 = (v15 == 2);
  int v17 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_2_r1_2, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v22_conj = v20 & v21;
  int v23_conj = v19 & v22_conj;
  int v24_conj = v18 & v23_conj;
  int v25_conj = v17 & v24_conj;
  int v26_conj = v16 & v25_conj;
  if (v26_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
