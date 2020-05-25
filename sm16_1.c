#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t daddy;
    pid_t child;
    if ((daddy = fork()) < 0) {
        printf("Failed...\n");
        exit(1);
    }  else if (!daddy) {
        if ((child = fork()) < 0) {
            printf("Failed...\n");
            exit(1);
        } else if (!child) {
            printf("3 ");
        } else {
            wait(NULL);
            printf("2 ");
        }
    } else {
        wait(NULL);
        printf("1\n");
    }
    return 0;
}