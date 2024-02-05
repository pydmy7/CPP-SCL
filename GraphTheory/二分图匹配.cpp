bool isBipartiteGraph(const std::vector<std::vector<int>>& adj) {
    const int n = adj.size();
    std::vector<int> color(n, 0);

    auto dfs = [&](auto&& dfs, int u, int c) -> bool {
        color[u] = c;
        for (int v : adj[u]) {
            if ((color[v] && color[v] == color[u]) || (!color[v] && !dfs(dfs, v, 3 ^ c))) {
                return false;
            }
        }
        return true;
    };

    for (int i = 0; i < n; ++i) {
        if (!color[i] && !dfs(dfs, i, 1)) {
            return false;
        }
    }
    return true;
}