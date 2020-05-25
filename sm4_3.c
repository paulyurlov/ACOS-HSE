FPClass fpclassf(float value, int *psign) {
    unsigned int* x = (unsigned int*) &value;
    unsigned int sign = *x >> 31;
    unsigned int M = *x & 8388607;
    unsigned int e = (*x << 1) >> 24;
    if ((e != 255) && (e != 0)) {
        *psign = sign;
        return FFP_NORMALIZED;
    }
    if (!e) {
        *psign = sign;
        if (!M) {
            return FFP_ZERO;
        } else {
            return FFP_DENORMALIZED;
        }
    }
    if (e == 255) {
        if (!M) {
            *psign = sign;
            return FFP_INF;
        } else {
            *psign = 0;
            return FFP_NAN;
        }
    }
    return FFP_NORMALIZED;
}