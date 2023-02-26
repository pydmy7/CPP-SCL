#ifndef __LAZYSEGMENTTREE_H__
#define __LAZYSEGMENTTREE_H__

#include <vector>

namespace scl {

// modify `Node pushdown LazySegmentTree`
template<typename T = long long>
class LazySegmentTree {
private:
    struct Node {
        T info = 0;  // info
        T tag = 0;  // tag
        void upd([[maybe_unused]] int l, [[maybe_unused]] int r, T v) {  // upd
            info = (r - l + 1) * v;
            tag = v;
        }
        Node merge(const Node& lhs, const Node& rhs) {  // merge
            Node ret;
            ret.info = lhs.info + rhs.info;
            return ret;
        }
    };

    const int n;
    std::vector<Node> tr;
    
    void pushdown(int l, int r, int rt) {
        if (tr[rt].tag == 0) {  // if (tag == Tag()) return;
            return;
        }

        int m = (l + r) >> 1;
        tr[rt << 1].upd(l, m, tr[rt].tag);  // ...
        tr[rt << 1 | 1].upd(m + 1, r, tr[rt].tag);  // ...
        tr[rt].tag = 0;  // tag = Tag();
    }

    template<typename... V>
    void update(int L, int R, int l, int r, int rt, const V&... v) {
        if (L <= l && r <= R) {
            tr[rt].upd(l, r, v...);
            return;
        }

        pushdown(l, r, rt);
        int m = (l + r) >> 1;
        if (L <= m) {
            update(L, R, l, m, rt << 1, v...);
        }
        if (m < R) {
            update(L, R,  m + 1, r, rt << 1 | 1, v...);
        }
        tr[rt] = tr[rt].merge(tr[rt << 1], tr[rt << 1 | 1]);
    }

    Node query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return tr[rt];
        }

        pushdown(l, r, rt);
        Node ret;
        int m = (l + r) >> 1;
        if (L <= m) {
            ret = ret.merge(ret, query(L, R, l, m, rt << 1));
        }
        if (m < R) {
            ret = ret.merge(ret, query(L, R, m + 1, r, rt << 1 | 1));
        }
        return ret;
    }

public:
    explicit LazySegmentTree(const int n, const T v = 0) : LazySegmentTree(std::vector<T>(n, v)) {}
    explicit LazySegmentTree(const std::vector<T>& init) : n(init.size()), tr(4 << std::__lg(n)) {
        auto build = [&](auto&& self, int l, int r, int rt) -> void {
            if (l == r) {
                tr[rt].info = init[l & r];  //  add more info
                return;
            }

            int m = (l + r) >> 1;
            self(self, l, m, rt << 1);
            self(self, m + 1, r, rt << 1 | 1);
            tr[rt] = tr[rt].merge(tr[rt << 1], tr[rt << 1 | 1]);
        };
        build(build, 0, n - 1, 1);
    }

    template<typename... V>
    void upd(const int L, const int R, const V&... v) {
        update(L, R, 0, n - 1, 1, v...);
    }

    Node qry(const int L, const int R) {
        return query(L, R, 0, n - 1, 1);
    }
};

}  // namespace scl

#endif  // __LAZYSEGMENTTREE_H__