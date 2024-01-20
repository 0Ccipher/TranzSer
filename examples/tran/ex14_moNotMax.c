/*
	Example 14  - 6 traces (relaxed maximality checks for events with the transaction of R1y is case of postponed write)
*/
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>
#include  <stdlib.h>

atomic_int x,y,z;

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

int __VERIFIER_atomic_t11(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;

	atomic_store_explicit(&x, 12 , memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x1-own: %d\n",r1);
	
	atomic_store_explicit(&z, 12, memory_order_seq_cst);
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z1-own: %d\n",r1);
	__VERIFIER_Transaction_end();
	printf("t1-done \n");
	return 1;
}

int __VERIFIER_atomic_t12(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;

	atomic_store_explicit(&z, 11, memory_order_seq_cst);
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z1-own: %d\n",r1);
	__VERIFIER_Transaction_end();
	printf("t1-done \n");
	return 1;
} 

int __VERIFIER_atomic_t2(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x2: %d\n",r1);
	r1 = atomic_load_explicit(&y, memory_order_seq_cst);
	printf("y2: %d\n",r1);
	atomic_store_explicit(&z, 2, memory_order_seq_cst); // it's okay if this is not maximal
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z2-own: %d\n",r1);

	__VERIFIER_Transaction_end();
	printf("t2-done \n");
	return 1;
}

int __VERIFIER_atomic_t3(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	
	atomic_store_explicit(&y, 3, memory_order_seq_cst);
	r1 = atomic_load_explicit(&y, memory_order_seq_cst);
	printf("y3-own: %d\n",r1);

	__VERIFIER_Transaction_end();
	printf("t3-done \n");
	return 1;
}

void *thr1(void *arg){
 	int bba1 = __VERIFIER_atomic_t11();
	printf("t11-returned \n");
	int bba11 = __VERIFIER_atomic_t12();
	printf("t12-returned \n");
	return NULL;
}

void *thr2(void *arg){
 	int bba1 = __VERIFIER_atomic_t2();
	printf("t2-returned \n");
	return NULL;
}

void *thr3(void *arg){
	int bba2 = __VERIFIER_atomic_t3();
	printf("t2-returned \n");
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4,t5;
	
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_create(&t3,NULL,thr3,NULL);
	
	

	pthread_join(t1,NULL);
	printf("t1-joined \n");
	pthread_join(t2,NULL);
	printf("t2-joined \n");
	pthread_join(t3,NULL);
	printf("t3-joined \n");
	
	
	// assert(0);
	printf("___Done\n\n");
	return 0;
}

