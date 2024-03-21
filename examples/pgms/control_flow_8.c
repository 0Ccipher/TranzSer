/* Copyright (C) 2022
 * This benchmark is part of SWSC
 */

/* Got inspiration from the Control-flow benchmark in Fig 8 in the journal JACM 2017
   https://dl.acm.org/citation.cfm?id=3073408
*/

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 

#  define N 8

// shared variables
atomic_int x, y, z;

void *p(void *arg)
{
	begin;
	int loc_x;
	loc_x =  atomic_load_explicit(&x, memory_order_seq_cst);
	end;
	return NULL;
}

void *q(void *arg)
{
	begin;
	atomic_store_explicit(&y, 1, memory_order_seq_cst);
	end;
	return NULL;
}

void *r(void *arg)
{
	begin;
	if (atomic_load_explicit(&y, memory_order_seq_cst) == 0)
		atomic_store_explicit(&z, 1, memory_order_seq_cst);
	end;
	return NULL;
}

void *s(void *arg)
{
	begin;
	if (atomic_load_explicit(&z, memory_order_seq_cst) == 1)
		if (atomic_load_explicit(&y, memory_order_seq_cst) == 0)
			atomic_store_explicit(&x, 1, memory_order_seq_cst);
	end;
	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t ps[N], qs[N], rs, ss;

	

	for (i = 0; i < N; i++){
		pthread_create(&ps[i], NULL, p, NULL);
		pthread_create(&qs[i], NULL, q, NULL);
	}

	pthread_create(&rs, NULL, r, NULL);
	pthread_create(&ss, NULL, s, NULL);

	return 0;
}
