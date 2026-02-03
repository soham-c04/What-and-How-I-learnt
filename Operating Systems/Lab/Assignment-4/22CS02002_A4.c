#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<stdbool.h>

#define max(a,b) (((a)>=(b))? (a):(b))

/*
Counter Example Deadlock created here when not following Banker's ALgorithm:
Total resources:
A:5  B:6  C:7  D:7

Max need:
P1-  A:2  B:5  C:4  D:4
P2-  A:5  B:6  C:6  D:6
P3-  A:5  B:2  C:4  D:0

Request:
P1-  A:0  B:2  C:1  D:3
P2-  A:1  B:1  C:2  D:0
P3-  A:1  B:0  C:0  D:0
All resources allocated successfully

Available resources:
A:3  B:3  C:4  D:4

Request
P1-  A:2  B:3  C:3  D:1
Resources allocated succesfully.
Process 1 completed.

Available resources:
A:3  B:5  C:5  D:7

Request:
P2-  A:4  B:5  C:4  D:6
P3-  A:4  B:2  C:4  D:0

None of the requests can be completed and they get stuck in a deadlock.
This is because both of them aquired 1 instance of A and require 4 more instances of A.
*/

int rand_num(int a,int b){
    return a+rand()%(b-a+1);
}
pthread_mutex_t lock;
sem_t available[4];
int acquired[3][4],need[3][4];
bool pending_request[3],pending_print=false;

bool check(){
    bool complete[3]={0};
    int avail[4],round=3;
    for(int i=0;i<4;i++){
        int x;
        sem_getvalue(&available[i],&x);
        avail[i]=x;
    }
    int exit[3],cur=0;
    for(int j=0;j<3;j++){
        complete[j]=true;
        for(int i=0;i<4;i++) if(need[j][i]!=acquired[j][i]) complete[j]=false;
        if(complete[j]) exit[cur++]=j+1;
    }
    while(round--){
        for(int j=0;j<3;j++){
            if(complete[j]) continue;
            bool pos=true;
            for(int i=0;i<4 && pos;i++){
                pos=pos&&(avail[i]>=(need[j][i]-acquired[j][i]));
            }
            if(pos){
                complete[j]=true;
                exit[cur++]=j+1;
                for(int i=0;i<4;i++) avail[i]+=acquired[j][i];
            }
        }
    }
    if(cur!=3) return false;
    printf("\nPossible exit sequence:- ");
    for(int j=0;j<2;j++) printf("%d->",exit[j]);
    printf("%d",exit[2]);
    return true;
}

