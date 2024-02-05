template<typename T = int>
struct Fraction {
    T num, den;

    constexpr void norm() {
        T gcd = std::gcd(num, den);
        num /= gcd, den /= gcd;
    }

    constexpr Fraction() : Fraction(0, 1) {}
    constexpr Fraction(T num) : Fraction(num, 1) {}
    constexpr Fraction(T num, T den) {
        assert(den != 0);
        if (den < 0) {
            den = -den;
            num = -num;
        }
        this->num = num;
        this->den = den;
        norm();
    }

    constexpr double toDouble() const {
        return 1.0 * num / den;
    }

    constexpr Fraction& operator+=(const Fraction& rhs) & {
        T lcm = std::lcm(den, rhs.den);
        num = num * (lcm / den) + rhs.num * (lcm / rhs.den);
        den = lcm;
        norm();
        return *this;
    }
    constexpr Fraction& operator-=(const Fraction& rhs) & {
        T lcm = std::lcm(den, rhs.den);
        num = num * (lcm / den) - rhs.num * (lcm / rhs.den);
        den = lcm;
        norm();
        return *this;
    }
    constexpr Fraction& operator*=(const Fraction& rhs) & {
        num *= rhs.num;
        den *= rhs.den;
        norm();
        return *this;
    }
    constexpr Fraction& operator/=(const Fraction& rhs) & {
        assert(rhs.num != 0);
        num *= rhs.den;
        den *= rhs.num;
        if (den < 0) {
            num = -num;
            den = -den;
        }
        norm();
        return *this;
    }
    
    friend constexpr Fraction operator+(Fraction lhs, const Fraction& rhs) {
        return lhs += rhs;
    }
    friend constexpr Fraction operator-(Fraction lhs, const Fraction& rhs) {
        return lhs -= rhs;
    }
    friend constexpr Fraction operator*(Fraction lhs, const Fraction& rhs) {
        return lhs *= rhs;
    }
    friend constexpr Fraction operator/(Fraction lhs, const Fraction& rhs) {
        return lhs /= rhs;
    }
    friend constexpr Fraction operator-(const Fraction& a) {
        return Fraction(-a.num, a.den);
    }
    
    friend constexpr bool operator==(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den == rhs.num * lhs.den;
    }
    friend constexpr bool operator!=(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den != rhs.num * lhs.den;
    }
    friend constexpr bool operator<(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den < rhs.num * lhs.den;
    }
    friend constexpr bool operator>(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den > rhs.num * lhs.den;
    }
    friend constexpr bool operator<=(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den <= rhs.num * lhs.den;
    }
    friend constexpr bool operator>=(const Fraction& lhs, const Fraction& rhs) {
        return lhs.num * rhs.den >= rhs.num * lhs.den;
    }

    friend constexpr std::istream& operator>>(std::istream& is, Fraction& a) {
        T num, den;
        is >> num;
        is.ignore(1, '/');
        is >> den;
        a = Fraction(num, den);
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const Fraction& a) {
        os << a.num << '/' << a.den;
        return os;
    }
};