std::pair<bool, std::vector<int>> topSort(const std::vector<std::vector<int>>& G) {
    const int n = G.size();

    std::vector<int> din(n);
    for (int u = 0; u < n; ++u) {
        for (int v : G[u]) {
            ++din[v];
        }
    }

    std::queue<int> Q;
    for (int i = 0; i < n; ++i) {
        if (din[i] == 0) {
            Q.push(i);
        }
    }

    std::vector<int> lines;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        lines.push_back(u);

        for (int v : G[u]) {
            if (--din[v] == 0) {
                Q.push(v);
            }
        }
    }

    return {n == (int)lines.size(), lines};
}