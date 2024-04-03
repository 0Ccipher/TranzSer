/*
	Example 6  - 3 traces 
*/
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>
#include  <stdlib.h>

atomic_int x,y;

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

int __VERIFIER_atomic_t1(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;

	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	r1 = atomic_load_explicit(&y, memory_order_seq_cst);

	__VERIFIER_Transaction_end();
	return 1;
}

int __VERIFIER_atomic_t2(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&x, 3, memory_order_seq_cst);
	// r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	
	atomic_store_explicit(&y, 3, memory_order_seq_cst);
	// r1 = atomic_load_explicit(&y, memory_order_seq_cst);

	__VERIFIER_Transaction_end();
	return 1;
}

int __VERIFIER_atomic_t3(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&y, 4, memory_order_seq_cst);
	// r1 = atomic_load_explicit(&y, memory_order_seq_cst);
	
	__VERIFIER_Transaction_end();
	return 1;
}


void *thr1(void *arg){
 	int bba1 = __VERIFIER_atomic_t1();
	return NULL;
}

void *thr2(void *arg){
	int bba2 = __VERIFIER_atomic_t2();
 	int bba1 = __VERIFIER_atomic_t3();
	return NULL;
}


int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4,t5;
	
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	
	// assert(0);
	printf("___Done\n\n");
	return 0;
}

