#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdbool.h>

#define f(n) for(int i=0;i<(n);i++)
#define COUNT 5
#define THINKING 2
#define EATING 1
#define HUNGRY 0

pthread_mutex_t mutex;
pthread_cond_t cond_var[COUNT];

bool chopstick[COUNT];
int state[COUNT];

void acquire_chopstick(int number){
    chopstick[number]=false;
}
void release_chopstick(int number){
    chopstick[number]=true;
    pthread_cond_signal(&cond_var[number]);
}
void* function(void *arg){
    int number = *(int *)arg;
    int left=number,right=(number+1)%COUNT;
    while(true){
        int t=1e9;
        while(t--);
        if(state[number]==HUNGRY){
            pthread_mutex_lock(&mutex);
            printf("Philosopher %d is Hungry.\n",number);
            while(true){
                if(chopstick[left] && chopstick[right]){
                    acquire_chopstick(left);
                    acquire_chopstick(right);
                    printf("Philosopher %d takes chopsticks %d and %d\n",number,left,right);
                    break;
                    
                }
                else{
                    pthread_cond_wait(&cond_var[left],&mutex);
                    pthread_cond_wait(&cond_var[right],&mutex);
                }
            }
            state[number]=EATING;
            pthread_mutex_unlock(&mutex);
        }
        else if(state[number]==EATING){
            pthread_mutex_lock(&mutex);
            printf("Philosopher %d is Eating.\n",number);
            sleep(1);
            printf("Philosopher %d releases chopsticks %d and %d\n",number,left,right);
            release_chopstick(left);
            release_chopstick(right);
            state[number]=THINKING;
            pthread_mutex_unlock(&mutex);
        }
        else{
            pthread_mutex_lock(&mutex);
            printf("Philosopher %d is Thinking.\n",number);
            sleep(1);
            state[number]=HUNGRY;
            pthread_mutex_unlock(&mutex);
        }
    }
}

void main(){
    f(COUNT) state[i]=THINKING;
    f(COUNT) chopstick[i]=false;
    f(COUNT) pthread_cond_init(&cond_var[i],NULL);
    f(COUNT) release_chopstick(i);
    pthread_mutex_init(&mutex,NULL);

    pthread_t p[COUNT];
    int x[COUNT];
    f(COUNT){
        x[i]=i;
        pthread_create(&p[i],NULL,function,&x[i]);
    }
    f(COUNT) pthread_join(p[i],NULL);
}
