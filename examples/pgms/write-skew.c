
#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

#define N 4

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

atomic_int x=0,y=0,z=0;
atomic_int a1 =0, a2=0;
atomic_int arr[N];


int __VERIFIER_atomic_t1(){
	//z = 2;
	begin;
	int r1 = x;
	y = 1;
	int r2 = 0;
	r2 = ( r1 == 0);
	if (r2 == 1){
		for(int i=0 ; i < N;i++)
			atomic_load_explicit(&arr[i],memory_order_seq_cst);
	}
	end;
	return r2;
}
int __VERIFIER_atomic_t2(){
	begin;
	int r1 = y;
	x = 2;
	int r2 = x;
	int r3 = 0;
	r3 = (r1 == 0);
	if (r3 == 1){
		for(int i=0 ; i < N;i++)
			atomic_store_explicit(&arr[i],10,memory_order_seq_cst);
	}
	end;
	return r3;
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
	pthread_t t1,t2;
	
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	if(a1 & a2) assert(0);
	return 0;
}
