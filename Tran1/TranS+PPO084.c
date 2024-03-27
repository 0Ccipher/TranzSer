/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_0_r1_2; 
atomic_int atom_1_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v13 = (v2_r1 == 2);
  atomic_store_explicit(&atom_0_r1_2, v13, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_cmpeq = (v5_r1 == v5_r1);
  if (v6_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v14 = (v5_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v14, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);

   int res = 0;
 begin;
  int v7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v8 = (v7 == 2);
  int v9 = atomic_load_explicit(&atom_0_r1_2, memory_order_seq_cst);
  int v10 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v11_conj = v9 & v10;
  int v12_conj = v8 & v11_conj;
  if (v12_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
