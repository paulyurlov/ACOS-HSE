#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        char * pEnd;
        int64_t x = (int64_t) strtol(argv[i], &pEnd, 10);
        if (!*argv[i] || *pEnd || 0) {
            printf("%d\n", -1);
        } else {
            if ((int8_t) x == x) {
                printf("%d\n", 1);
            } else if ((int16_t) x == x) {
                printf("%d\n", 2);
            } else if ((int32_t) x == x) {
                printf("%d\n", 4);
            } else {
                printf("%d\n", -1);
            }
        }
    }
}