/*TranZSER test*/#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();
#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
atomic_int vars[6]; 

atomic_int __fence_var;

void *t0(void *arg){
 begin;
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);
  end;
  return NULL;
}




void *t1(void *arg){
 begin;
label_2:;
  atomic_store_explicit(&vars[3], 2, memory_order_seq_cst);
  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);
  end;
  return NULL;
}




int main(int argc, char **argv){
  pthread_t thr0; 
  pthread_t thr1; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1, NULL , t1, NULL);

  pthread_join(thr0,NULL);
  pthread_join(thr1,NULL);

   int res = 0;
 begin;
  int v1 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v2 = (v1 == 2);
  int v3 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v4 = (v3 == 2);
  int v5_conj = v2 & v4;
  if (v5_conj == 1) res = 1;
  end;
 if(res == 1) assert(0);  return 0;
}
