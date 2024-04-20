/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[5]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r8_0; 
atomic_int atom_2_r7_1; 
atomic_int atom_3_r5_0; 
atomic_int atom_4_r5_0; 

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
  int v6_r7 = v5_r6 ^ v5_r6;
  int v9_r8 = atomic_load_explicit(&vars[2+v6_r7], memory_order_seq_cst);
  int v39 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v39, memory_order_seq_cst);
  int v40 = (v9_r8 == 0);
  atomic_store_explicit(&atom_1_r8_0, v40, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v12_r4 = v11_r3 ^ v11_r3;
  atomic_store_explicit(&vars[3+v12_r4], 1, memory_order_seq_cst);
  int v14_r7 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v41 = (v14_r7 == 1);
  atomic_store_explicit(&atom_2_r7_1, v41, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v17_r4 = v16_r3 ^ v16_r3;
  int v20_r5 = atomic_load_explicit(&vars[4+v17_r4], memory_order_seq_cst);
  int v42 = (v20_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v42, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v22_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v23_r4 = v22_r3 ^ v22_r3;
  int v26_r5 = atomic_load_explicit(&vars[0+v23_r4], memory_order_seq_cst);
  int v43 = (v26_r5 == 0);
  atomic_store_explicit(&atom_4_r5_0, v43, memory_order_seq_cst);
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
