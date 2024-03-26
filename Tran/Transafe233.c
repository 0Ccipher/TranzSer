void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[3]; 
atomic_int atom_1_r1_2; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r5_1; 

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
  int v4_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_r4 = v4_r3 ^ v4_r3;
  int v6_r4 = v5_r4 + 1;
  atomic_store_explicit(&vars[1], v6_r4, memory_order_seq_cst);
  int v35 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v35, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v8_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r3 = v8_r1 ^ v8_r1;
  int v10_r3 = v9_r3 + 1;
  atomic_store_explicit(&vars[2], v10_r3, memory_order_seq_cst);
  int v36 = (v8_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v36, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v12_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  int v14_r3 = v13_r3 + 1;
  atomic_store_explicit(&vars[0], v14_r3, memory_order_seq_cst);
  int v37 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v37, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v16_r1 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v18_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v20_r4 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v22_r5 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v38 = (v16_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v38, memory_order_seq_cst);
  int v39 = (v22_r5 == 1);
  atomic_store_explicit(&atom_4_r5_1, v39, memory_order_seq_cst);
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

  int v23 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v24 = (v23 == 2);
  int v25 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_4_r5_1, memory_order_seq_cst);
  int v30_conj = v28 & v29;
  int v31_conj = v27 & v30_conj;
  int v32_conj = v26 & v31_conj;
  int v33_conj = v25 & v32_conj;
  int v34_conj = v24 & v33_conj;
  if (v34_conj == 1) assert(0);
  return 0;
}
