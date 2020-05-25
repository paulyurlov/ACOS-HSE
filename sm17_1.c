#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    if (argc != 4 ) {
        printf("Wrong input");
        exit(1);
    }
    int pid, fd;
    pid = fork();
    if (!pid) {
        fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
        fd = open(argv[2], O_RDONLY);
        dup2(fd, 0);
        close(fd);
        execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "Exec failed\n");
        _exit(1);
    }
    wait(NULL);
    return 0;
}