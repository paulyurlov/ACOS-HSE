#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

volatile int cnt = 1;


void sigint_handler(int signo){
    if (signo == SIGUSR1) {
        cnt = 1;
    }
    if (signo == SIGUSR2) {
        cnt = 0;
    }
}


int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigint_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigset_t bs;
    sigemptyset(&bs);
    sigaddset(&bs, SIGUSR1);
    sigaddset(&bs, SIGUSR2);
    printf("%d\n", getpid());
    fflush(stdout);
    long long x;
    while (scanf("%lld", &x) == 1) {
        if (cnt == 1) {
            printf("%lld\n", -x);
            fflush(stdout);
        } else {
            printf("%lld\n", x*x);
            fflush(stdout);
        }
    }
}