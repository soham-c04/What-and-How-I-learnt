#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<stdbool.h>

#define max(a,b) (((a)>=(b))? (a):(b))

/*
Counter Example Deadlock created here:
Total resources:
A:5  B:6  C:7  D:7

Initially acquired resources by Process:
P1-  A:0  B:2  C:1  D:3
P2-  A:1  B:1  C:2  D:0
P3-  A:1  B:0  C:0  D:0

Available resources:
A:3  B:3  C:4  D:4

Overall requested resources by Process:
P1-  A:2  B:5  C:4  D:4
P2-  A:5  B:6  C:6  D:6
P3-  A:5  B:2  C:4  D:0
*/

int rand_num(int a,int b){
    return a+rand()%(b-a+1);
}
int total[n],available[4];
int acquired[3][4],requested[3][4];
sem_t sem[4];

bool check(){
    bool complete[3]={0};
    int avail[4];
    for(int i=0;i<4;i++) avail[i]=available[i];
    int round=3;
    while(round--){
        for(int j=0;j<3;j++){
            if(complete[j]) continue;
            bool pos=true,incomplete=false;
            for(int i=0;i<4 && pos;i++){
                pos=pos&&(avail[i]>=requested[j][i]-acquired[j][i]);
                if(requested[j][i]!=acquired[j][i]) incomplete=true;
            }
            if(pos && incomplete){
                complete[j]=true;
                for(int i=0;i<4;i++) avail[i]+=acquired[j][i];
            }
        }
    }
    for(int j=0;j<3;j++) if(!complete[j]) return false;
    return false;
}

void* f1(void *arg){
    int t=1e7;
    while(t--);
    bool pos=false;
    while(!pos){
        pos=true;
        for(int i=0;i<4 && pos;i++) pos=pos&&(acquired[0][i]+available[i]>=requested[0][i]);
    }
    for(int i=0;i<4;i++){
        available[i]-=requested[0][i]-acquired[0][i];
        for(int j=0;j<requested[0][i]-acquired[0][i];j++) sem_wait(&sem[i]);
    }
    printf("\n\nProcess 1 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        available[i]+=requested[0][i];
        printf("%c:%d  ",i+'A',available[i]);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<requested[0][i];j++) sem_post(&sem[i]);
    }
}
void* f2(void *arg){
    int t=1e7;
    while(t--);
    bool pos=false;
    while(!pos){
        pos=true;
        for(int i=0;i<4 && pos;i++) pos=pos&&(acquired[1][i]+available[i]>=requested[1][i]);
    }
    for(int i=0;i<4;i++){
        available[i]-=requested[1][i]-acquired[1][i];
        for(int j=0;j<requested[1][i]-acquired[1][i];j++) sem_wait(&sem[i]);
    }
    printf("\n\nProcess 2 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        available[i]+=requested[1][i];
        printf("%c:%d  ",i+'A',available[i]);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<requested[1][i];j++) sem_post(&sem[i]);
    }
}
void* f3(void *arg){
    int t=1e7;
    while(t--);
    bool pos=false;
    while(!pos){
        pos=true;
        for(int i=0;i<4 && pos;i++) pos=pos&&(acquired[2][i]+available[i]>=requested[2][i]);
    }
    for(int i=0;i<4;i++){
        available[i]-=requested[2][i]-acquired[2][i];
        for(int j=0;j<requested[2][i]-acquired[2][i];j++) sem_wait(&sem[i]);
    }
    printf("\n\nProcess 3 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        available[i]+=requested[2][i];
        printf("%c:%d  ",i+'A',available[i]);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<requested[2][i];j++) sem_post(&sem[i]);
    }
}
void main(){
    srand(time(NULL));
    for(int i=0;i<4;i++) total[i]=rand_num(5,10);
    for(int i=0;i<4;i++){
        int x=max(0,total[i]-3);
        int all=total[i];
        for(int j=0;j<3;j++){
            acquired[j][i]=rand_num(0,x); // Set initially acquired value
            requested[j][i]=rand_num(acquired[j][i],max(acquired[j][i],total[i]));
            x-=acquired[j][i];
            all-=acquired[j][i];
        }
        available[i]=all;
    }
    printf("\nTotal resources:\n");
    for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',total[i]);
    printf("\n\nInitially acquired resources by Process:\n");
    for(int j=0;j<3;j++){
        printf("P%d-  ",j+1);
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',acquired[j][i]);
        printf("\n");
    }
    printf("\nAvailable resources:\n");
    for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',available[i]);
    printf("\n\nOverall requested resources by Process:\n");
    for(int j=0;j<3;j++){
        printf("P%d-  ",j+1);
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',requested[j][i]);
        printf("\n");
    }

    // Initialize semaphores
    for(int i=0;i<4;i++) sem_init(&sem[i],0,available[i]);

    pthread_t p1,p2,p3;

    pthread_create(&p1,NULL,(void*) f1,NULL);
    pthread_create(&p2,NULL,(void*) f2,NULL);
    pthread_create(&p3,NULL,(void*) f3,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
}