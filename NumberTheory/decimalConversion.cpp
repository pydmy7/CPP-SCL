// decimalConversion
std::string atob(const std::string& s, int a, int b) {
    std::vector<int> A;
    for (char c : s) {
        if (std::isdigit(c)) {
            A.push_back(c - '0');
        } else if (std::isupper(c)) {
            A.push_back(c - 'A' + 10);
        } else {
            assert(std::islower(c));
            A.push_back(c - 'a' + 36);
        }
    }
    std::reverse(A.begin(), A.end());

    std::vector<int> B;
    while (!A.empty()) {
        int rem = 0;  //余数
        for (int i = A.size() - 1; i >= 0; --i) {
            A[i] += rem * a;
            rem = A[i] % b;
            A[i] /= b;
        }
        B.push_back(rem);
        while (!A.empty() && A.back() == 0) {
            A.pop_back();
        }
    }
    std::reverse(B.begin(),B.end());

    std::string res;
    for (int bi : B) {
        if (bi < 10) {
            res += bi + '0';
        } else if (bi < 36) {
            res += bi - 10 + 'A';
        } else {
            res += bi - 36 + 'a';
        }
    }

    return res;
}