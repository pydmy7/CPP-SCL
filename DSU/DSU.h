#ifndef __DSU_H__
#define __DSU_H__

#include <vector>
#include <numeric>
#include <cassert>

namespace scl {

    class DSU {
    private:
        int n, cnt;
        std::vector<int> p, sz;

    public:
        explicit DSU(const int n) : n(n), cnt(n), p(n), sz(n, 1) {
            std::iota(p.begin(), p.end(), 0);
        }

        int find(const int x) {
            assert(0 <= x && x < n);
            return x == p[x] ? x : p[x] = find(p[x]);
        }
        bool same(const int a, const int b) {
            assert(0 <= a && a < n);
            assert(0 <= b && b < n);
            return find(a) == find(b);
        }
        int size(const int x) {
            assert(0 <= x && x < n);
            return sz[find(x)];
        }
        int count() {
            return cnt;
        }
        void merge(const int a, const int b) {
            assert(0 <= a && a < n);
            assert(0 <= b && b < n);
            int pa = find(a), pb = find(b);
            if (pa == pb) return;
            sz[pb] += sz[pa];
            p[pa] = pb;
            --cnt;
        }
    };

}  // namespace scl

#endif  // __DSU_H__