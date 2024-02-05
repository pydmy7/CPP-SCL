template<typename T,
    class CMP = std::less<T>>
class RMQ {
private:
    const int n;
    const CMP cmp;
    std::vector<std::vector<T>> a;

public:
    explicit RMQ(const std::vector<T>& init) : n(init.size()), cmp(CMP()) {
        const int lg = std::__lg(n);
        a.assign(lg + 1, std::vector<T>(n));
        for (int j = 0; j <= lg; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                a[j][i] = (j == 0 ? init[i] : std::min(a[j - 1][i], a[j - 1][i + (1 << (j - 1))], cmp));
            }
        }
    }

    T rangeQuery(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        int k = std::__lg(r + 1 - l);
        return std::min(a[k][l], a[k][r + 1 - (1 << k)], cmp);
    }
};