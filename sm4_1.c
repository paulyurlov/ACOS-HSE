#include <stdio.h>

int main() {
    float a;
    while (scanf("%f", &a) != EOF) {
        unsigned int* x = (unsigned int*) &a;
        printf("%u ", *x >> 31);
        printf("%u ", (*x << 1) >> 24);
        printf("%x\n", (*x & 8388607));
    }
}