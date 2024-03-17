void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

#define N 3

atomic_int x=0,y=0,z=0;
atomic_int a1 =0, a2=0;\

int __VERIFIER_atomic_t1(){
	//z = 2;
	begin;
	int r1 = x;
	y = 1;
	int r2 = 0;
	r2 = ( r1 == 0);
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

	printf(" a1=%d , a2=%d \n", a1,a2);
	if(a1 & a2) assert(0);
	return 0;
}
