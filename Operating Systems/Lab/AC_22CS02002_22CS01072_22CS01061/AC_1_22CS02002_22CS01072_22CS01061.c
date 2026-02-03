#include<stdio.h>
#include<unistd.h>

int main() {
    fork();
    printf("Test 1\n");
    fork();
    printf("Test 2\n");
    fork();
    printf("Test 3\n");
    fork();
    printf("Test 4\n");
    return 0;
}