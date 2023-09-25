/* Copyright (C) 2018
 * This benchmark is part of SWSC
 */

/* There are N^2+N+1 weak traces */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>

#define N 0

atomic_int x,y,z,w;

atomic_int var[N];

void *writer1(void *arg){
	// atomic_store_explicit(&w, 1, memory_order_seq_cst);
	// int l1 = atomic_load_explicit(&x, memory_order_seq_cst);
	// printf("\tlx1: %d\t",l1);
	atomic_store_explicit(&y, 1, memory_order_seq_cst);
	return NULL;
}

void *writer2(void *arg){
	// atomic_store_explicit(&x, 2, memory_order_seq_cst);
	// atomic_store_explicit(&x, 4, memory_order_seq_cst);
	int l1 = atomic_load_explicit(&x, memory_order_seq_cst);
	printf("\tlx2: %d\t",l1);
	int ly = 0;
	ly = atomic_load_explicit(&y, memory_order_seq_cst);
	printf("\tly2: %d\n",ly);
	// atomic_store_explicit(&x, 5, memory_order_seq_cst);
	// atomic_store_explicit(&y, 2, memory_order_seq_cst);
	// int lt = 0;
	// ly = atomic_load_explicit(&y, memory_order_seq_cst);
	// printf("\t\tlt2:\n");

  	return NULL;
}

void *writer3(void *arg){
	int l2 = 0;
	// l2 = atomic_load_explicit(&w, memory_order_seq_cst);
	printf("\tlw3: %d\n",l2);
  	atomic_store_explicit(&x, 3, memory_order_seq_cst);
	// int l3 = 0;
	// printf("\t\tlt3:\n");
	// atomic_store_explicit(&y, 3, memory_order_seq_cst);	
	return NULL;
}


int arg[N];
int main(int argc, char **argv){
	printf("\tStart___________________________\n");
  	pthread_t t[4];
	pthread_t e[N];
     
    	pthread_create(&t[0], NULL, writer1, NULL);
	pthread_create(&t[1], NULL, writer2, NULL);
	pthread_create(&t[2], NULL, writer3, NULL);
	// for (int i = 0; i < N; i++)
	// {
	// 	pthread_create(&e[i], NULL, writer3, NULL);
	// }
	

  
  
   	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);
	// for (int i = 0; i < N; i++)
	// {
	// 	pthread_join(e[i], NULL);
	// }
	printf("\tEnd____________________________\n******************************************************\n");
  return 0;
}
