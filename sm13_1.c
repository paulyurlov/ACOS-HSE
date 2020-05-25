#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main() {
    int inlet;
    time_t sup1;
    time_t sup2;
    while (scanf("%d", &inlet) != EOF) {
        time_t now = time(NULL);
        if(__builtin_mul_overflow(inlet, 24 * 3600, &sup1) || __builtin_add_overflow(now, sup1, &sup2)) {
            printf("OVERFLOW\n");
            continue;
        }
        struct tm* local = localtime(&sup2);
        char str[20];
        strftime(str, 20, "%Y-%m-%d\n", local);
        printf("%s", str);
    }
    return 0;
}
