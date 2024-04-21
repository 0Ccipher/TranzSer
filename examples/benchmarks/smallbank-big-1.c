#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst


atomic_int customersAccNO[3] = {1,2,3};
atomic_int checkingAccountBal[3] = {1000,700,500};
atomic_int savingsAccountBal[3] = {10000,2000,500};

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;


void amalgamate(int custID0, int custID1){
    begin;
    //get balance
    int sbal0 = atomic_load_explicit(&savingsAccountBal[custID0],SC);
    int cbal1 = atomic_load_explicit(&checkingAccountBal[custID1],SC);
    int total = sbal0 + cbal1;
    //update balance
    atomic_store_explicit(&checkingAccountBal[custID0],0,SC);
    atomic_store_explicit(&savingsAccountBal[custID1],total,SC);
    end;
}

int balance(int custID){
    begin;
    atomic_load_explicit(&customersAccNO[custID],SC);
    //get balance
    int sbal0 = atomic_load_explicit(&savingsAccountBal[custID],SC);
    int cbal1 = atomic_load_explicit(&checkingAccountBal[custID],SC);
    int total = sbal0 + cbal1;
    end;
    return total;
}

void depositChecking(int custID, int amount){
    begin;
    atomic_load_explicit(&customersAccNO[custID],SC);
    //update balance
    atomic_store_explicit(&checkingAccountBal[custID],amount,SC);
    end;
}

void sendPayment(int sendAcct, int destAcct, int amount){
    begin;
    atomic_load_explicit(&customersAccNO[sendAcct],SC);
    atomic_load_explicit(&customersAccNO[destAcct],SC);
    int cbal = atomic_load_explicit(&checkingAccountBal[sendAcct],SC);
    int sbal = atomic_load_explicit(&savingsAccountBal[destAcct],SC);
    if(cbal < amount){
        abort;
        return;
    }
    cbal = cbal - amount;
    sbal = sbal + amount;
    atomic_store_explicit(&checkingAccountBal[sendAcct],cbal,SC);
    atomic_store_explicit(&checkingAccountBal[destAcct],sbal,SC);
    end;
}

void transactSavings(int custID, int amount){
    begin;
    atomic_load_explicit(&customersAccNO[custID],SC);
    int sbal = atomic_load_explicit(&savingsAccountBal[custID],SC);
    sbal = sbal - amount;
    if(sbal < 0){
        abort;
        return;
    }
    atomic_store_explicit(&savingsAccountBal[custID],sbal,SC);
    end;
}

void writeCheck(int custID, int amount){
    begin;
    atomic_load_explicit(&customersAccNO[custID],SC);
    int sbal = atomic_load_explicit(&savingsAccountBal[custID],SC);
    int cbal = atomic_load_explicit(&checkingAccountBal[custID],SC);
    int total = sbal + cbal;
    if(total < amount){
        cbal = cbal - (amount - 1); 
        atomic_store_explicit(&checkingAccountBal[custID],cbal,SC);
    }
    else{
        atomic_store_explicit(&checkingAccountBal[custID],cbal-amount,SC);
    }
    end;
}
void * thr1(void *arg){
    writeCheck(2,100);
    balance(0);
    return NULL;
}
void * thr2(void *arg){
    balance(0);
    balance(1);
    balance(2);
    return NULL;
}
void * thr3(void *arg){
    amalgamate(0,1);
    transactSavings(1,100);
    return NULL;
}
void * thr4(void *arg){
    writeCheck(1,140);
    depositChecking(1,700);
    sendPayment(1,0,10);
    return NULL;
}
void * thr5(void *arg){
    writeCheck(1,500);
    balance(0);
    balance(1);
    balance(2);
    return NULL;
}
int main() {
    pthread_t t1,t2,t3,t4,t5;

   
    pthread_create(&t4,NULL,thr4,NULL);
    pthread_create(&t5,NULL,thr5,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);
    pthread_create(&t1,NULL,thr1,NULL);


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);    
   // printf("----------------------------------------------\n");
    return 0;
}
