#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    unsigned long long N;
    scanf("%llu", &N);
    for (unsigned long long i = 1; i <= N; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Failed...\n");
            exit(1);
        } else if (pid != 0) {
            wait(NULL);
            exit(0);
        }
        if (i == N) {
            printf("%llu\n", i);
            fflush(STDIN_FILENO);
        } else {
            printf("%llu ", i);
            fflush(STDIN_FILENO);
        }
    }
    return 0;
}