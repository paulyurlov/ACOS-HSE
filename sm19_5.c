#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>

//Частично код был в конспекте лектора https://github.com/blackav/hse-caos-2019/blob/master/19-signal1/sem-signals.pdf

void do_work(int sup, int *p, int num, unsigned long long max) {
    sigset_t bs;
    int val;
    sigemptyset(&bs);
    sigaddset(&bs, SIGUSR1);
    struct signalfd_siginfo inf;
    read(sup, &inf, sizeof(inf));
    if (inf.ssi_signo == SIGUSR1){
        read(p[0], &val, sizeof(val));
        if (val > max) {
            exit(0);
        }
        printf("%d %d\n", num, val);
        fflush(stdout);
        val++;
        write(p[1], &val, sizeof(val));
    }

}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("invalid args");
        _exit(1);
    }
    unsigned long long n = strtoull(argv[1], NULL, 10);
    int pid1, pid2;
    int p[2];
    int val = 1;
    int sup;
    if (pipe(p) < 0) {
        perror("pipe");
        exit(1);
    }
    sigset_t bs;
    sigemptyset(&bs);
    sigaddset(&bs, SIGUSR1);
    if ((pid1 = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (!pid1) {
        sup = signalfd(-1, &bs, 0);
        do_work(sup, p, 1, n);
        _exit(0);
    }
    if ((pid2 = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if(!pid2) {
        sup = signalfd(-1, &bs, 0);
        do_work(sup, p, 2, n);
        _exit(0);
    }
    write(p[1], &val, sizeof(val));
    kill(pid1, SIGUSR1);
    close(p[0]);
    close(p[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}