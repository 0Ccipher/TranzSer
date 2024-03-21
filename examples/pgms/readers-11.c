/* This benchmark is adapted from RCMC */


#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

#  define N 11

atomic_int x;
atomic_int idx[N+1];

void *thread_writer(void *unused)
{
	begin;
	atomic_store_explicit(&x, 42, memory_order_seq_cst);
	end;
	return NULL;
}

void *thread_reader(void *arg)
{
	begin;
	int r = *((int *) arg);
	atomic_load_explicit(&x, memory_order_seq_cst);
	end;
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t[N+1];


	for (int i = 0; i <= N; i++) {
		if (i == 0)
			pthread_create(&t[i], NULL, thread_writer, NULL);
		else
			pthread_create(&t[i], NULL, thread_reader, &idx[i-1]);
	}

	for (int i = 0; i <= N; i++) {
		pthread_join(t[i], NULL);
	}

	return 0;
}
