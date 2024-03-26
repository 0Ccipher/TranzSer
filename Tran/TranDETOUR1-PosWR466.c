void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r6_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r4_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v3_r4 = v2_r3 ^ v2_r3;
  atomic_store_explicit(&vars[1+v3_r4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6_r3 = v5_r1 ^ v5_r1;
  atomic_store_explicit(&vars[2+v6_r3], 1, memory_order_seq_cst);
  int v8_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v36 = (v5_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v36, memory_order_seq_cst);
  int v37 = (v8_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v37, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v11_r4 = v10_r3 ^ v10_r3;
  atomic_store_explicit(&vars[3+v11_r4], 1, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v13_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  atomic_store_explicit(&vars[4+v14_r3], 1, memory_order_seq_cst);
  int v38 = (v13_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v38, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v16_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v17_r3 = v16_r1 ^ v16_r1;
  int v20_r4 = atomic_load_explicit(&vars[0+v17_r3], memory_order_seq_cst);
  int v39 = (v16_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v39, memory_order_seq_cst);
  int v40 = (v20_r4 == 0);
  atomic_store_explicit(&atom_4_r4_0, v40, memory_order_seq_cst);
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

  int v21 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v22 = (v21 == 2);
  int v23 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v24 = (v23 == 2);
  int v25 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_4_r4_0, memory_order_seq_cst);
  int v30_conj = v28 & v29;
  int v31_conj = v27 & v30_conj;
  int v32_conj = v26 & v31_conj;
  int v33_conj = v25 & v32_conj;
  int v34_conj = v24 & v33_conj;
  int v35_conj = v22 & v34_conj;
  if (v35_conj == 1) assert(0);
  return 0;
}
