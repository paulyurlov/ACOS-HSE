#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>

const unsigned I32_SIZE = 4;
const unsigned NUM_BASE = 10;

int main(int argc, char** argv){
    if (argc != 4) {
        return 1;
    }
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        return 2;
    }
    int rows = strtol(argv[2], NULL, NUM_BASE);
    int cols = strtol(argv[3], NULL, NUM_BASE);
    int off = lseek(fd, rows * cols * I32_SIZE - 1, SEEK_SET);
    if (off < 0) {
        return 5;
    }
    int res = write(fd, "", 1);
    if (res != 1) {
        return 4;
    }
    int32_t* array = (int32_t*)mmap(NULL, rows * cols * I32_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (array == MAP_FAILED) {
        close(fd);
        return 3;
    }
    int32_t value = 1;
    int k = 0;
    for (;;) {
        for (int i = k; i < (cols - k) && value <= rows * cols; ++i) {
            array[cols * k + i] = value++;
        }
        for (int i = k + 1; i < (rows - k) && value <= rows * cols; ++i) {
            array[(i + 1) * cols - 1 - k] = value++;
        }
        for (int i = k + 1; i < (cols - k) && value <= rows * cols; ++i) {
            array[(rows - k) * cols - 1 - i] = value++;
        }
        for (int i = k + 1; i < (rows - k - 1) && value <= rows * cols; ++i) {
            array[(rows - 1 - i) * cols + k] = value++;
        }
        if (value > rows * cols) {
            break;
        }
        ++k;
    }
#ifdef DEBUG 
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", array[i * cols + j]);
        }
        printf("\n");
    }
#endif
    munmap(array, rows * cols * I32_SIZE);
    close(fd);
    return 0;
}