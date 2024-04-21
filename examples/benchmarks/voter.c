#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

atomic_int MaxVotesPerPhone[4] = {5,10,55,7};
atomic_int contestant[4] = {1,2,3,4};
atomic_int voteCount[4] = {2,10,5,6}; //votes per phone
atomic_int votes[4] = {7,8,5,3};//votes to contestants


#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

void vote(int voteid,int contestantNo, int phoneNo){
    begin;
    int contestant = atomic_load_explicit(&contestant[contestantNo],SC);
    int voteCount = atomic_load_explicit(&voteCount[phoneNo],SC);
    int maxvotes = atomic_load_explicit(&MaxVotesPerPhone[phoneNo],SC);
    if(voteCount >= maxvotes){
        abort;//voter_over_vote_limit
        return;
    }
    int cvotes = atomic_load_explicit(&votes[contestantNo],SC);
    atomic_store_explicit(&votes[contestantNo],cvotes+1,SC);
    end;
}

void * thr1(void *arg){
    vote(120,1,1);
    vote(121,1,1);
    return NULL;
}
void * thr2(void *arg){
    vote(122,2,1);
    vote(123,3,2);
    return NULL;
}
void * thr3(void *arg){
    vote(122,0,2);
    vote(123,0,2);
    return NULL;
}

void * thr4(void *arg){
    vote(122,3,2);
    vote(123,3,2);
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
