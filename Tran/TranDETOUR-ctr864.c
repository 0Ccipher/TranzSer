/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[8]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r8_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r8_0; 

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
  int v5_r5 = v4_r3 ^ v4_r3;
  int v8_r6 = atomic_load_explicit(&vars[2+v5_r5], memory_order_seq_cst);
  int v10_r8 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v35 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v35, memory_order_seq_cst);
  int v36 = (v10_r8 == 0);
  atomic_store_explicit(&atom_1_r8_0, v36, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v12_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v15_cmpeq = (v14_r3 == v14_r3);
  if (v15_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v37 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v17_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v18_r3 = v17_r1 ^ v17_r1;
  int v21_r4 = atomic_load_explicit(&vars[6+v18_r3], memory_order_seq_cst);
  int v23_r6 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v25_r8 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v38 = (v17_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v38, memory_order_seq_cst);
  int v39 = (v25_r8 == 0);
  atomic_store_explicit(&atom_4_r8_0, v39, memory_order_seq_cst);
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
