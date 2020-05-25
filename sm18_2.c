#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>


int main() {
    int fd[2];
    int pid1, pid2;
    int x;
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid1 = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (!pid1) {
        pid2 = fork();
        if (!pid2) {
            close(fd[1]);
            int y;
            long long s = 0;
            while (read(fd[0], &y, sizeof(int)) == sizeof(int)) {
                s += y;
            }
            close(fd[0]);
            printf("%lld\n", s);
            exit(0);
        } else {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            exit(0);
        }


    } else {
        while(scanf("%d", &x) == 1) {
            write(fd[1], &x, sizeof(int));
        }
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}