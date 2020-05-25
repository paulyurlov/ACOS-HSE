#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc !=4) {
        fprintf(stderr, "Invalid arguments count\n");
        exit(1);
    }
    errno = 0;
    char * err;
    long a = strtol(argv[2], &err, 10);
    if (errno) {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }
    if (*err) {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }
    errno = 0;
    long b = strtol(argv[3], &err, 10);
    if (errno) {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }
    if (*err) {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }
    if (a <= 0 || b <=0) {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }
    if (a >= b) {
        return 0;
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        close(fd);
        fprintf(stderr, "Failed to get size\n");
        exit(1);
    }
    if (size == 0) {
        return 0;
    }
    char* array = (char* )mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (array == MAP_FAILED) {
        fprintf(stderr, "Failed to allocate memory\n");
        close(fd);
        exit(1);
    }
    long lines = 0;
    for (off_t i = 0; i < size; ++i) {
        if (array[i] == '\n') {
            ++lines;
        }
    }
    if (a >= lines) {
        munmap(array, size);
        close(fd);
        return 0;
    }
    --a;
    --b;
    if (b > lines) {
        b = lines;
    }
    long iter = 0;
    long intervals[lines + 2];
    intervals[0] = -1;
    intervals[lines + 1] = size + 2;
    for (off_t i = 0; i < size; ++i) {
        if (array[i] == '\n') {
            intervals[++iter] = i;
        }
    }
    for (long i = b; i > a; --i ) {
        for (off_t j = 1 + intervals[i - 1]; j < intervals[i] + 1; ++j) {
            if (j == size) {
                break;
            }
            printf("%c", array[j]);
        }
    }
    return 0;
}