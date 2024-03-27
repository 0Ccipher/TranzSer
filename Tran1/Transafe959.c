/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[7]; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v2_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[3], v4_r3, memory_order_seq_cst);
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v24 = (v2_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v24, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v6_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  int v8_r3 = v7_r3 + 1;
  atomic_store_explicit(&vars[6], v8_r3, memory_order_seq_cst);
  int v25 = (v6_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v25, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v10_r1 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v11_r3 = v10_r1 ^ v10_r1;
  int v12_r3 = v11_r3 + 1;
  atomic_store_explicit(&vars[0], v12_r3, memory_order_seq_cst);
  int v26 = (v10_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v26, memory_order_seq_cst);
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
  int v13 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v14 = (v13 == 2);
  int v15 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v16 = (v15 == 2);
  int v17 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v20_conj = v18 & v19;
  int v21_conj = v17 & v20_conj;
  int v22_conj = v16 & v21_conj;
  int v23_conj = v14 & v22_conj;
  if (v23_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
