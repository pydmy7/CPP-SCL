#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>


namespace geometry {

template<typename T>
struct Point {
    T x;
    T y;
    Point(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {}
    
    template<typename U>
    operator Point<U>() {
        return Point<U>{U(x), U(y)};
    }
    Point &operator+=(const Point& p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(const Point& p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(const T& v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(const T& v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point{-x, -y};
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T& b) {
        return a *= b;
    }
    friend Point operator*(const T& a, Point b) {
        return b *= a;
    }
    friend Point operator/(Point a, const T& b) {
        return a /= b;
    }
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<typename T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T>& a_ = Point<T>(), const Point<T>& b_ = Point<T>()) : a(a_), b(b_) {}
};

template<typename T>
int sgn(const Point<T>& a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<typename T>
T dot(const Point<T>& a, const Point<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T cross(const Point<T>& a, const Point<T>& b) {
    return a.x * b.y - a.y * b.x;
}

template<typename T>
T square(const Point<T>& p) {
    return dot(p, p);
}

template<typename T>
double length(const Point<T>& p) {
    return std::sqrt(square(p));
}

template<typename T>
double length(const Line<T>& l) {
    return length(l.a - l.b);
}

template<typename T>
Point<T> normalize(const Point<T>& p) {
    return p / length(p);
}

template<typename T>
double angle(const Point<T>& a, const Point<T>& b) {
    return std::acos(1.0 * dot(a, b) / (length(a) * length(b)));
}

template<typename T>
Point<T> rotate(const Point<T>& a, double rad = 0.0, const Point<T>& o = {0, 0}) {
    T x = (a.x - o.x) * std::cos(rad) - (a.y - o.y) * std::sin(rad) + o.x;
    T y = (a.x - o.x) * std::sin(rad) + (a.y - o.y) * std::cos(rad) + o.y;
    return Point<T>{x, y};
}

template<typename T>
Line<T> rotate(const Line<T>& l, double rad = 0.0, const Point<T>& o = {0, 0}) {
    return Line<T>{rotate(l.a, rad, o), rotate(l.b, rad, o)};
}

template<typename T>
double distance(const Point<T>& a, const Point<T>& b) {
    return length(a - b);
}

template<typename T>
double distancePL(const Point<T>& p, const Line<T>& l) {
    return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

template<typename T>
double distancePS(const Point<T>& p, const Line<T>& l) {
    if (dot(p - l.a, l.b - l.a) < 0) {
        return distance(p, l.a);
    }
    if (dot(p - l.b, l.a - l.b) < 0) {
        return distance(p, l.b);
    }
    return distancePL(p, l);
}

template<typename T>
double distanceSS(const Line<T>& l1, const Line<T>& l2) {
    if (std::get<0>(segmentIntersection(l1, l2)) != 0) {
        return 0.0;
    }
    return std::min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

inline int onPolygonGrid(const std::vector<Point<int>>& p) {
    int cnt = 0;
    for (int n = static_cast<int>(p.size()), i = 0; i < n; ++i) {
        auto a = p[i], b = p[(i + 1) % n];
        cnt += std::gcd(std::abs(a.x - b.x), std::abs(a.y - b.y));
    }
    return cnt;
}

inline int inPolygonGrid(const std::vector<Point<int>>& p) {
    int cnt = 0;
    for (int n = static_cast<int>(p.size()), i = 0; i < n; ++i) {
        auto a = p[i], b = p[(i + 1) % n], c = p[(i + 2) % n];
        cnt += b.y * (a.x - c.x);
    }
    cnt = std::abs(cnt);
    return (cnt - onPolygonGrid(p)) / 2 + 1;
}

template<typename T>
bool parallel(const Point<T>& a, const Point<T>& b) {
    return cross(a, b) == 0;
}

template<typename T>
bool parallel(const Line<T>& l1, const Line<T>& l2) {
    return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}

template<typename T>
bool pointOnLineLeft(const Point<T>& p, const Line<T>& l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<typename T>
Point<T> lineIntersection(const Line<T>& l1, const Line<T>& l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<typename T>
bool pointOnSegment(const Point<T>& p, const Line<T>& l) {
    return cross(p - l.a, l.b - l.a) == 0
        && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<typename T>
double polygonArea(const std::vector<Point<T>>& p) {
    if (p.size() < 3) {
        return 0.0;
    }
    double area = 0.0;
    for (int n = static_cast<int>(p.size()), i = 0; i < n; ++i) {
        area += cross(p[i], p[(i + 1) % n]);
    }
    return area / 2.0;
}

template<typename T>
std::vector<Point<T>> getPolygonHull(std::vector<Point<T>> p) {
    std::vector<Point<T>> h, l;
    std::sort(p.begin(), p.end(), [&](auto a, auto b) {
        if (a.x != b.x) {
            return a.x < b.x;
        } else {
            return a.y < b.y;
        }
    });
    p.erase(std::unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) {
        return p;
    }
    
    for (auto&& a : p) {
        while (h.size() > 1 && cross(a - h.back(), a - h[h.size() - 2]) <= 0) {
            h.pop_back();
        }
        while (l.size() > 1 && cross(a - l.back(), a - l[l.size() - 2]) >= 0) {
            l.pop_back();
        }
        l.emplace_back(a);
        h.emplace_back(a);
    }
    
    l.pop_back();
    std::reverse(h.begin(), h.end());
    h.pop_back();
    l.insert(l.end(), h.begin(), h.end());
    return l;
}

template<typename T>
bool pointInPolygon(const Point<T>& a, const std::vector<Point<T>>& p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 1;
}

template<typename T>
bool segmentInPolygon(const Line<T>& l, const std::vector<Point<T>>& p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

template<typename T>
bool polygonInPolygon(std::vector<Point<T>> polygon1, std::vector<Point<T>> polygon2) {
    if (polygonArea(polygon1) > polygonArea(polygon2)) {
        std::swap(polygon1, polygon2);
    }
    return std::all_of(polygon1.begin(), polygon1.end(), [&polygon2](auto&& point) {
        return pointInPolygon(point, polygon2);
    });
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<typename T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T>& l1, const Line<T>& l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

template<typename T>
std::vector<Point<T>> halfPlaneIntersection(std::vector<Line<T>> lines) {
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        
        return cross(d1, d2) > 0;
    });
    
    std::deque<Line<T>> ls;
    std::deque<Point<T>> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.emplace_back(l);
            continue;
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }
        
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        
        ps.emplace_back(lineIntersection(ls.back(), l));
        ls.emplace_back(l);
    }
    
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.emplace_back(lineIntersection(ls[0], ls.back()));
    
    return std::vector(ps.begin(), ps.end());
}

}



int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cout << "gometry\n";

    return 0;
}
