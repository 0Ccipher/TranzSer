#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>
#include  <stdlib.h>

atomic_int x,y,z,dummy;
int a1 = 0, a2 =0;

void __VERIFIER_TrBegin(int a){
	printf("Begin Transaction\n");
}

void TrEnd(){
	printf("End Transaction\n");
}

int __VERIFIER_atomic_t1(){
	// __VERIFIER_TrBegin(dummy == 0);
	__VERIFIER_assume(z==0);
	atomic_store_explicit(&z, 1, memory_order_seq_cst);
	int r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z1: %d\n",r1);
	atomic_store_explicit(&x, 1, memory_order_seq_cst);
	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	// int r1 = atomic_load_explicit(&arr[1], memory_order_seq_cst);
	// printf("finished t1\n");
	// TrEnd();
	int i=0;
	for (__VERIFIER_loop_begin(); i <= 2; i++){
		printf("hello\n");
	}
	i=0;
	for (; i <= 2; i++){
		printf("hello\n");
	}
	atomic_store_explicit(&x, 4, memory_order_seq_cst);
	return 1;
}

int __VERIFIER_atomic_t2(){
	// __VERIFIER_TrBegin(dummy==0);
	int r1 = 0;
	// atomic_store_explicit(&y, 1, memory_order_seq_cst);
	atomic_store_explicit(&x, 3, memory_order_seq_cst);
	// atomic_store_explicit(&x, 4, memory_order_seq_cst);
	// atomic_store_explicit(&x, 5, memory_order_seq_cst);
	// atomic_store_explicit(&arr[1], 1, memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x2: %d\n",r1);
	// r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	// TrEnd();
	return r1;
 }


void *thr1(void *arg){
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
 	a1 = __VERIFIER_atomic_t1();
	// // atomic_t3();
	return NULL;
}

void *thr2(void *arg){
	atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
	a2 = __VERIFIER_atomic_t2();
	// a1 = __VERIFIER_atomic_t1();
	return NULL;

}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	// __VERIFIER_atomic_t2();
	// abort();
	assert(0);
	return 0;
}

