#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>


int shell(char* file) {
    if (!fork()) {
        execlp(file, file, NULL);
        _exit(1);
    }
    int st;
    wait(&st);
    return !WEXITSTATUS(st) && WIFEXITED(st);
}


int main(int argc, char** argv) {
    if (argc != 4 ) {
        printf("Wrong input");
        exit(1);
    }
    return !((shell(argv[1]) || shell(argv[2])) && shell(argv[3]));
}