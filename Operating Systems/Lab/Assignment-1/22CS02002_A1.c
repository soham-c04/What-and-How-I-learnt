#include<fcntl.h>    
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>

void Producer(){
	srand(time(NULL));
	const int size=4096;
    int shm_id=shm_open("22cs02002.txt",O_CREAT | O_RDWR, 0666);
    ftruncate(shm_id,size);
    void *ptr=mmap(0,size,PROT_WRITE,MAP_SHARED,shm_id,0);
    char c='a'+rand()%26;
    printf("Inserted element: %c\n",c);
    sprintf(ptr,"%c",c);
}
void Consumer(){
	const int size=4096;
    int shm_id=shm_open("22cs02002.txt",O_RDONLY, 0666);
    ftruncate(shm_id,size);
    void *ptr=mmap(0,size,PROT_READ,MAP_SHARED,shm_id,0);
    printf("Deleted character: ");
    printf("%c\n",(char*)ptr);
    shm_unlink("22cs02002.txt");
}

int main(){
    srand(time(NULL));
    int sz=0;
    while(1){
        int which=rand()%2;
        if(sz==0) which=1;
        else if(sz==100) which=0;
        if(which){
        	Producer();
            sz++;
        }
        else{
        	Consumer();
            sz--;
        }
        sleep(1);
    }
	return 0;
}
