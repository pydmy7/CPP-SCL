class LcaTree {
private:
    int lg;
    const int n;
    std::vector<std::vector<int>> f;
    std::vector<int> dep;
    std::vector<int> dis;

public:
    LcaTree(const std::vector<std::vector<std::pair<int, int>>>& adj, int root = 0) : n(adj.size()) {
        lg = std::__lg(n);
        f.resize(n, std::vector<int>(lg + 1, -1));
        dep.resize(n);
        dis.resize(n);

        auto dfs = [&](auto&& dfs, int u, int fa) -> void {
            for (auto [v, d] : adj[u]) {
                if (v == fa) {
                    continue;
                }
                dep[v] = dep[u] + 1;
                dis[v] = dis[u] + d;
                f[v][0] = u;
                dfs(dfs, v, u);
            }
        };
        dfs(dfs, root, -1);

        for (int j = 1; j <= lg; ++j) {
            for (int i = 0; i < n; ++i) {
                f[i][j] = f[i][j - 1] == -1 ? -1 : f[f[i][j - 1]][j - 1];
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            std::swap(u, v);
        }
        for (int d = dep[u] - dep[v], i = lg; i >= 0; --i) {
            if (d >> i & 1) {
                u = f[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = lg; i >= 0; --i){
            if (f[u][i] != -1 && f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }
    
    int lca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }

    // dist is used to calculate edge weights
    // If it's point power: dis[a] + dis[b] - dis[lca(a, b)] + pointweight[lca(a, b)]
    int dist(int a, int b) {
        return dis[a] + dis[b] - 2 * dis[lca(a, b)];
    }
};