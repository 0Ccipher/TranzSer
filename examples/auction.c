#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdint.h>

atomic_int arr[3] ;// x,y,z;
int a1 = 0, a2 =0;
int __VERIFIER_atomic_t1(){	
	atomic_store_explicit(&arr[0], 1, memory_order_seq_cst);
	int r1 = atomic_load_explicit(&arr[1], memory_order_seq_cst);
	if(r1 == 0) return 1;
	else return 0;
}

int __VERIFIER_atomic_t2(){
	atomic_store_explicit(&arr[1], 1, memory_order_seq_cst);
	int r1 = atomic_load_explicit(&arr[0], memory_order_seq_cst);
	if(r1 == 0) return 1;
	else return 0;
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

	printf(" a1=%d , a2=%d \n", a1,a2);
	if(a1 && a2) assert(0);
	return 0;
}
