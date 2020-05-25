#include <stdio.h>

int check(unsigned int x) {
    int order = 0;
    while (x % 2 == 0) {
        if (order > 8 ) {
            break;
        }
        x = x / 2;
        order++;
    }
    if (x >> 24 == 0) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    unsigned int a;
    while (scanf("%u", &a) != EOF) {
        printf("%d\n", check(a));
    }
}