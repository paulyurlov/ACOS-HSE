#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    off_t size = lseek(fd, 0, SEEK_END);
    double* array = (double*)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (array == MAP_FAILED) {
        close(fd);
        return 1;
    }
    double avg = 0.0;
    size_t count = size / sizeof(double);
    for (size_t i = 0; i < count; ++i) {
        avg += array[i];
    }
    printf("%a\n", avg / count);
    munmap(array, size);
    close(fd);
    return 0;
}