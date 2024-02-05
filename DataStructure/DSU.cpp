class DSU {
private:
    int n, cnt;
    std::vector<int> p, sz;

public:
    DSU(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        this->cnt = n;
        sz.assign(n, 1);
        p.resize(n);
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        assert(0 <= x && x < n);
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return find(a) == find(b);
    }
    int size(int x) {
        assert(0 <= x && x < n);
        return sz[find(x)];
    }
    int count() {
        return cnt;
    }
    bool merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int pa = find(a), pb = find(b);
        if (pa == pb) {
            return false;
        }
        sz[pa] += sz[pb];
        p[pb] = pa;
        --cnt;
        return true;
    }
};