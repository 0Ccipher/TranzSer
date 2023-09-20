/* Copyright (C) 2018
 * This benchmark is part of SWSC
 */

/* There are N^2+N+1 weak traces */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>

#define N 100

atomic_int x,y,z,w;

atomic_int var[N];

void *writer1(void *arg){
	// atomic_store_explicit(&x, 1, memory_order_seq_cst); //Currently only one co-ordering load will not read from this
	// atomic_store_explicit(&x, 2, memory_order_seq_cst);
	return NULL;
}

void *writer2(void *arg){
	atomic_store_explicit(&x, 2, memory_order_seq_cst);
	// atomic_store_explicit(&x, 4, memory_order_seq_cst);
	int l1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("\tl1: %d\n",l1);
	// atomic_store_explicit(&x, 1, memory_order_seq_cst);
	// atomic_store_explicit(&x, 2, memory_order_seq_cst);
	// int l1 = y;
	// x = 1;
	// x = 2;
  	return NULL;
}

void *writer3(void *arg){
	int l2 = atomic_load_explicit(&w, memory_order_seq_cst);
	printf("\tl2: %d\n",l2);
	// int l3 = atomic_load_explicit(&w, memory_order_seq_cst);
	// printf("\tl3: %d\n",l3);
	// int l4 = atomic_load_explicit(&w, memory_order_seq_cst);
	// printf("\tl4: %d\n",l4);
  	atomic_store_explicit(&x, 3, memory_order_seq_cst);
	// atomic_store_explicit(&x, 9, memory_order_seq_cst);	
	return NULL;
}


int arg[N];
int main(int argc, char **argv){
	printf("\tStart___________________________\n");
  	pthread_t t[4];
	pthread_t e[N];
     
    // pthread_create(&t[0], NULL, writer1, NULL);
	pthread_create(&t[1], NULL, writer2, NULL);
	pthread_create(&t[2], NULL, writer3, NULL);


  
  
    // pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);
	
	printf("\tEnd____________________________\n");
  return 0;
}
