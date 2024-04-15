
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <assert.h>

atomic_int x=0,y=0;
int a1=0,a2=0;
atomic_int vars[4] = {0,0,0,0};


void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

int __VERIFIER_atomic_t0(){
  begin;
  int r1 = atomic_load(&x);
  atomic_store(&y , 1);
  // printf("x=%d ", atomic_load(&x));
  int r2 = 0;
  r2 = (r1 == 1);
  if(r2 == 1){
    int r6 = vars[3];
		int r7 = vars[1];
  }
  end;
  return r2;
}


int __VERIFIER_atomic_t1(){
  __VERIFIER_Transaction_begin();
  int r1 = atomic_load(&y);
  atomic_store(&x , 1);
  // printf("y=%d ",atomic_load(&y));
  int r2 = 0;
  r2 = (r1 == 1);
  if(r2 == 1){
    int r6 = vars[0];
		int r7 = vars[2];
  }
  end;
  return r2;
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

void *t0(void *arg){
  __VERIFIER_atomic_t0();
return NULL;

}


void *t1(void *arg){
  a2 =__VERIFIER_atomic_t1();
return NULL;

}

void *thr3(void *arg){
 	__VERIFIER_atomic_t7();
 	__VERIFIER_atomic_t5();
	return NULL;
}

void *thr4(void *arg){
	__VERIFIER_atomic_t6();
	__VERIFIER_atomic_t5();
	return NULL;
}

int main(int argc, char **argv){
  pthread_t thr0,t3; 
  pthread_t thr1,t4; 

  pthread_create(&thr0, NULL , t0, NULL);
  pthread_create(&thr1 , NULL , t1, NULL);
  pthread_create(&t3,NULL,thr3,NULL);
	pthread_create(&t4,NULL,thr4,NULL);
	pthread_join(thr0,NULL);
	pthread_join(thr1,NULL);
	pthread_join(t4,NULL);
	pthread_join(t3,NULL);
  // if( a1 & a2 )assert(0);
  return 0;
}
