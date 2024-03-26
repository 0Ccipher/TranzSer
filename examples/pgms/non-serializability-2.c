
#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#define N 4

atomic_int x=0,y=0,z=0,w = 0, a1=0,a2=0,a3=0;
atomic_int arr[N];


void __VERIFIER_atomic_t1(){
	begin;
	x = 1;
	w = 2;
	int r1 = x;
	end;
}

int __VERIFIER_atomic_t2(){
	begin;
	int r1 = x;
	//printf("x2=%d ", x);
	w = 1;
	y = 1;
	x = 2; //update 
	int r3 = 0;
	r3 = (r1 == 1);
	if (r3 == 1){
		for(int i=0 ; i < N;i++)
			atomic_load_explicit(&arr[i],memory_order_seq_cst);
	}
	end;
	return r3;
 }

int __VERIFIER_atomic_t3(){	
	begin;
	z = 1;
	int r1 = x;
	//printf("x3=%d ", x);
	int r3 = 0;
	x = 3; //
	r3 = (r1 == 1);
	if (r3 == 1){
		for(int i=0 ; i < N;i++)
			atomic_load_explicit(&arr[i],memory_order_seq_cst);
	}
	end;
	return r3;
}

void *thr1(void *arg){
 	__VERIFIER_atomic_t1();
	return NULL;
}

void *thr2(void *arg){
	a1 = __VERIFIER_atomic_t2();
	return NULL;
}

void *thr3(void *arg){
	a2 = __VERIFIER_atomic_t3();
	return NULL;
}

void *write0(void *arg){
	begin;
	atomic_store_explicit(&arr[0], 10 , memory_order_seq_cst);
	end;
	return NULL;
}
void *write1(void *arg){
	begin;
	atomic_store_explicit(&arr[1], 10 , memory_order_seq_cst);
	end;
	return NULL;
}
void *write2(void *arg){
	begin;
	atomic_store_explicit(&arr[2], 10 , memory_order_seq_cst);
	end;
	return NULL;
}
void *write3(void *arg){
	begin;
	atomic_store_explicit(&arr[3], 10 , memory_order_seq_cst);
	end;
	return NULL;
}
void *write4(void *arg){
	begin;
	atomic_store_explicit(&arr[4], 10 , memory_order_seq_cst);
	end;
	return NULL;
}
void *write5(void *arg){
	begin;
	atomic_store_explicit(&arr[5], 10 , memory_order_seq_cst);
	end;
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3;
	pthread_t pt[N];
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_create(&t3,NULL,thr3,NULL);
		pthread_create(&pt[1],NULL,write1,NULL);
		pthread_create(&pt[2],NULL,write2,NULL);
		pthread_create(&pt[3],NULL,write3,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	for(int i=1 ; i<N;i++){
		pthread_join(pt[i],NULL);
	}
	//printf("a1=%d a2=%d \n", a1 , a2);
	if( a1 & a2) assert(0);
	return 0;
}
