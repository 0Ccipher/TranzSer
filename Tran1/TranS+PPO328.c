/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[3]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v21 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v21, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_cmpeq = (v7_r3 == v7_r3);
  if (v8_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v22 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v22, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v10_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v14_r4 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v15_r5 = v14_r4 ^ v14_r4;
  atomic_store_explicit(&vars[0+v15_r5], 1, memory_order_seq_cst);
  int v23 = (v10_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v23, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);

   int res = 0;
 begin;
  int v16 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v19_conj = v17 & v18;
  int v20_conj = v16 & v19_conj;
  if (v20_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
