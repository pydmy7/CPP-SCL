vector<vector<int>> permute(vector<int>& nums) {
    const int n = nums.size();

    std::vector<int> path;
    std::vector<bool> vis(n);
    std::vector<std::vector<int>> ans;
    auto dfs = [&](auto&& dfs, int u) -> void {
        if (u == n) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(dfs, u + 1);
                path.pop_back();
                vis[i] = false;
            }
        }
    };
    dfs(dfs, 0);

    return ans;
}