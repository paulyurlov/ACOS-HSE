#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    if (argc != 6) {
        fprintf(stderr, "Invalid arguments count\n");
        exit(1);
    }
    int fd = open(argv[2], O_RDWR);
    if (fd < 0) {
        fd = creat(argv[2], 0666);
    }
    int K = atoi(argv[5]);
    int N = atoi(argv[1]);
    int D = atoi(argv[4]);
    int A0 = atoi(argv[3]);
    pid_t pid;
    ftruncate(fd, N * K * sizeof(int));
    close(fd);
    for (int i = 0; i < N; ++i) {
        int fd = open(argv[2], O_RDWR);
        if ((pid = fork()) < 0) {
            printf("Failed...\n");
            exit(1);
        } else if (pid == 0) {
            int An = A0 + i * D;
            for (int j = 0; j < K; ++j){
                lseek(fd, sizeof(int) * (i + j * N), SEEK_SET);
                write(fd, &An, sizeof(int));
                An += N * D;
            }
            close(fd);
            exit(0);
        }
    }
    while(wait(NULL) > 0) {

    }
    return 0;
}   