int maxMatchOfBipartiteGraph(const std::vector<std::vector<int>>& adj, int nl, int nr) {
    std::vector<int> lid(nr, -1);
    std::vector<bool> vis(nr, false);
    
    auto isMatch = [&](auto&& self, int u) -> bool {
        for (int v : adj[u]) {
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            if (lid[v] == -1 || self(self, lid[v])) {
                lid[v] = u;
                return true;
            }
        }
        return false;
    };
    
    int ans = 0;
    for (int i = 0; i < nl; ++i) {
        std::fill(vis.begin(), vis.end(), false);
        if (isMatch(isMatch, i)) {
            ++ans;
        }
    }
    return ans;
};