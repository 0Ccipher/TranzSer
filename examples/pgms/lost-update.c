void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

#define N 3

atomic_int x=0,w = 0,a1=0,a2=0;
atomic_int vars[4] = {0,0,0,0};


int __VERIFIER_atomic_t1(){
	begin;
	int r1 = x;//
	int r2 = 0;
	w = 1;
	x = 1;//
	if( r1 == 0) {
		r2 =1;
		int l = vars[0];
		l = vars[1];	
		l = vars[2];
		l = vars[3];
	}
	end;
	return r2;
}

int __VERIFIER_atomic_t2(){
	begin;
	int r1 = x;//
	int r2 = 0;
	w = 2;
	x = 2;//
	if( r1 == 0) {
		r2 =1;
		int l = vars[0];
		l = vars[1];	
		l = vars[2];
		l = vars[3];
	}
	end;
	return r2;
 }

void __VERIFIER_atomic_t5(){
	begin;
	vars[0] = 10;
	end;
}

void __VERIFIER_atomic_t6(){
	begin;
	vars[1] = 16;
	vars[3] = 16;
	end;
}

void __VERIFIER_atomic_t7(){
	begin;
	vars[1] = 2;
	end;
}

void *thr1(void *arg){
 	a1 = __VERIFIER_atomic_t1();
	return NULL;
}

void *thr2(void *arg){
	a2 =__VERIFIER_atomic_t2();
	return NULL;
}
void *thr5(void *arg){
	__VERIFIER_atomic_t5();
	__VERIFIER_atomic_t6();
	__VERIFIER_atomic_t7();
	return NULL;
}
void *thr6(void *arg){
	__VERIFIER_atomic_t6();
	__VERIFIER_atomic_t7();
	return NULL;
}


int main(int argc, char *argv[]){
	pthread_t t1,t2,t5,t6,t7,t8;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_create(&t5,NULL,thr5,NULL);
	pthread_create(&t6,NULL,thr6,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t5,NULL);
	pthread_join(t6,NULL);
	
	// printf("a1=%d , a2=%d \n", a1,a2);
	if( a1 & a2) assert(0);
	return 0;
}
