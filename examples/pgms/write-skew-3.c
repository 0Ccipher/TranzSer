
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
atomic_int vars[6] = {0,0,0,0,0,0};


int __VERIFIER_atomic_t1(){
	//z = 2;
	begin;
	int r1 = x;
	y = 1;
	int r2 = 0;
	r2 = ( r1 == 0);
	end;
	if(r2 ==0) return 0;
	begin;
	atomic_load(&vars[0]);
	atomic_store(&vars[0],2);
	end;
	begin;
	atomic_load(&vars[1]);
	atomic_store(&vars[1],2);
	end;
	begin;
	atomic_load(&vars[2]);
	atomic_store(&vars[2],2);
	end;
	begin;
	atomic_load(&vars[2]);
	atomic_store(&vars[2],2);
	end;
	begin;
	atomic_load(&vars[4]);
	atomic_store(&vars[4],2);
	end;
	begin;
	atomic_load(&vars[5]);
	atomic_store(&vars[5],2);
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
	if(r2==0) return 0;
	begin;
	atomic_load(&vars[0]);
	atomic_store(&vars[0],2);
	end;
	begin;
	atomic_load(&vars[1]);
	atomic_store(&vars[1],2);
	end;
	begin;
	atomic_load(&vars[2]);
	atomic_store(&vars[2],2);
	end;
	begin;
	atomic_load(&vars[2]);
	atomic_store(&vars[2],2);
	end;
	begin;
	atomic_load(&vars[4]);
	atomic_store(&vars[4],2);
	end;
	begin;
	atomic_load(&vars[5]);
	atomic_store(&vars[5],2);
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
