#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>

atomic_int x,y,z;
int a1 = 0, a2 =0;
int __VERIFIER_atomic_t1(){	
	atomic_store_explicit(&x, 1, memory_order_seq_cst);
	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	// int r1 = atomic_load_explicit(&arr[1], memory_order_seq_cst);
	return 1;
}

int __VERIFIER_atomic_t2(){
	// atomic_store_explicit(&arr[1], 1, memory_order_seq_cst);
	int r1 = 0;
	// r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	return r1;
 }


void *thr1(void *arg){
 	a1 = __VERIFIER_atomic_t1();
	return NULL;
}

void *thr2(void *arg){
	a2 = __VERIFIER_atomic_t2();
	return NULL;

}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	__VERIFIER_atomic_t2();
	printf("a2=%d \n",a2);
	return 0;
}
