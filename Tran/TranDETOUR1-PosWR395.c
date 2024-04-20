/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[4]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r5_0; 
atomic_int atom_4_r1_2; 
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
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v5_r6 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v36 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v36, memory_order_seq_cst);
  int v37 = (v5_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r4 = v7_r3 ^ v7_r3;
  int v11_r5 = atomic_load_explicit(&vars[2+v8_r4], memory_order_seq_cst);
  int v38 = (v11_r5 == 0);
  atomic_store_explicit(&atom_2_r5_0, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v13_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  atomic_store_explicit(&vars[3+v14_r3], 1, memory_order_seq_cst);
  int v16_r6 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v17_r7 = v16_r6 ^ v16_r6;
  int v20_r8 = atomic_load_explicit(&vars[0+v17_r7], memory_order_seq_cst);
  int v39 = (v13_r1 == 2);
  atomic_store_explicit(&atom_4_r1_2, v39, memory_order_seq_cst);
  int v40 = (v20_r8 == 0);
  atomic_store_explicit(&atom_4_r8_0, v40, memory_order_seq_cst);
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
