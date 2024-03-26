void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[7]; 
atomic_int atom_1_r1_1; 
atomic_int atom_3_r1_1; 
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
  int v30 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v30, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[1], 2, memory_order_seq_cst);
  int v6_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v7_r5 = v6_r3 ^ v6_r3;
  int v8_r5 = v7_r5 + 1;
  atomic_store_explicit(&vars[3], v8_r5, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v10_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_r3 = v10_r1 ^ v10_r1;
  int v12_r3 = v11_r3 + 1;
  atomic_store_explicit(&vars[4], v12_r3, memory_order_seq_cst);
  int v31 = (v10_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  atomic_store_explicit(&vars[4], 2, memory_order_seq_cst);
  int v14_r3 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v15_r5 = v14_r3 ^ v14_r3;
  int v16_r5 = v15_r5 + 1;
  atomic_store_explicit(&vars[6], v16_r5, memory_order_seq_cst);
  int v18_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v32 = (v18_r7 == 0);
  atomic_store_explicit(&atom_4_r7_0, v32, memory_order_seq_cst);
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

  int v19 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v20 = (v19 == 2);
  int v21 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v22 = (v21 == 2);
  int v23 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_4_r7_0, memory_order_seq_cst);
  int v26_conj = v24 & v25;
  int v27_conj = v23 & v26_conj;
  int v28_conj = v22 & v27_conj;
  int v29_conj = v20 & v28_conj;
  if (v29_conj == 1) assert(0);
  return 0;
}
