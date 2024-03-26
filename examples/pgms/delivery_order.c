#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#define N 3

atomic_int x=0,y=0,z=0;
atomic_int a1=0,a2=0;
atomic_int arr[N];

void __VERIFIER_atomic_t1(){	
	begin;
	for(int i=0 ; i<N;i++)
		arr[i] = 1;
	z = 1;
	x = 1;
	end;
}

void __VERIFIER_atomic_t2(){
	begin;
	y = 1;
	end;
 }

int __VERIFIER_atomic_t3(){
	begin;
	x = 2;
	int r1 = z ;
	int l3 = ( z == 0);
	end;
	return l3;
}
int __VERIFIER_atomic_t4(){
	begin;
	int r2 = y;
	int r3 = x;
	int r4 = 0;
	if( r2 == 1 && r3 == 2){
		r4 = 1;
		for(int i=0 ; i<N;i++)
		r2 = arr[i];
	}
		
	
	end;
	return r4;
}


void *thr1(void *arg){
 	__VERIFIER_atomic_t1();
 	__VERIFIER_atomic_t2();
	return NULL;
}

void *thr2(void *arg){
	a1 = __VERIFIER_atomic_t3();
	a2 = __VERIFIER_atomic_t4();
	return NULL;

}
int main(int argc, char *argv[]){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	//printf(" a1=%d , a2=%d \n", a1,a2);
	if(a1 & a2) assert(0);
	return 0;
}
