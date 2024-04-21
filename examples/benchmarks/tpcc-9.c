#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

// atomic_int warehouse; //one warehouse
atomic_int item[2]={1,2};
atomic_int itemPrice[2]={4,5};
atomic_int stock[2]={30,20}; // item stock
// atomic_int districts; // one district
atomic_int orders[4]={0,0,0,0}; // 0:c0i0;1:c0i1;2:c2i0;3:c2i1
atomic_int customers[2]={0,2};
atomic_int cbalance[2]={100,100};
atomic_int payments=0; //total payments 

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

int stockLevel(int threshold){
    begin;
    int stock = 0;
    int i1 = orders[0] + orders[2];
    if(i1 < threshold){
        stock = stock+1;
    }
    int i2 = orders[1] + orders[3];
    if(i2 < threshold){
        stock = stock+1;
    }
    end;
    return stock;
}

int orderStatus(int customerID){
    begin;
    int status = orders[customerID];
    status = status + orders[customerID+1];
    end;
    return status;
}

void payment(int customerID, int amount){
    begin;
    cbalance[customerID] =  cbalance[customerID] - amount;
    payments = payments + amount;
    end;
}
//cid:2 or 0
void createNewOrder(int customerID, int item0 , int item1){
    begin;
    if(item0 > 0){
        int id = customerID + 0;
        orders[id]= orders[id] + item0;
    }
    if(item1 > 0){
        int id = customerID + 1;
        orders[id]= orders[id] + item1;
    }
    end;
}

//delivered the items- delete the orders
void delivery(){
    begin;
    for(int i=0 ; i < 4;i++){
            orders[i] = 0;
    }
    end;
}

void * thr1(void *arg){
    stockLevel(100);
    orderStatus(1);
    createNewOrder(0,1,2);
    return NULL;
}
void * thr2(void *arg){
    payment(0,10);
    stockLevel(234);
    delivery();
    return NULL;
}
void * thr3(void *arg){
    stockLevel(75);
    return NULL;
}

void * thr4(void *arg){
    createNewOrder(2,1,2);
    orderStatus(0);
    return NULL;
}

int main() {
    pthread_t t1,t2,t3,t4;

    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);
    pthread_create(&t4,NULL,thr4,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
   // printf("----------------------------------------------\n");
    return 0;
}
