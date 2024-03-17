#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <assert.h>


void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()

atomic_int x=0,y=0,z=0,w = 0,a1=0,a2=0;
void __VERIFIER_atomic_t1(){
	begin;
	atomic_store(&x,1);//
	atomic_store(&y,1);
	end;
}

void __VERIFIER_atomic_t2(){	
	begin;
	int r1 = atomic_load(&z);
	atomic_store(&y,2);
	end;
}

int __VERIFIER_atomic_t3(){
	begin;
	int r1 = atomic_load(&w);
	atomic_store(&w,3);
	int r2 = atomic_load(&y);
	int r3 = 0;
	int r4 = atomic_load(&x);
	r3 = (r2 == 2);
	int r5 = 0;
	r5 = ((r4 == 0));
	printf(" y3=%d", y);
	r3 = ((r3 & r5));
	end;
	return r3;
 }

int __VERIFIER_atomic_t4(){
	begin;
	int r1 = atomic_load(&w);
	int r2 = atomic_load(&x);
	int r3 = 0;
	printf(" x4=%d ", x);
	r3 = (x == 1);
	end;
	return r3;
}


void *thr1(void *arg){
 	__VERIFIER_atomic_t1();
 	__VERIFIER_atomic_t2();
	return NULL;
}

void *thr2(void *arg){
	a1 = __VERIFIER_atomic_t3();
	a2 =__VERIFIER_atomic_t4();
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("\n--- a1=%d a2=%d ----\n", a1,a2);
	if( a1 & a2) assert(0);
	return 0;
}
