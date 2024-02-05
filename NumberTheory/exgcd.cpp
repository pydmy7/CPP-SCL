template<typename T>
constexpr std::array<T, 3> exgcd(T a, T b) {
    if (b == 0) {
        return std::array<T, 3>{a, 1, 0};
    }

    auto [g, x, y] = exgcd(b, a % b);
    return std::array<T, 3>{g, y, x - a / b * y};
}