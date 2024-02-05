//辛普森积分
constexpr double eps = 1E-7;  //设置为题目精度要求的1/100
double F(double x) {
    return ;
}
double simpon(double a, double b){
    double mid = (a + b) / 2.0;
    return (F(a) + 4 * F(mid) + F(b)) * (b - a) / 6.0;
}
double asr(double a, double b, double eps, double S) {
    double mid = (a + b) / 2.0;
    double L = simpon(a, mid), R = simpon(mid, b);
    if (std::fabs(L + R - S) <= 15.0 * eps) {
        return L + R + (L + R - S) / 15.0;
    }
    return asr(a, mid, eps / 2.0, L) + asr(mid, b, eps / 2.0, R);
}
double asr(double a, double b, double eps) {
    return asr(a, b, eps, simpon(a, b));
}