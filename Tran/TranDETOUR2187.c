/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r5_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r5_1; 
atomic_int atom_4_r6_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v41 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v41, memory_order_seq_cst);
  int v42 = (v6_r5 == 1);
  atomic_store_explicit(&atom_1_r5_1, v42, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v8_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r4 = v8_r3 ^ v8_r3;
  int v10_r4 = v9_r4 + 1;
  atomic_store_explicit(&vars[2], v10_r4, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v12_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  int v14_r3 = v13_r3 + 1;
  atomic_store_explicit(&vars[3], v14_r3, memory_order_seq_cst);
  int v16_r5 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v43 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v43, memory_order_seq_cst);
  int v44 = (v16_r5 == 1);
  atomic_store_explicit(&atom_3_r5_1, v44, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  int v18_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v19_r4 = v18_r3 ^ v18_r3;
  int v20_r4 = v19_r4 + 1;
  atomic_store_explicit(&vars[0], v20_r4, memory_order_seq_cst);
  int v22_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v45 = (v22_r6 == 1);
  atomic_store_explicit(&atom_4_r6_1, v45, memory_order_seq_cst);
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
