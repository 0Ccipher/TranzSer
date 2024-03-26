void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[6]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r7_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r7_0; 

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
  int v4_r3 = v3_r3 + 1;
  atomic_store_explicit(&vars[1], v4_r3, memory_order_seq_cst);
  int v6_r5 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r6 = v6_r5 ^ v6_r5;
  int v10_r7 = atomic_load_explicit(&vars[2+v7_r6], memory_order_seq_cst);
  int v38 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v38, memory_order_seq_cst);
  int v39 = (v10_r7 == 0);
  atomic_store_explicit(&atom_1_r7_0, v39, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v12_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v13_r4 = v12_r3 ^ v12_r3;
  int v14_r4 = v13_r4 + 1;
  atomic_store_explicit(&vars[3], v14_r4, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v16_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v17_r3 = v16_r1 ^ v16_r1;
  int v18_r3 = v17_r3 + 1;
  atomic_store_explicit(&vars[4], v18_r3, memory_order_seq_cst);
  int v40 = (v16_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v40, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v20_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v21_r3 = v20_r1 ^ v20_r1;
  int v22_r3 = v21_r3 + 1;
  atomic_store_explicit(&vars[5], v22_r3, memory_order_seq_cst);
  int v24_r5 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v25_r6 = v24_r5 ^ v24_r5;
  int v28_r7 = atomic_load_explicit(&vars[0+v25_r6], memory_order_seq_cst);
  int v41 = (v20_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v41, memory_order_seq_cst);
  int v42 = (v28_r7 == 0);
  atomic_store_explicit(&atom_4_r7_0, v42, memory_order_seq_cst);
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

  int v29 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_1_r7_0, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v33 = atomic_load_explicit(&atom_4_r7_0, memory_order_seq_cst);
  int v34_conj = v32 & v33;
  int v35_conj = v31 & v34_conj;
  int v36_conj = v30 & v35_conj;
  int v37_conj = v29 & v36_conj;
  if (v37_conj == 1) assert(0);
  return 0;
}
