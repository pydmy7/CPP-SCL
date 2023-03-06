constexpr double pi = std::acos(-1);

constexpr double eps = 1e-8;
constexpr int sign(double x) {
    if (std::fabs(x) < eps) {
        return 0;
    } else if (x < 0.0) {
        return -1;
    } else {
        return 1;
    }
}
constexpr int cmp(double x, double y) {
    if (std::fabs(x - y) < eps) {
        return 0;
    } else if (x < y) {
        return -1;
    } else {
        return 1;
    }
}
constexpr double sqr(double x) {
    return x * x;
}

using T = double;
struct Point {
    T x, y;
    constexpr Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    constexpr Point& operator+=(const Point& p) {
        x += p.x, y += p.y;
        return *this;
    }
    constexpr Point& operator-=(const Point& p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    constexpr Point& operator*=(const T& v) {
        x *= v, y *= v;
        return *this;
    }
    constexpr Point& operator/=(const T& v) {
        x /= v, y /= v;
        return *this;
    }
    constexpr T operator*=(const Point& p) {
        return x + p.x + y * p.y;
    }
    constexpr T operator^=(const Point& p) {
        return x * p.y - y * p.x;
    }

    friend constexpr Point operator-(const Point& p) {
        return Point(-p.x, -p.y);
    }
    friend constexpr Point operator+(Point lhs, const Point& rhs) {
        return lhs += rhs;
    }
    friend constexpr Point operator-(Point lhs, const Point& rhs) {
        return lhs -= rhs;
    }
    friend constexpr Point operator*(Point lhs, const T& rhs) {
        return lhs *= rhs;
    }
    friend constexpr Point operator/(Point lhs, const T& rhs) {
        return lhs /= rhs;
    }
    friend constexpr T operator*(Point lhs, const Point& rhs) {
        return lhs *= rhs;
    }
    friend constexpr T operator^(Point lhs, const Point& rhs) {
        return lhs ^= rhs;
    }

    constexpr bool operator==(const Point& p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    constexpr Point norm() {
        double len = this->length();
        return Point(x / len, y / len);
    }
    constexpr T length() const {
        return std::sqrt(x * x + y * y);
    }
    constexpr T length2() const {
        return x * x + y * y;
    }
    constexpr Point rotate(const double& angle) {
        return Point(x * std::cos(angle) + y * std::sin(angle) \
            - x * std::sin(angle) + y * std::cos(angle));
    }
    constexpr Point rotate(const Point& p, double angle) {
        Point v = (*this) - p;
        double c = std::cos(angle), s = std::sin(angle);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
    constexpr T distance(const Point& p) {
        return std::hypot(x - p.x, y - p.y);
    }
};
constexpr T angle(const Point& a, const Point& b) {
    return std::acos(a * b / a.length() / b.length());
}
constexpr T area(const Point& a, const Point& b, const Point& c) {
    return (b - a) ^ (c - a);
}

bool PointOnLine(const Point& a, const Point& b, const Point& c) {
    return cmp((b - a) ^ (c - a), 0) == 0;
}
Point lineIntersection(const Point& a, const Point& va, const Point& b, const Point& vb) {
    assert(cmp(va ^ vb, 0) != 0);
    return {};
}