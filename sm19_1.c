#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

//было на семинаре

enum { BREAK = 4 };

volatile int cnt = 0;


void sigint_handler(int signo){
    (void)signo;
    if (cnt == BREAK) {
        _exit(0);
    }
    printf("%d\n", cnt++);
    fflush(stdout);
}


int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    sigset_t bs;
    sigemptyset(&bs);
    sigaddset(&bs, SIGINT);
    sigprocmask(SIG_BLOCK, &bs, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    sigprocmask(SIG_UNBLOCK, &bs, NULL);
    while(1) {
        pause();
    }
}