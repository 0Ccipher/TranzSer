/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r7_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r7_0; 
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
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r6 = v6_r5 ^ v6_r5;
  int v10_r7 = atomic_load_explicit(&vars[2+v7_r6], memory_order_seq_cst);
  int v40 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v40, memory_order_seq_cst);
  int v41 = (v10_r7 == 0);
  atomic_store_explicit(&atom_1_r7_0, v41, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r4 = v12_r3 ^ v12_r3;
  int v14_r4 = v13_r4 + 1;
  atomic_store_explicit(&vars[3], v14_r4, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v16_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v17_r3 = v16_r1 ^ v16_r1;
  int v18_r3 = v17_r3 + 1;
  atomic_store_explicit(&vars[4], v18_r3, memory_order_seq_cst);
  int v20_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v21_r6 = v20_r5 ^ v20_r5;
  int v24_r7 = atomic_load_explicit(&vars[5+v21_r6], memory_order_seq_cst);
  int v42 = (v16_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v42, memory_order_seq_cst);
  int v43 = (v24_r7 == 0);
  atomic_store_explicit(&atom_3_r7_0, v43, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v26_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
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

   int res = 0;
 begin;
  int v31 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_1_r7_0, memory_order_seq_cst);
  int v33 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v34 = atomic_load_explicit(&atom_3_r7_0, memory_order_seq_cst);
  int v35 = atomic_load_explicit(&atom_4_r5_0, memory_order_seq_cst);
  int v36_conj = v34 & v35;
  int v37_conj = v33 & v36_conj;
  int v38_conj = v32 & v37_conj;
  int v39_conj = v31 & v38_conj;
  if (v39_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
