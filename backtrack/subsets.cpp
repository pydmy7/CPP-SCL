vector<vector<int>> subsets(vector<int>& nums) {
    const int n = nums.size();
    
    std::vector<int> path;
    std::vector<std::vector<int>> res;
    auto dfs = [&](auto&& dfs, int u) -> void {
        if (u == n) {
            res.push_back(path);
            return;
        }

        dfs(dfs, u + 1);

        path.push_back(nums[u]);
        dfs(dfs, u + 1);
        path.pop_back();
    };
    dfs(dfs, 0);

    return res;
}

vector<vector<int>> subsets(vector<int>& nums) {
    const int n = nums.size();

    std::vector<int> path;
    std::vector<std::vector<int>> res;
    auto dfs = [&](auto&& dfs, int u) -> void {
        res.push_back(path);
        
        if (u == n) {
            return;
        }

        for (int i = u; i < n; ++i) {
            path.push_back(nums[i]);
            dfs(dfs, i + 1);
            path.pop_back();
        }
    };
    dfs(dfs, 0);

    return res;
}