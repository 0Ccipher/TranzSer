#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

atomic_int items[6]={0,8,2,1005,1,-1};

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

void addItemQuantity(int item , int quantity){
    begin;
    if(item < 1 || item > 5){
            abort;
            return;
    }
    atomic_store_explicit(&items[item] , quantity , SC);
    end;
}
void additem(int item){
    addItemQuantity(item,1);
}

void removeItem(int item){
    begin;
    if(item < 1 || item > 5){
        abort;
        return;
    }
    atomic_store_explicit(&items[item] , -1 , SC);
    end;
}
void getItem(int item){
    begin;
    if(item < 1 || item > 5){
        abort;
        return;
    }
    atomic_load_explicit(&items[item],SC);
    end;
}
int getQuantity(int item){
    begin;
    if(item < 1 || item > 5){
        abort;
        return -1;
    }
    if(atomic_load_explicit(&items[item],SC) == -1){
        abort;
        return -1;
    }
    int q = atomic_load_explicit(&items[item],SC);
    end;
    return q;
}

void changeQuantity(int item,int newq){
    begin;
    if(item < 1 || item > 5){
        abort;
        return;
    }
    if(atomic_load_explicit(&items[item],SC) == -1){
        abort;
        return;
    }
    atomic_store_explicit(&items[item] , newq , SC);
    end;
}

int getList(){
    begin;
    int itemss=0;
    for(int i=1 ; i <= 5;i++){
        if(atomic_load_explicit(&items[i],SC) != -1){
            itemss = itemss + 1;
        }
    }
    end;
    return itemss;
}

void * thr1(void *arg){
    additem(5);
    getItem(5);
    changeQuantity(4,0);
    return NULL;
}
void * thr2(void *arg){
    additem(5);
    getItem(3);
    changeQuantity(5,100);
    return NULL;
}
void * thr3(void *arg){
    getItem(3);
    getItem(4);
    changeQuantity(3,200);
    return NULL;
}

int main() {
    pthread_t t1,t2,t3;

    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
   // printf("----------------------------------------------\n");
    return 0;
}