void* f1(void *arg){
    bool complete=false;
    while(!complete){
        int t=1e7;
        while(t--);
        pthread_mutex_lock(&lock);
        int request[4];
        printf("\n\nProcess 1 requested for resources:\n");
        int sum=0;
        while(!sum){
            for(int i=0;i<4;i++){
                request[i]=rand_num(0,need[0][i]-acquired[0][i]);
                sum+=request[i];
            }
        }
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',request[i]);

        bool exit_sequence=false,first=true;
        while(!exit_sequence){
            int t=1e7;
            while(t--);
            if(!first) pthread_mutex_lock(&lock);
            if(pending_request[0] && pending_request[1] && pending_request[2]){
                // if(!pending_print) printf("\nNone of the requested resources can be allocated to any process\n");
                pending_print=true;
                pthread_mutex_unlock(&lock);
                return;
            }
            exit_sequence=true;
            for(int i=0;i<4;i++){
                int x;
                sem_getvalue(&available[i],&x);
                if(request[i]>x) exit_sequence=false;
            }
            if(exit_sequence){
                for(int i=0;i<4;i++){
                    for(int x=0;x<request[i];x++) sem_wait(&available[i]);
                    acquired[0][i]+=request[i];
                }
                // if(first){
                //     for(int i=0;i<4;i++){
                //         int x;
                //         sem_getvalue(&available[i],&x);
                //         printf("%c:%d  ",'A'+i,x);
                //     }
                //     for(int j=0;j<3;j++){
                //         printf("\nProcess %d- ",j+1);
                //         for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                //     }
                // }
                exit_sequence=check();
                if(!exit_sequence){
                    for(int i=0;i<4;i++){
                        for(int x=0;x<request[i];x++) sem_post(&available[i]);
                        acquired[0][i]-=request[i];
                    }
                }
            }
            if(first && !exit_sequence){
                // for(int j=0;j<3;j++){
                //     printf("\nProcess %d- ",j+1);
                //     for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                // }
                printf("\nFailed to allocate requested resources to Process 1.\n");
            }
            if(!exit_sequence){
                pending_request[0]=true;
                pthread_mutex_unlock(&lock);
            }
            first=false;
        }
        pending_request[0]=false;
        printf("\nRequested resources successflly allocated to Process 1.\nAvailable resources:\n");
        complete=true;
        for(int i=0;i<4;i++){
            int x;
            sem_getvalue(&available[i],&x);
            printf("%c:%d  ",i+'A',x);
            if(need[0][i]!=acquired[0][i]) complete=false;
        }
        if(!complete) pthread_mutex_unlock(&lock);
        sleep(1);
    }
    printf("\n\nProcess 1 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        while(need[0][i]--) sem_post(&available[i]);
        int x;
        sem_getvalue(&available[i],&x);
        printf("%c:%d  ",i+'A',x);
    }
    printf("\n\n");
    pthread_mutex_unlock(&lock);
}
void* f2(void *arg){
    bool complete=false;
    while(!complete){
        int t=1e7;
        while(t--);
        pthread_mutex_lock(&lock);
        int request[4];
        printf("\n\nProcess 2 requested for resources:\n");
        int sum=0;
        while(!sum){
            for(int i=0;i<4;i++){
                request[i]=rand_num(0,need[1][i]-acquired[1][i]);
                sum+=request[i];
            }
        }
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',request[i]);

        bool exit_sequence=false,first=true;
        while(!exit_sequence){
            int t=1e7;
            while(t--);
            if(!first) pthread_mutex_lock(&lock);
            if(pending_request[0] && pending_request[1] && pending_request[2]){
                // if(!pending_print) printf("\nNone of the requested resources can be allocated to any process\n");
                pending_print=true;
                pthread_mutex_unlock(&lock);
                return;
            }
            exit_sequence=true;
            for(int i=0;i<4;i++){
                int x;
                sem_getvalue(&available[i],&x);
                if(request[i]>x) exit_sequence=false;
            }
            if(exit_sequence){
                for(int i=0;i<4;i++){
                    for(int x=0;x<request[i];x++) sem_wait(&available[i]);
                    acquired[1][i]+=request[i];
                }
                // if(first){
                //     for(int i=0;i<4;i++){
                //         int x;
                //         sem_getvalue(&available[i],&x);
                //         printf("%c:%d  ",'A'+i,x);
                //     }
                //     for(int j=0;j<3;j++){
                //         printf("\nProcess %d- ",j+1);
                //         for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                //     }
                // }
                exit_sequence=check();
                if(!exit_sequence){
                    for(int i=0;i<4;i++){
                        for(int x=0;x<request[i];x++) sem_post(&available[i]);
                        acquired[1][i]-=request[i];
                    }
                }
            }
            if(first && !exit_sequence){
                // for(int j=0;j<3;j++){
                //     printf("\nProcess %d- ",j+1);
                //     for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                // }
                printf("\nFailed to allocate requested resources to Process 2.\n");
            }
            if(!exit_sequence){
                pending_request[1]=true;
                pthread_mutex_unlock(&lock);
            }
            first=false;
        }
        pending_request[1]=false;
        printf("\nRequested resources successflly allocated to Process 2.\nAvailable resources:\n");
        complete=true;
        for(int i=0;i<4;i++){
            int x;
            sem_getvalue(&available[i],&x);
            printf("%c:%d  ",i+'A',x);
            if(need[1][i]!=acquired[1][i]) complete=false;
        }
        if(!complete) pthread_mutex_unlock(&lock);
        sleep(1);
    }
    printf("\n\nProcess 2 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        while(need[1][i]--) sem_post(&available[i]);
        int x;
        sem_getvalue(&available[i],&x);
        printf("%c:%d  ",i+'A',x);
    }
    printf("\n\n");
    pthread_mutex_unlock(&lock);
}
void* f3(void *arg){
    bool complete=false;
    while(!complete){
        int t=1e7;
        while(t--);
        pthread_mutex_lock(&lock);
        
        int request[4];
        printf("\n\nProcess 3 requested for resources:\n");
        int sum=0;
        while(!sum){
            for(int i=0;i<4;i++){
                request[i]=rand_num(0,need[2][i]-acquired[2][i]);
                sum+=request[i];
            }
        }
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',request[i]);

        bool exit_sequence=false,first=true;
        while(!exit_sequence){
            int t=1e7;
            while(t--);
            if(!first) pthread_mutex_lock(&lock);
            if(pending_request[0] && pending_request[1] && pending_request[2]){
                // if(!pending_print) printf("\nNone of the requested resources can be allocated to any process\n");
                pending_print=true;
                pthread_mutex_unlock(&lock);
                return;
            }
            exit_sequence=true;
            for(int i=0;i<4;i++){
                int x;
                sem_getvalue(&available[i],&x);
                if(request[i]>x) exit_sequence=false;
            }
            if(exit_sequence){
                for(int i=0;i<4;i++){
                    for(int x=0;x<request[i];x++) sem_wait(&available[i]);
                    acquired[2][i]+=request[i];
                }
                // if(first){
                //     for(int i=0;i<4;i++){
                //         int x;
                //         sem_getvalue(&available[i],&x);
                //         printf("%c:%d  ",'A'+i,x);
                //     }
                //     for(int j=0;j<3;j++){
                //         printf("\nProcess %d- ",j+1);
                //         for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                //     }
                // }
                exit_sequence=check();
                if(!exit_sequence){
                    for(int i=0;i<4;i++){
                        for(int x=0;x<request[i];x++) sem_post(&available[i]);
                        acquired[2][i]-=request[i];
                    }
                }
            }
            if(first && !exit_sequence){
                // for(int j=0;j<3;j++){
                //     printf("\nProcess %d- ",j+1);
                //     for(int i=0;i<4;i++) printf("%c:%d,%d  ",'A'+i,need[j][i]-acquired[j][i],acquired[j][i]); 
                // }
                printf("\nFailed to allocate requested resources to Process 3.\n");
            }
            if(!exit_sequence){
                pending_request[2]=true;
                pthread_mutex_unlock(&lock);
            }
            first=false;
        }
        pending_request[2]=false;
        printf("\nRequested resources successflly allocated to Process 3.\nAvailable resources:\n");
        complete=true;
        for(int i=0;i<4;i++){
            int x;
            sem_getvalue(&available[i],&x);
            printf("%c:%d  ",i+'A',x);
            if(need[2][i]!=acquired[2][i]) complete=false;
        }
        if(!complete) pthread_mutex_unlock(&lock);
        sleep(1);
    }
    printf("\n\nProcess 3 completed.\nAvailable resources:\n");
    for(int i=0;i<4;i++){
        while(need[2][i]--) sem_post(&available[i]);
        int x;
        sem_getvalue(&available[i],&x);
        printf("%c:%d  ",i+'A',x);
    }
    printf("\n\n");
    pthread_mutex_unlock(&lock);
}
void main(){
    srand(time(NULL));
    printf("\nTotal resources:\n");
    for(int i=0;i<4;i++){
        int x=rand_num(5,10);
        printf("%c:%d  ",i+'A',x);
        sem_init(&available[i],0,x); // Initialize semaphores
        for(int j=0;j<3;j++){
            need[j][i]=rand_num(0,x);
            acquired[j][i]=0; // Initially all processed have no resources acquired
        }
    }
    printf("\n\nMax need of resources by Process:\n");
    for(int j=0;j<3;j++){
        pending_request[j]=false;
        printf("P%d-  ",j+1);
        for(int i=0;i<4;i++) printf("%c:%d  ",i+'A',need[j][i]);
        printf("\n");
    }

    pthread_t p1,p2,p3;

    pthread_mutex_init(&lock,NULL);

    pthread_create(&p1,NULL,(void*) f1,NULL);
    pthread_create(&p2,NULL,(void*) f2,NULL);
    pthread_create(&p3,NULL,(void*) f3,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
}