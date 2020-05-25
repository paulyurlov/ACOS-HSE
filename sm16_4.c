#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>


int process() {
    int x;
    pid_t pid;
    int status;
    if (scanf("%d", &x) != 1) {
        return 0;
    } else {
        if ((pid = fork()) < 0) {
            printf("-1\n");
            return -1;
        } else if (pid == 0) {
            _exit(process());
        } else {
            // Sleep for 1s
            //sleep(1);
            waitpid(pid, &status, 0);
            if (status == 0) {
                printf("%d\n", x);
                fflush(stdout);
                return 0;
            }
            return -1;
        }
    }
}



int main() {
    int res = process();
    if (res == -1) {
        printf("-1\n");
    }
    return 0;
}