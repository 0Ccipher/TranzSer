/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[7]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r3_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r7_0; 

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
  int v31 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v31, memory_order_seq_cst);
  int v32 = (v4_r3 == 0);
  atomic_store_explicit(&atom_1_r3_0, v32, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  int v10_r4 = atomic_load_explicit(&vars[2+v7_r3], memory_order_seq_cst);
  int v12_r6 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v13_cmpeq = (v12_r6 == v12_r6);
  if (v13_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v33 = (v6_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v15_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v17_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v19_r5 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v21_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v34 = (v15_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v34, memory_order_seq_cst);
  int v35 = (v21_r7 == 0);
  atomic_store_explicit(&atom_4_r7_0, v35, memory_order_seq_cst);
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
  int v22 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_1_r3_0, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_4_r7_0, memory_order_seq_cst);
  int v27_conj = v25 & v26;
  int v28_conj = v24 & v27_conj;
  int v29_conj = v23 & v28_conj;
  int v30_conj = v22 & v29_conj;
  if (v30_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
