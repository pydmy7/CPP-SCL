template<typename T = int,
    const char op = 'S'>
class Fenwick {
private:
    const int n;
    std::vector<T> tr;

public:
    explicit Fenwick(int n) : n(n), tr(n, 0) {}
    explicit Fenwick(const std::vector<T>& init) : n(init.size()) {
        static_assert(op == 'S' || op == 'D', "fenwick-op can only be 'S' or 'D'");
        tr.resize(n, 0);
        if constexpr (op == 'S') [[likely]] {
            for (int i = 0; i < n; ++i) {
                add(i, init[i]);
            }
        } else [[unlikely]] {
            add(0, init[0]);
            for (int i = 1; i < n; ++i) {
                add(i, init[i] - init[i - 1]);
            }
        }
    }

    void add(int idx, T val) {
        assert(0 <= idx && idx <= n);
        for (int i = idx + 1; i <= n; i += i & -i) {
            tr[i - 1] += val;
        }
    }
    void add(int l, int r, T val) {
        assert(l <= r);
        add(l, val), add(r + 1, -val);
    }
    T query(int idx) {
        assert(-1 <= idx && idx < n);
        T sum = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) {
            sum += tr[i - 1];
        }
        return sum;
    }
    T query(int l, int r) {
        // if (l > r) return 0;
        assert(l <= r);
        return query(r) - query(l - 1);
    }
    int kth(T x) {  // min pos s.t. sum[0, pos] >= x
        assert(x >= 0);
        int lg = std::__lg(n), pos = 0;
        for (int i = 1 << lg; i > 0; i >>= 1) {
            if (pos + i <= n && tr[pos + i - 1] < x) {
                pos += i, x -= tr[pos - 1];
            }
        }
        return pos;
    }
};