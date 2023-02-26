#ifndef __RMQ_H__
#define __RMQ_H__

#include <vector>
#include <cassert>
#include <algorithm>

namespace scl {

    template<typename T, class CMP = std::less<T>>
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

        T rangeCmp(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = std::__lg(r + 1 - l);
            return std::min(a[k][l], a[k][r + 1 - (1 << k)], cmp);
        }
    };

}  // namespace scl

#endif  // __RMQ_H__