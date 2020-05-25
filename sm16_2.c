#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    for (int i = 1; i <= 3; ++i) {
        pid = fork();
        if (pid < 0) {
            printf("Failed...\n");
            exit(1);
        } else if (pid == 0) {
            char inlet[8];
            read(0, &inlet, 8);
            int x = strtol(inlet, NULL, 10);
            printf("%d %d\n", i, x * x);
            exit(0);

        }
    }
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
    return 0;
}