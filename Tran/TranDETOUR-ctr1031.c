void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[6]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r9_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r4_0; 

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
  int v6_r4 = atomic_load_explicit(&vars[1+v3_r3], memory_order_seq_cst);
  int v8_r6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r8 = v8_r6 ^ v8_r6;
  int v12_r9 = atomic_load_explicit(&vars[3+v9_r8], memory_order_seq_cst);
  int v33 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v33, memory_order_seq_cst);
  int v34 = (v12_r9 == 0);
  atomic_store_explicit(&atom_1_r9_0, v34, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v14_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v16_r3 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v17_cmpeq = (v16_r3 == v16_r3);
  if (v17_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v35 = (v14_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v35, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v19_r1 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v20_r3 = v19_r1 ^ v19_r1;
  int v23_r4 = atomic_load_explicit(&vars[0+v20_r3], memory_order_seq_cst);
  int v36 = (v19_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v36, memory_order_seq_cst);
  int v37 = (v23_r4 == 0);
  atomic_store_explicit(&atom_4_r4_0, v37, memory_order_seq_cst);
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

  int v24 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_1_r9_0, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_4_r4_0, memory_order_seq_cst);
  int v29_conj = v27 & v28;
  int v30_conj = v26 & v29_conj;
  int v31_conj = v25 & v30_conj;
  int v32_conj = v24 & v31_conj;
  if (v32_conj == 1) assert(0);
  return 0;
}
