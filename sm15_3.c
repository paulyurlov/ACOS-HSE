#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            printf("-1\n");
            continue;
        }
        off_t size = lseek(fd, 0, SEEK_END);
        if (size == 0) {
            printf("0\n");
            continue;
        }
        char* array = (char*)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (array == MAP_FAILED) {
            close(fd);
            continue;
        }
        unsigned long long quantity_of_strings = 0;
        for (size_t j = 0; j < size / sizeof(char); ++j) {
            if (j != size / sizeof(char) - 1) {
                if (array[j] == '\n') {
                    quantity_of_strings++;
                }
            } else {
                quantity_of_strings++;
            }
        }
        munmap(array, size);
        printf("%llu\n", quantity_of_strings);
        close(fd);
    }
    return 0;
}