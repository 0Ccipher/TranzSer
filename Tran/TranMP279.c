/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[5]; 
atomic_int atom_0_r5_0; 
atomic_int atom_1_r5_0; 
atomic_int atom_2_r5_0; 
atomic_int atom_3_r5_0; 
atomic_int atom_4_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  int v6_r5 = atomic_load_explicit(&vars[1+v3_r4], memory_order_seq_cst);
  int v40 = (v6_r5 == 0);
  atomic_store_explicit(&atom_0_r5_0, v40, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v8_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r4 = v8_r3 ^ v8_r3;
  int v12_r5 = atomic_load_explicit(&vars[2+v9_r4], memory_order_seq_cst);
  int v41 = (v12_r5 == 0);
  atomic_store_explicit(&atom_1_r5_0, v41, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v15_r4 = v14_r3 ^ v14_r3;
  int v18_r5 = atomic_load_explicit(&vars[3+v15_r4], memory_order_seq_cst);
  int v42 = (v18_r5 == 0);
  atomic_store_explicit(&atom_2_r5_0, v42, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v20_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v21_r4 = v20_r3 ^ v20_r3;
  int v24_r5 = atomic_load_explicit(&vars[4+v21_r4], memory_order_seq_cst);
  int v43 = (v24_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v43, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v26_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v27_r4 = v26_r3 ^ v26_r3;
  int v30_r5 = atomic_load_explicit(&vars[0+v27_r4], memory_order_seq_cst);
  int v44 = (v30_r5 == 0);
  atomic_store_explicit(&atom_4_r5_0, v44, memory_order_seq_cst);
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
