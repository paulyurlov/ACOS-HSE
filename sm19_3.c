#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

volatile int br = 0;

void sigint_handler(int signo){
    if (signo == SIGUSR2) {
        br = 2;
    }
    if (signo == SIGUSR1) {
        br = 1;
    }
    if (signo == SIGTERM) {
        br = 3;
    }
}

unsigned long long f = 0;
unsigned long long s = 0;

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigint_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigset_t bs, old;
    sigemptyset(&bs);
    sigaddset(&bs, SIGUSR1);
    sigaddset(&bs, SIGUSR2);
    sigaddset(&bs, SIGTERM);
    sigprocmask(SIG_BLOCK, &bs, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &bs, NULL);
    sigprocmask(SIG_BLOCK, &bs, &old);
    while(1) {
        while(!br) {
            sigsuspend(&old);
        }
        if (br == 2) {
            s++;
        }
        if (br == 1) {
            printf("%llu %llu\n", f, s);
            fflush(stdout);
            f++;
        }
        if (br == 3) {
            _exit(0);
        }
        br = 0;
    }
    return 0;
}
//https://github.com/blackav/hse-caos-2019/blob/master/19-signal1/sem-signals.pdf - sigsuspend