#include <stdio.h>
#include <math.h>

int getdigits(int a) {
    int i = 0;
    int ans = 0;
    while (a > 0) {
        int b = a % 10;
        ans += b * (int)pow(7, i);
        a = a / 10;
        ++i;
    }
    return ans;
}

int main() {
    double a;
    double sign = 1;
    while (scanf("%lf", &a) != EOF) {
        if (a < 0) {
            sign = -1;
            a = -a;
        }
        double res = 0;
        int k = (int)a;
        double flt = a - k;
        res += getdigits(k);
        int i = -1;
        while (flt > 0) {
            int tmp = (int)(flt * 10);
            res += tmp * pow(7, i);
            flt = flt * 10 - tmp;
            if ((flt/10 >= 0.1) || (flt/10 == 0.0)) {
                break;
            }
            --i;
        }
        res = res * sign;
        printf("%.10g\n", res);
    }
}