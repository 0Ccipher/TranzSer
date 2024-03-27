/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[9]; 
atomic_int atom_0_r1_1; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v6_r4 = atomic_load_explicit(&vars[1+v3_r3], memory_order_seq_cst);
  int v8_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_cmpeq = (v8_r6 == v8_r6);
  if (v9_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v33 = (v2_r1 == 1);
  atomic_store_explicit(&atom_0_r1_1, v33, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v11_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v12_r3 = v11_r1 ^ v11_r1;
  int v15_r4 = atomic_load_explicit(&vars[4+v12_r3], memory_order_seq_cst);
  int v17_r6 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v18_cmpeq = (v17_r6 == v17_r6);
  if (v18_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[6], 1, memory_order_seq_cst);
  int v34 = (v11_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v34, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v20_r1 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v21_r3 = v20_r1 ^ v20_r1;
  int v24_r4 = atomic_load_explicit(&vars[7+v21_r3], memory_order_seq_cst);
  int v26_r6 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v27_cmpeq = (v26_r6 == v26_r6);
  if (v27_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v35 = (v20_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v35, memory_order_seq_cst);
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
  int v28 = atomic_load_explicit(&atom_0_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v31_conj = v29 & v30;
  int v32_conj = v28 & v31_conj;
  if (v32_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
