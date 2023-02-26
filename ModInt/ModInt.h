#ifndef __ModInt_H__
#define __MOdInt_H__

#include <cassert>
#include <iostream>

namespace scl {

    template<int P = 998244353>
    struct ModInt {
        // consteval -> constexpr  since C++20
        static constexpr bool isPrime(int x) {
            if (x < 2) {
                return false;
            }
            
            for (int i = 2; i <= x / i; ++i) {
                if (x % i == 0) {
                    return false;
                }
            }
            return true;
        }
        static_assert(isPrime(P));

        using i64 = long long;

        int x;
        
        constexpr ModInt() : x{} {}
        constexpr ModInt(i64 x) : x{norm(x % P)} {}
        
        // assume -P <= x < 2P
        constexpr int norm(int x) const {
            if (x < 0) {
                x += P;
            }
            if (x >= P) {
                x -= P;
            }
            return x;
        }
        constexpr int val() const {
            return x;
        }
        explicit constexpr operator int() const {
            return x;
        }
        constexpr ModInt operator-() const {
            ModInt res;
            res.x = norm(P - x);
            return res;
        }
        constexpr ModInt power(i64 n) const {
            ModInt tmp = *this, ret = 1;
            for (; n; n >>= 1) {
                if (n & 1) {
                    ret *= tmp;
                }
                tmp *= tmp;
            }
            return ret;
        }
        constexpr ModInt inv() const {
            assert(x != 0);
            return power(P - 2);
        }
        constexpr ModInt& operator*=(ModInt rhs) {
            x = 1LL * x * rhs.x % P;
            return *this;
        }
        constexpr ModInt& operator+=(ModInt rhs) {
            x = norm(x + rhs.x);
            return *this;
        }
        constexpr ModInt& operator-=(ModInt rhs) {
            x = norm(x - rhs.x);
            return *this;
        }
        constexpr ModInt& operator/=(ModInt rhs) {
            return *this *= rhs.inv();
        }
        
        friend constexpr ModInt operator*(ModInt lhs, ModInt rhs) {
            ModInt res = lhs;
            res *= rhs;
            return res;
        }
        friend constexpr ModInt operator+(ModInt lhs, ModInt rhs) {
            ModInt res = lhs;
            res += rhs;
            return res;
        }
        friend constexpr ModInt operator-(ModInt lhs, ModInt rhs) {
            ModInt res = lhs;
            res -= rhs;
            return res;
        }
        friend constexpr ModInt operator/(ModInt lhs, ModInt rhs) {
            ModInt res = lhs;
            res /= rhs;
            return res;
        }
        
        friend constexpr bool operator==(ModInt lhs, ModInt rhs) {
            return lhs.val() == rhs.val();
        }
        friend constexpr bool operator!=(ModInt lhs, ModInt rhs) {
            return lhs.val() != rhs.val();
        }
        
        friend constexpr std::istream& operator>>(std::istream& is, ModInt& a) {
            i64 v;
            is >> v;
            a = ModInt(v);
            return is;
        }
        friend constexpr std::ostream& operator<<(std::ostream& os, const ModInt& a) {
            return os << a.val();
        }
    };

}  // namespace scl

#endif  // __ModInt_H__