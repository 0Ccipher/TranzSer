/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_0_r3_3; 
atomic_int atom_0_r4_4; 
atomic_int atom_3_r5_2; 
atomic_int atom_3_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4_r4 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_cmpeq = (v4_r4 == v4_r4);
  if (v5_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v19 = (v2_r3 == 3);
  atomic_store_explicit(&atom_0_r3_3, v19, memory_order_seq_cst);
  int v20 = (v4_r4 == 4);
  atomic_store_explicit(&atom_0_r4_4, v20, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[0], 3, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[0], 4, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v7_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r3 = v7_r1 ^ v7_r1;
  int v9_r3 = v8_r3 + 1;
  atomic_store_explicit(&vars[0], v9_r3, memory_order_seq_cst);
  int v11_r5 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v21 = (v11_r5 == 2);
  atomic_store_explicit(&atom_3_r5_2, v21, memory_order_seq_cst);
  int v22 = (v7_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v22, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);
  pthread_create(&thr2, NULL , t2, NULL);
  pthread_create(&thr3, NULL , t3, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);
  pthread_join(thr2,NULL);
  pthread_join(thr3,NULL);

  return 0;
}
