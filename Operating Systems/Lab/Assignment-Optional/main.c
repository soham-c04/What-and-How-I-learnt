#include<stdio.h>
#include<pthread.h>
#include<time.h>

int x,count;
pthread_mutex_t lock1,lock2,lock3,lock4;

void* f1(void *arg){
    while(1){
        int t=1e9;
        while(t--);
        pthread_mutex_lock(&lock1);
        x*=3;
        count++;
        printf("f1: %d\n",x);
        if(count%4==0) printf("\n");
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&lock2);
    }
}
void* f2(void *arg){
    while(1){
        int t=1e9;
        while(t--);
        pthread_mutex_lock(&lock2);
        x+=6;
        count++;
        printf("f2: %d\n",x);
        if(count%4==0) printf("\n");
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&lock3);
    }
}
void* f3(void *arg){
    while(1){
        int t=1e9;
        while(t--);
        pthread_mutex_lock(&lock3);
        x/=3;
        count++;
        printf("f3: %d\n",x);
        if(count%4==0) printf("\n");
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&lock4);
    }
}
void* f4(void *arg){
    while(1){
        int t=1e9;
        while(t--);
        pthread_mutex_lock(&lock4);
        x-=1;
        count++;
        printf("f4: %d\n",x);
        if(count%4==0) printf("\n");
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&lock1);
    }
}

void main(){
    pthread_t p1,p2,p3,p4;
    x=1;count=0;

    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);
    pthread_mutex_init(&lock3,NULL);
    pthread_mutex_init(&lock4,NULL);

    pthread_mutex_lock(&lock2);
    pthread_mutex_lock(&lock3);
    pthread_mutex_lock(&lock4);

    printf("x: %d\n\n",x);

    pthread_create(&p1,NULL,(void*) f1,NULL);
    pthread_create(&p2,NULL,(void*) f2,NULL);
    pthread_create(&p3,NULL,(void*) f3,NULL);
    pthread_create(&p4,NULL,(void*) f4,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
}
