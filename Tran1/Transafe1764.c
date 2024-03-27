/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r5_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 

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
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v29 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v29, memory_order_seq_cst);
  int v30 = (v6_r5 == 0);
  atomic_store_explicit(&atom_1_r5_0, v30, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v8_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_r5 = v10_r3 ^ v10_r3;
  int v12_r5 = v11_r5 + 1;
  atomic_store_explicit(&vars[4], v12_r5, memory_order_seq_cst);
  int v31 = (v8_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v31, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v14_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v17_r5 = v16_r3 ^ v16_r3;
  int v18_r5 = v17_r5 + 1;
  atomic_store_explicit(&vars[0], v18_r5, memory_order_seq_cst);
  int v32 = (v14_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v32, memory_order_seq_cst);
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
  int v19 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v20 = (v19 == 2);
  int v21 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_1_r5_0, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v25_conj = v23 & v24;
  int v26_conj = v22 & v25_conj;
  int v27_conj = v21 & v26_conj;
  int v28_conj = v20 & v27_conj;
  if (v28_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
