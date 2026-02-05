#include<stdio.h>
#include<pthread.h>

#define MAX_SIZE 5
pthread_mutex_t buflock;
int count;

void producer(char *buf){
    while(1){
        while(count==MAX_SIZE);
        pthread_mutex_lock(&buflock);
        printf("Produced character: ");
        buf[count]=getchar();
        getchar();
        count++;
        printf("Count: %d\n",count);
        fflush(stdin);
        fflush(stdout);
        pthread_mutex_unlock(&buflock);
    }
}
void consumer(char *buf){
    while(1){
        while(count==0);
        pthread_mutex_lock(&buflock);
        char c=buf[count-1];
        printf("Consumed Character: %c Count: %d\n",c,count);
        fflush(stdout);
        count--;
        pthread_mutex_unlock(&buflock);
    }
}

void main(){
    char buffer[MAX_SIZE];
    pthread_t p;
    count=0;
    pthread_mutex_init(&buflock,NULL);
    pthread_create(&p,NULL,(void*) producer,&buffer);
    consumer(buffer);
}