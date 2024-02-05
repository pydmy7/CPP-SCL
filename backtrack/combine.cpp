vector<vector<int>> combine(int n, int k) {
    std::vector<int> path;
    std::vector<std::vector<int>> res;
    auto dfs = [&](auto&& dfs, int u) -> void {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }

        if (u > n || path.size() + n - u + 1 < k) {
            return;
        }

        dfs(dfs, u + 1);
        
        path.push_back(u);
        dfs(dfs, u + 1);
        path.pop_back();
    };
    dfs(dfs, 1);

    return res;
}

vector<vector<int>> combine(int n, int k) {
    std::vector<int> path;
    std::vector<std::vector<int>> res;
    auto dfs = [&](auto&& dfs, int u) -> void {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }

        if (u > n || path.size() + n - u + 1 < k) {
            return;
        }
        
        for (int i = u; i <= n; ++i) {
            path.push_back(i);
            dfs(dfs, i + 1);
            path.pop_back();
        }
    };
    dfs(dfs, 1);

    return res;
}