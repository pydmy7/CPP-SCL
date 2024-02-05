// 区间并
std::vector<std::pair<int, int>> intervalMerge(std::vector<std::pair<int, int>> intervals) {
    if (!std::is_sorted(intervals.begin(), intervals.end())) {
        std::sort(intervals.begin(), intervals.end());
    }
    std::vector<std::pair<int, int>> merged;
    for (auto [l, r] : intervals) {
        if (merged.empty() || merged.back().second < l) {
            merged.push_back({l, r});
        } else {
            merged.back().second = std::max(merged.back().second, r);
        }
    }
    return merged;
}

// 区间交
std::vector<std::pair<int, int>> intervalIntersection(std::vector<std::pair<int, int>> A, std::vector<std::pair<int, int>> B) {
    if (!std::is_sorted(A.begin(), A.end())) {
        std::sort(A.begin(), A.end());
    }
    if (!std::is_sorted(B.begin(), B.end())) {
        std::sort(B.begin(), B.end());
    }
    std::vector<std::pair<int, int>> res;
    for (std::size_t i = 0, j = 0; i < A.size() && j < B.size();) {
        int l = std::max(A[i].first, B[j].first), r = std::min(A[i].second, B[j].second);
        if (l <= r) {
            res.push_back({l, r});
        }
        if (A[i].second <= B[j].second) {
            ++i;
        } else {
            ++j;
        }
    }
    return res;
}