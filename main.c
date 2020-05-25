
#include <stdio.h>

void myhypot(double a, double b, double* r);

int main() {
    double* r = 0;
    double a = *r;
    myhypot(4.0, 3.0, r);
    printf("%lf\n", a);
}