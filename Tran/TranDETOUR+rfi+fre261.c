void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[4]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r5_0; 
atomic_int atom_3_r7_1; 
atomic_int atom_4_r7_1; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v2_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r3 = v2_r1 ^ v2_r1;
  atomic_store_explicit(&vars[1+v3_r3], 1, memory_order_seq_cst);
  int v5_r6 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v40 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v40, memory_order_seq_cst);
  int v41 = (v5_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v41, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v8_r4 = v7_r3 ^ v7_r3;
  int v11_r5 = atomic_load_explicit(&vars[2+v8_r4], memory_order_seq_cst);
  int v42 = (v11_r5 == 0);
  atomic_store_explicit(&atom_2_r5_0, v42, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v13_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v14_r4 = v13_r3 ^ v13_r3;
  atomic_store_explicit(&vars[3+v14_r4], 1, memory_order_seq_cst);
  int v16_r7 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v43 = (v16_r7 == 1);
  atomic_store_explicit(&atom_3_r7_1, v43, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  int v18_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v19_r4 = v18_r3 ^ v18_r3;
  atomic_store_explicit(&vars[0+v19_r4], 1, memory_order_seq_cst);
  int v21_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v44 = (v21_r7 == 1);
  atomic_store_explicit(&atom_4_r7_1, v44, memory_order_seq_cst);
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

  int v22 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v23 = (v22 == 2);
  int v24 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v25 = (v24 == 2);
  int v26 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v27 = (v26 == 2);
  int v28 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_2_r5_0, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_3_r7_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_4_r7_1, memory_order_seq_cst);
  int v33_conj = v31 & v32;
  int v34_conj = v30 & v33_conj;
  int v35_conj = v29 & v34_conj;
  int v36_conj = v28 & v35_conj;
  int v37_conj = v27 & v36_conj;
  int v38_conj = v25 & v37_conj;
  int v39_conj = v23 & v38_conj;
  if (v39_conj == 1) assert(0);
  return 0;
}
