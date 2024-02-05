int power(int a, int b, int p) {
    // 底数优化
    a = a % p;

    // 指数优化
    // if (isPrime(p) && std::gcd(a, p) == 1) {
    //     b = b % (p - 1);
    // }

    int res = 1 % p;
    for (; b; b >>= 1, a = 1LL * a * a % p) {
        if (b & 1) {
            res = 1LL * res * a % p;
        }
    }

    return res;
}