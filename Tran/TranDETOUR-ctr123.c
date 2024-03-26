void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int vars[5]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r3_0; 
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
  int v4_r3 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v25 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v25, memory_order_seq_cst);
  int v26 = (v4_r3 == 0);
  atomic_store_explicit(&atom_1_r3_0, v26, memory_order_seq_cst);
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
  int v6_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v7_cmpeq = (v6_r1 == v6_r1);
  if (v7_cmpeq)  goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v27 = (v6_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v27, memory_order_seq_cst);
    end;
return NULL;
}




void *t4(void *arg){
label_5:;
  begin;
  int v9_r1 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v11_r3 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v13_r5 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  int v15_r7 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v28 = (v9_r1 == 1);
  atomic_store_explicit(&atom_4_r1_1, v28, memory_order_seq_cst);
  int v29 = (v15_r7 == 0);
  atomic_store_explicit(&atom_4_r7_0, v29, memory_order_seq_cst);
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

  int v16 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v17 = atomic_load_explicit(&atom_1_r3_0, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_4_r1_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_4_r7_0, memory_order_seq_cst);
  int v21_conj = v19 & v20;
  int v22_conj = v18 & v21_conj;
  int v23_conj = v17 & v22_conj;
  int v24_conj = v16 & v23_conj;
  if (v24_conj == 1) assert(0);
  return 0;
}
