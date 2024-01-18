#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>
#include  <stdlib.h>

atomic_int x,y,z,dummy;
int a1 = 0, a2 =0;

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

int __VERIFIER_atomic_t1(){

	__VERIFIER_Transaction_begin();
	// atomic_store_explicit(&z, 1, memory_order_seq_cst);
	int r1 = 0;
	// atomic_store_explicit(&x, 1, memory_order_seq_cst);
	
	atomic_store_explicit(&z, 11, memory_order_seq_cst);
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z12-own: %d\n",r1);
	
	__VERIFIER_Transaction_end();

	return 1;
}

int __VERIFIER_atomic_t2(){
	__VERIFIER_Transaction_begin();
	int r1 = 0;
	
	atomic_store_explicit(&z, 2, memory_order_seq_cst);
	
	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x21: %d\n",r1);
	
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z2-own: %d\n",r1);
	
	__VERIFIER_Transaction_end();
	return r1;
 }

int __VERIFIER_atomic_t3(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&z, 31, memory_order_seq_cst);

	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z13-own: %d\n",r1);
	
	__VERIFIER_Transaction_end();

	return 1;
}


void *thr1(void *arg){
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
 	int bba1 = __VERIFIER_atomic_t1();
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
	// int b1 = __VERIFIER_atomic_t1();
	// // atomic_t3();
	return NULL;
}

void *thr2(void *arg){
	// a2 = __VERIFIER_atomic_t2();
	int ba1 = __VERIFIER_atomic_t2();
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
	// int bba1 = __VERIFIER_atomic_t1();
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
	return NULL;

}

void *thr3(void *arg){
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
 	int bba1 = __VERIFIER_atomic_t3();
	int ba2 = __VERIFIER_atomic_t2();
	// atomic_store_explicit(&dummy, 1, memory_order_seq_cst);
	// int b1 = __VERIFIER_atomic_t1();
	// // atomic_t3();
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4,t5;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t3,NULL,thr3,NULL);
	pthread_create(&t4,NULL,thr1,NULL);

	pthread_join(t1,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	
	// assert(0);
	printf("___Done\n\n");
	return 0;
}

