void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[10]; 
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
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v5_cmpeq = (v4_r3 == v4_r3);
  if (v5_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v39 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v39, memory_order_seq_cst);
    end;
return NULL;
}




void *t2(void *arg){
label_3:;
  begin;
  int v7_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v9_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v10_cmpeq = (v9_r3 == v9_r3);
  if (v10_cmpeq)  goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  int v40 = (v7_r1 == 1);
  atomic_store_explicit(&atom_2_r1_1, v40, memory_order_seq_cst);
    end;
return NULL;
}




void *t3(void *arg){
label_4:;
  begin;
  int v12_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v13_r3 = v12_r1 ^ v12_r1;
  int v16_r4 = atomic_load_explicit(&vars[5+v13_r3], memory_order_seq_cst);
  int v18_r6 = atomic_load_explicit(&vars[6], memory_order_seq_cst);
  int v19_cmpeq = (v18_r6 == v18_r6);
  if (v19_cmpeq)  goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  atomic_store_explicit(&vars[7], 1, memory_order_seq_cst);
  int v41 = (v12_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v41, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v21_r1 = atomic_load_explicit(&vars[7], memory_order_seq_cst);
  int v23_r3 = atomic_load_explicit(&vars[8], memory_order_seq_cst);
  int v25_r5 = atomic_load_explicit(&vars[9], memory_order_seq_cst);
  int v26_r7 = v25_r5 ^ v25_r5;
  int v29_r8 = atomic_load_explicit(&vars[0+v26_r7], memory_order_seq_cst);
  int v42 = (v21_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v42, memory_order_seq_cst);
  int v43 = (v29_r8 == 0);
  atomic_store_explicit(&atom_4_r8_0, v43, memory_order_seq_cst);
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

  int v30 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_2_r1_1, memory_order_seq_cst);
  int v32 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v33 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v34 = atomic_load_explicit(&atom_4_r8_0, memory_order_seq_cst);
  int v35_conj = v33 & v34;
  int v36_conj = v32 & v35_conj;
  int v37_conj = v31 & v36_conj;
  int v38_conj = v30 & v37_conj;
  if (v38_conj == 1) assert(0);
  return 0;
}
