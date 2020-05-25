#include <stdio.h>
#include <math.h>
#include <string.h>

typedef double (* funcptr_t) (double x);

typedef struct FunctionTable {
    char name[1000000];
    funcptr_t func;
} FunctionTable;

double solve(const FunctionTable* tab, int end, char* x, double in) {
    for (int i = 0; i < end; ++i) {
        if (strcmp(x, tab[i].name) == 0) {
            return (tab[i].func)(in);
        }
    }
    return NAN;
}
int main() {
    static const FunctionTable array[] = {{"sin", &sin}, {"cos", &cos}, {"exp", &exp},
                                        {"log", &log}, {"tan", &tan}, {"sqrt", &sqrt}};
    double x;
    char str[1000000];
    while (scanf("%s %lg", str, &x) == 2) {
        printf("%a\n", solve(array, (sizeof(array) / sizeof(FunctionTable)), str, x));
    }
}