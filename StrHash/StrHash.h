#ifndef __STRHASH_H__
#define __STRHASH_H__

#include <array>
#include <vector>
#include <string>
#include <cassert>

namespace scl {

    class StrHash {
    private:
        typedef long long ll;
        static constexpr std::array<int, 2> p = {223333333, 773333333};
        static constexpr std::array<int, 2> mod = {1000000033, 1000002233};
        
        const int n;
        std::vector<std::vector<ll>> h, rh, pw;
        
    public:
        explicit StrHash(const std::string& s) : n(s.size()), h(2, std::vector<ll>(n + 1)), rh(2, std::vector<ll>(n + 1)), pw(h) {
            pw[0][0] = pw[1][0] = 1ll;
            for (int i = 1; i <= n; ++i) {
                pw[0][i] = pw[0][i - 1] * p[0] % mod[0];
                pw[1][i] = pw[1][i - 1] * p[1] % mod[1];
            }
            for (int i = 1; i <= n; ++i) {
                h[0][i] = (h[0][i - 1] * p[0] + s[i - 1]) % mod[0];
                h[1][i] = (h[1][i - 1] * p[1] + s[i - 1]) % mod[1];
            }
            for (int i = n - 1; i >= 0; --i) {
                rh[0][i] = (rh[0][i + 1] * p[0] + s[i]) % mod[0];
                rh[1][i] = (rh[1][i + 1] * p[1] + s[i]) % mod[1];
            }
        }

        ll get(const int l, const int r) {
            assert(0 <= l && l <= r && r < n);
            return (((h[0][r + 1] - h[0][l] * pw[0][r - l + 1] % mod[0] + mod[0]) % mod[0]) << 30) \
                + (h[1][r + 1] - h[1][l] * pw[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
        }
        ll rget(const int l, const int r) {
            assert(0 <= l && l <= r && r < n);
            return (((rh[0][l] - rh[0][r + 1] * pw[0][r - l + 1] % mod[0] + mod[0]) % mod[0]) << 30) \
                + (rh[1][l] - rh[1][r + 1] * pw[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
        }
    };

}  // namespace scl

#endif  // __STRHASH_H__