/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r7_0; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  int v4_r4 = v3_r4 + 1;
  atomic_store_explicit(&vars[1], v4_r4, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = v6_r1 ^ v6_r1;
  int v8_r3 = v7_r3 + 1;
  atomic_store_explicit(&vars[2], v8_r3, memory_order_seq_cst);
  int v36 = (v6_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v36, memory_order_seq_cst);
  end;
  return NULL;
}




void *t2(void *arg){
 begin;
label_3:;
  int v10_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v11_r3 = v10_r1 ^ v10_r1;
  int v12_r3 = v11_r3 + 1;
  atomic_store_explicit(&vars[3], v12_r3, memory_order_seq_cst);
  int v37 = (v10_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v37, memory_order_seq_cst);
  end;
  return NULL;
}




void *t3(void *arg){
 begin;
label_4:;
  int v14_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v15_r3 = v14_r1 ^ v14_r1;
  int v16_r3 = v15_r3 + 1;
  atomic_store_explicit(&vars[4], v16_r3, memory_order_seq_cst);
  int v38 = (v14_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v38, memory_order_seq_cst);
  end;
  return NULL;
}




void *t4(void *arg){
 begin;
label_5:;
  int v18_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v19_r3 = v18_r1 ^ v18_r1;
  int v20_r3 = v19_r3 + 1;
  atomic_store_explicit(&vars[5], v20_r3, memory_order_seq_cst);
  int v22_r5 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v23_r6 = v22_r5 ^ v22_r5;
  int v26_r7 = atomic_load_explicit(&vars[0+v23_r6], memory_order_seq_cst);
  int v39 = (v18_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v39, memory_order_seq_cst);
  int v40 = (v26_r7 == 0);
  atomic_store_explicit(&atom_4_r7_0, v40, memory_order_seq_cst);
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
  int v27 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_4_r7_0, memory_order_seq_cst);
  int v32_conj = v30 & v31;
  int v33_conj = v29 & v32_conj;
  int v34_conj = v28 & v33_conj;
  int v35_conj = v27 & v34_conj;
  if (v35_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
