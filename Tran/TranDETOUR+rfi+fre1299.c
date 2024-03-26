void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[3]; 
atomic_int atom_1_r1_2; 
atomic_int atom_1_r4_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_2; 
atomic_int atom_4_r6_1; 

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
  int v6_r4 = atomic_load_explicit(&vars[1+v3_r3], memory_order_seq_cst);
  int v30 = (v2_r1 == 2);
  atomic_store_explicit(&atom_1_r1_2, v30, memory_order_seq_cst);
  int v31 = (v6_r4 == 0);
  atomic_store_explicit(&atom_1_r4_0, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v8_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v9_r3 = v8_r1 ^ v8_r1;
  atomic_store_explicit(&vars[2+v9_r3], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 2, memory_order_seq_cst);
  int v32 = (v8_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v32, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v11_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v12_r3 = v11_r1 ^ v11_r1;
  atomic_store_explicit(&vars[0+v12_r3], 1, memory_order_seq_cst);
  int v14_r6 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v33 = (v11_r1 == 2);
  atomic_store_explicit(&atom_4_r1_2, v33, memory_order_seq_cst);
  int v34 = (v14_r6 == 1);
  atomic_store_explicit(&atom_4_r6_1, v34, memory_order_seq_cst);
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

  int v15 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v16 = (v15 == 2);
  int v17 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v18 = (v17 == 2);
  int v19 = atomic_load_explicit(&atom_1_r1_2, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_r4_0, memory_order_seq_cst);
  int v21 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v22 = atomic_load_explicit(&atom_4_r1_2, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_4_r6_1, memory_order_seq_cst);
  int v24_conj = v22 & v23;
  int v25_conj = v21 & v24_conj;
  int v26_conj = v20 & v25_conj;
  int v27_conj = v19 & v26_conj;
  int v28_conj = v18 & v27_conj;
  int v29_conj = v16 & v28_conj;
  if (v29_conj == 1) assert(0);
  return 0;
}
