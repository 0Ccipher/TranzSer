void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r8_0; 
atomic_int atom_3_r1_2; 
atomic_int atom_3_r6_1; 
atomic_int atom_4_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
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
label_3:;
  begin;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v12_r4 = v11_r3 ^ v11_r3;
  atomic_store_explicit(&vars[3+v12_r4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v14_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v15_r3 = v14_r1 ^ v14_r1;
  atomic_store_explicit(&vars[4+v15_r3], 1, memory_order_seq_cst);
  int v17_r6 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v41 = (v14_r1 == 2);
  atomic_store_explicit(&atom_3_r1_2, v41, memory_order_seq_cst);
  int v42 = (v17_r6 == 1);
  atomic_store_explicit(&atom_3_r6_1, v42, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  atomic_store_explicit(&vars[4], 2, memory_order_seq_cst);
  int v19_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v20_r4 = v19_r3 ^ v19_r3;
  int v23_r5 = atomic_load_explicit(&vars[0+v20_r4], memory_order_seq_cst);
  int v43 = (v23_r5 == 0);
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

  int v24 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v25 = (v24 == 2);
  int v26 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v27 = (v26 == 2);
  int v28 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_r8_0, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_3_r1_2, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_3_r6_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_4_r5_0, memory_order_seq_cst);
  int v33_conj = v31 & v32;
  int v34_conj = v30 & v33_conj;
  int v35_conj = v29 & v34_conj;
  int v36_conj = v28 & v35_conj;
  int v37_conj = v27 & v36_conj;
  int v38_conj = v25 & v37_conj;
  if (v38_conj == 1) assert(0);
  return 0;
}
