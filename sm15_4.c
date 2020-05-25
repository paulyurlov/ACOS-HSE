#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    long long result = 0;
    off_t size = lseek(fd, 0, SEEK_END);
    off_t difference = lseek(fd, 0, SEEK_END);
    off_t offset = 0;
    uint8_t * array;
    printf("%lld\n", size);
    if (size == 0) {
        printf("0\n");
        printf("0\n");
        return 0;
    }
    off_t left = 0;
    off_t right = size;
    off_t mid;
    while (left <= right) {
        mid = (right - left)/2 + left;
        array = (uint8_t *)mmap(NULL, mid, PROT_READ, MAP_SHARED, fd, offset);
        if (array != MAP_FAILED ) {
            munmap(array, mid);
            array = (uint8_t *)mmap(NULL, mid + 1, PROT_READ, MAP_SHARED, fd, offset);
            if (array == MAP_FAILED) {
                size = mid;
                break;
            } else {
                munmap(array, mid + 1);
            }
        }
        array = (uint8_t *)mmap(NULL, mid, PROT_READ, MAP_SHARED, fd, offset);
        if (array == MAP_FAILED) {
            right = mid - 1;
        }
        else {
            munmap(array, mid);
            left = mid + 1;
        }
    }
    printf("%lld\n", size);
    int kek = 0;
    unsigned int bit = 127;
    unsigned int high = 128;
    unsigned int tmp = 0;
    unsigned int shift = 0;
    off_t steps = difference / size;
    for (off_t step = 0; step < steps; ++step) {
        array = (uint8_t *)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, size * kek);
        for (long long i = 0; i < size / sizeof(uint8_t); ++i) {
            tmp |= (array[i] & bit) << shift;
            shift += 7;
            if ((array[i] & high) == 0) {
                if ((shift < 32) && ((array[i] & 0x40) != 0)) {
                    tmp |= (~0 << shift);
                }
                result += (int) tmp;
                tmp = 0;
                shift = 0;
            }
        }
        munmap(array, size);
        ++kek;
    }
    if (difference - steps * size > 0) {
        array = (uint8_t *)mmap(NULL, difference - steps * size, PROT_READ, MAP_SHARED, fd, steps * size);
        for (off_t j = 0; j < (difference - steps * size) / sizeof(uint8_t); ++j) {
            tmp |= (array[j] & bit) << shift;
            shift += 7;
            if ((array[j]& high) == 0) {
                if ((shift < 32) && ((array[j] & 0x40) != 0)) {
                    tmp |= (~0 << shift);
                }
                result += (int) tmp;
                tmp = 0;
                shift = 0;
            }
        }
        munmap(array, difference);
    }
    printf("%lld\n", result);
    return 0;
}