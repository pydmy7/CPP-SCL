template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template<int P>
class ModInt {
private:
    int x;
    static int mod;

    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return mod;
        }
    }

    // assume -P <= x < 2P
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

public:
    constexpr ModInt() : x{} {}
    constexpr ModInt(i64 x) : x{norm(x % getMod())} {}
    
    constexpr static void setMod(int mod_) {
        mod = mod_;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr ModInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr ModInt& operator*=(const ModInt& rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr ModInt& operator+=(const ModInt& rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt& rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr ModInt& operator/=(const ModInt& rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) {
        return lhs *= rhs;
    }
    friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) {
        return lhs += rhs;
    }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) {
        return lhs -= rhs;
    }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) {
        return lhs /= rhs;
    }

    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) {
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

template<>
int ModInt<0>::mod = 1;

template<int V, int P>
constexpr ModInt<P> CInv = ModInt<P>(V).inv();

using Z = ModInt<0>;