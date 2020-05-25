#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <math.h>

long long transfer(long long x) {
    long long tmp = x;
    if (x < 0) {
        tmp = -x;
    }
    long long answer = 0;
    int i = 0;
    while (tmp != 0) {
        ++i;
        tmp = tmp / 4;
    }
    if (x < 0) {
        tmp = -x;
    }
    while (tmp != 0) {
        answer += (tmp % 4) * (long long)(pow(10, i));
        tmp = tmp / 4;
        --i;
    }
    long long res = 0;
    while (answer > 0) {
        res += answer % 10;
        answer = answer / 10;
    }
    return res;
}

int main (int argc, char** argv) {
    int prev, pid;
    int status;
    for (int i = 1; i < argc; ++i) {
        if (i == 1) {
            pid = fork();
            prev = pid;
            printf("%lld\n", transfer(strtoll(argv[i], NULL, 10)));
            fflush(stdout);
            _exit(0);
        } else {
            pid = fork();
            printf("%lld\n", transfer(strtoll(argv[i], NULL, 10)));
            fflush(stdout);
            _exit(0);
        }
    }
    while(wait(NULL) > 0) {
    }
    return 0;
}