void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[7]; 
atomic_int atom_1_r1_1; 
atomic_int atom_2_r1_1; 
atomic_int atom_3_r1_1; 
atomic_int atom_4_r1_1; 
atomic_int atom_4_r8_0; 

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
  int v3_cmpeq = (v2_r1 == v2_r1);
  if (v3_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  int v31 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v31, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v5_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_r3 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v8_cmpeq = (v7_r3 == v7_r3);
  if (v8_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  int v32 = (v5_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v32, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v10_r1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v11_cmpeq = (v10_r1 == v10_r1);
  if (v11_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v33 = (v10_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v33, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v13_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v14_r3 = v13_r1 ^ v13_r1;
  int v17_r4 = atomic_load_explicit(&vars[5+v14_r3], memory_order_seq_cst);
  int v19_r6 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v21_r8 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v34 = (v13_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v34, memory_order_seq_cst);
  int v35 = (v21_r8 == 0);
  atomic_store_explicit(&atom_4_r8_0, v35, memory_order_seq_cst);
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

  int v22 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v23 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v24 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v25 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_4_r8_0, memory_order_seq_cst);
  int v27_conj = v25 & v26;
  int v28_conj = v24 & v27_conj;
  int v29_conj = v23 & v28_conj;
  int v30_conj = v22 & v29_conj;
  if (v30_conj == 1) assert(0);
  return 0;
}
