/* This benchmark is adpated from RCMC */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

#  define N 9

atomic_int x;
int idx[9] = {1,2,3,4,5,6,7,8,9};

void *thread_n(void *arg)
{
	begin;
	int new = *((int *) arg);
	int exp = new - 1;
	if(x==exp){
		x = new;
	}
	//atomic_compare_exchange_strong_explicit(&x, &exp, new, memory_order_seq_cst,
						//memory_order_seq_cst);
	end;
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t[N];


	for (int i = 1; i < N + 1; i++) {
		pthread_create(&t[i - 1], NULL, thread_n, &idx[i - 1]);
	}

	return 0;

}
