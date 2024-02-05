std::vector<int> getPhi(int n) {
    std::vector<int> phi(n + 1);
    std::iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    return phi;
}