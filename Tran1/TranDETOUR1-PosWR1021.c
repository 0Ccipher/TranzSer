/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[2]; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_2; 
atomic_int atom_2_r4_0; 
atomic_int atom_3_r3_1; 

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
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v25 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v25, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  int v9_r4 = atomic_load_explicit(&vars[0+v6_r3], memory_order_seq_cst);
  int v26 = (v5_r1 == 2);
  atomic_store_explicit(&atom_2_r1_2, v26, memory_order_seq_cst);
  int v27 = (v9_r4 == 0);
  atomic_store_explicit(&atom_2_r4_0, v27, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v28 = (v11_r3 == 1);
  atomic_store_explicit(&atom_3_r3_1, v28, memory_order_seq_cst);
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

   int res = 0;
 begin;
  int v12 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v13 = (v12 == 2);
  int v14 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v15 = (v14 == 2);
  int v16 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_2_r1_2, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_2_r4_0, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_3_r3_1, memory_order_seq_cst);
  int v20_conj = v18 & v19;
  int v21_conj = v17 & v20_conj;
  int v22_conj = v16 & v21_conj;
  int v23_conj = v15 & v22_conj;
  int v24_conj = v13 & v23_conj;
  if (v24_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
