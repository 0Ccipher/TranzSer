#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>
#include  <stdlib.h>

atomic_int x,y,z,w,dummy;
int a1 = 0, a2 =0;

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

int __VERIFIER_atomic_t1(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;

	r1 = atomic_load_explicit(&y, memory_order_seq_cst);
	// printf("x: %d , y: %d \n",x,y);

	__VERIFIER_Transaction_end();
	return 1;
}

int __VERIFIER_atomic_t2(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;	
	// atomic_store_explicit(&x, 1, memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	__VERIFIER_Transaction_end();
	return r1;
 }

int __VERIFIER_atomic_t3(){

	__VERIFIER_Transaction_begin();
	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	__VERIFIER_Transaction_end();
	return 1;
}

int __VERIFIER_atomic_t4(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&y, 2, memory_order_seq_cst);
	__VERIFIER_Transaction_end();
	return 1;
}


void *thr1(void *arg){
 	int bba1 = __VERIFIER_atomic_t1();
	int ba1 = __VERIFIER_atomic_t2();
	return NULL;
}

void *thr2(void *arg){
	int ba1 = __VERIFIER_atomic_t3();
	int ba2 = __VERIFIER_atomic_t4();
	return NULL;

}


int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4,t5;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	// assert(0);
	return 0;
}

