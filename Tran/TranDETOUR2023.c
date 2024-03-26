void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[4]; 
atomic_int atom_0_r3_1; 
atomic_int atom_1_r6_1; 
atomic_int atom_2_r5_0; 
atomic_int atom_3_r5_0; 
atomic_int atom_4_r5_0; 

atomic_int __fence_var;

void *t0(void *arg){
label_1:;
  begin;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  int v2_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v42 = (v2_r3 == 1);
  atomic_store_explicit(&atom_0_r3_1, v42, memory_order_seq_cst);
    end;
return NULL;
}




void *t1(void *arg){
label_2:;
  begin;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  int v4_r3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5_r4 = v4_r3 ^ v4_r3;
  int v6_r4 = v5_r4 + 1;
  atomic_store_explicit(&vars[1], v6_r4, memory_order_seq_cst);
  int v8_r6 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v43 = (v8_r6 == 1);
  atomic_store_explicit(&atom_1_r6_1, v43, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v10_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v11_r4 = v10_r3 ^ v10_r3;
  int v14_r5 = atomic_load_explicit(&vars[2+v11_r4], memory_order_seq_cst);
  int v44 = (v14_r5 == 0);
  atomic_store_explicit(&atom_2_r5_0, v44, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v17_r4 = v16_r3 ^ v16_r3;
  int v20_r5 = atomic_load_explicit(&vars[3+v17_r4], memory_order_seq_cst);
  int v45 = (v20_r5 == 0);
  atomic_store_explicit(&atom_3_r5_0, v45, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v22_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v23_r4 = v22_r3 ^ v22_r3;
  int v26_r5 = atomic_load_explicit(&vars[0+v23_r4], memory_order_seq_cst);
  int v46 = (v26_r5 == 0);
  atomic_store_explicit(&atom_4_r5_0, v46, memory_order_seq_cst);
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

  int v27 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v28 = (v27 == 2);
  int v29 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v30 = (v29 == 2);
  int v31 = atomic_load_explicit(&atom_0_r3_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_1_r6_1, memory_order_seq_cst);
  int v33 = atomic_load_explicit(&atom_2_r5_0, memory_order_seq_cst);
  int v34 = atomic_load_explicit(&atom_3_r5_0, memory_order_seq_cst);
  int v35 = atomic_load_explicit(&atom_4_r5_0, memory_order_seq_cst);
  int v36_conj = v34 & v35;
  int v37_conj = v33 & v36_conj;
  int v38_conj = v32 & v37_conj;
  int v39_conj = v31 & v38_conj;
  int v40_conj = v30 & v39_conj;
  int v41_conj = v28 & v40_conj;
  if (v41_conj == 1) assert(0);
  return 0;
}
