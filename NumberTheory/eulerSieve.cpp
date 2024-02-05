std::vector<int> minprimefactor, primes;
void eulerSieve(int n) {
    minprimefactor.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minprimefactor[i] == 0) {
            minprimefactor[i] = i;
            primes.push_back(i);
        }
        
        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            minprimefactor[i * p] = p;
            if (p == minprimefactor[i]) {
                break;
            }
        }
    }
}
