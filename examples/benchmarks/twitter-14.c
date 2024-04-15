#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

atomic_int users[4]={1,2,3,4};
atomic_int tweets[4]={10,20,5,30};//tweets by uid
atomic_int followers[4] = {0,0,1,40};
atomic_int follows[4] = {5,2,3,15};

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

int getFollowers(int uid){
    begin;
    int f = followers[uid];
    end;
    return f;
}

void publishTweet(int uid){
    begin;
    tweets[uid] = tweets[uid] + 1 ;
    end;
}

int getNewsfeed(int uid){
    begin;
    int f = follows[uid];
    f = tweets[uid];
    end;
    return f;
}

void follow(int uid, int fid){
    begin;
    followers[fid] =  followers[fid] + 1;
    follows[uid] = follows[uid] + 1;
    end; 
}

int getTimeline(int uid){
    begin;
    int f = 0;
    f = tweets[uid];
    end;
    return f;
}

void * thr1(void *arg){
     publishTweet(1);
            getTimeline(1);
            follow(2,3);
            getTimeline(2);
    return NULL;
}
void * thr2(void *arg){
    follow(0,1);
            getTimeline(1);
            publishTweet(2);
            follow(2,3);
    return NULL;
}
void * thr3(void *arg){
    publishTweet(1);
            getFollowers(3);
            follow(0,1);
            getNewsfeed(2);
    return NULL;
}
void * thr4(void *arg){
    getTimeline(1);
            getNewsfeed(3);
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
