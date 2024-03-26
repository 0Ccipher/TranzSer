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
atomic_int a1 = 0, a2 =0;
atomic_int vars[4] = {0,0,0,0};

void __VERIFIER_atomic_t1(){	
	begin;
	z = 1;
	int r1 = z;
	x = 1;
	end;
}

void __VERIFIER_atomic_t2(){
	begin;
	y = 2;
	end;
 }

int __VERIFIER_atomic_t3(){
	begin;
	z =3;
	int r1 = x;
	int r2 = y;
	int r3 = 0;
	//printf("x3=%d , y3=%d ", x,y);
	if(r1==1 && r2==0) r3 = 1;
	end;
	return r3;
}
int __VERIFIER_atomic_t4(){
	begin;
	int r1 = x;
	int r2 = y;
	//printf("x4=%d , y4=%d ", x,y);
	int r3 = 0;
	if(r1==0 && r2==2) r3 = 1;
	end;
	return r3;
}

void __VERIFIER_atomic_t5(){
	begin;
	int r1 = vars[0];
	vars[0] = 10;
	end;
}

void __VERIFIER_atomic_t6(){
	begin;
	int r1 = vars[2];
	vars[1] = 16;
	vars[2] = 16;
	end;
}

void __VERIFIER_atomic_t7(){
	begin;
	int r1 = vars[3];
	int r2 = vars[1];
	r2 = r2 + r1;
	vars[1] = r2;
	end;
}


void *thr1(void *arg){
 	__VERIFIER_atomic_t1();
	__VERIFIER_atomic_t5();
	return NULL;
}

void *thr2(void *arg){
	__VERIFIER_atomic_t2();
	__VERIFIER_atomic_t6();
	return NULL;
}

void *thr3(void *arg){
 	a1 = __VERIFIER_atomic_t3();
	__VERIFIER_atomic_t7();
	return NULL;
}

void *thr4(void *arg){
	a2 = __VERIFIER_atomic_t4();
	return NULL;

}

int main(int argc, char *argv[]){
	pthread_t t1,t2,t3,t4;
	pthread_create(&t1,NULL,thr1,NULL);
	pthread_create(&t2,NULL,thr2,NULL);
	pthread_create(&t3,NULL,thr3,NULL);
	pthread_create(&t4,NULL,thr4,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);

	//printf(" a1=%d , a2=%d \n", a1,a2);
	if(a1 & a2) assert(0);
	return 0;
}
