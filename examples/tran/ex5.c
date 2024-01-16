/* Example 5 - 4 traces */
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

	r1 = atomic_load_explicit(&w, memory_order_seq_cst);
	printf("w1: %d\n",r1);

	__VERIFIER_Transaction_end();
	printf("t1-done \n");
	return 1;
}

int __VERIFIER_atomic_t3(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&z, 3, memory_order_seq_cst);
	r1 = atomic_load_explicit(&z, memory_order_seq_cst);
	printf("z3-own: %d\n",r1);

	atomic_store_explicit(&x, 3, memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x3-own: %d\n",r1);
	
	__VERIFIER_Transaction_end();
	printf("t3-done \n");
	return 1;
}

int __VERIFIER_atomic_t4(){

	__VERIFIER_Transaction_begin();
	int r1 = 0;
	atomic_store_explicit(&x, 4, memory_order_seq_cst);
	r1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("x4-own: %d\n",r1);
	atomic_store_explicit(&w, 4, memory_order_seq_cst);
	r1 = atomic_load_explicit(&w, memory_order_seq_cst);
	printf("w4-own: %d\n",r1);
	
	__VERIFIER_Transaction_end();
	printf("t4-done \n");
	return 1;
}


void *thr1(void *arg){
 	int bba1 = __VERIFIER_atomic_t1();
	printf("t1-returned \n");
	return NULL;
}

void *thr3(void *arg){
 	int bba1 = __VERIFIER_atomic_t3();
	printf("t3-returned \n");
	return NULL;
}

void *thr4(void *arg){
 	int bba1 = __VERIFIER_atomic_t4();
	printf("t4-returned \n");
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4,t5;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t3,NULL,thr3,NULL);
	pthread_create(&t4,NULL,thr4,NULL);
	pthread_join(t1,NULL);
	printf("t1-joined \n");
	pthread_join(t3,NULL);
	printf("t3-joined \n");
	pthread_join(t4,NULL);
	printf("t4-joined \n");
	
	// assert(0);
	printf("___Done\n\n");
	return 0;
}

