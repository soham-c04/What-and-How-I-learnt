#include<stdio.h>
#include<pthread.h>

int sum=0;
void* add_to_sum(void* arg) {
    int number = *(int*)arg;  // Cast argument to integer   
    sum += number;  // Critical section: adding to shared variable
    return NULL;
}
void main(){
    pthread_t thread1, thread2;
    int num1 = 10;
    int num2 = 20;

    pthread_create(&thread1, NULL, add_to_sum, &num1);
    pthread_create(&thread2, NULL, add_to_sum, &num2);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the result
    printf("Final sum: %d\n", sum);

}