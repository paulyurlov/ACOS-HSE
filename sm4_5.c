void to_half_float(int value, unsigned short *hf) {
    short int sign = 0;
    int valu = value;
    if (value < 0) {
        sign = 1 << 15;
        valu = -value;
    }
    int sup = valu;
    int e = 0;
    int order = 0;
    while ((sup % 2 == 0) && (order <= 5)) {
        sup >>= 1;
        order++;
    }
    while (sup > 0) {
        sup >>= 1;
        e++;
    }
    if (e > 11) {
        *hf = sign | (31 << 10);
    } else {
        short int exp = e + order - 1 + 15;
        exp <<= 10;
        sup = valu;
        sup >>= order;
        short int m = (short int) sup;
        short int prev = m;
        while ((prev <= m) && (m != 0)) {
            m <<= 1;
            prev = m;
        }
        short int res = exp | m;
        *hf = sign | res;

    }
}