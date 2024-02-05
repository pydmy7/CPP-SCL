struct Edge {
    int v, d;
    bool operator<(const Edge& rhs) const {
        return !(d < rhs.d);
    }
};

std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& adj, int s) {
    constexpr int inf = std::numeric_limits<int>::max();
    const int n = adj.size();

    std::vector<int> dist(n, inf);
    std::vector<bool> done(n);

    std::priority_queue<Edge> pq;
    pq.push({s, 0});
    dist[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();
        if (done[u]) {
            continue;
        }
        done[u] = true;
        for (auto [v, d] : adj[u]) {
            if (dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;
                pq.push({v, dist[v]});
            }
        }
    }

    for (int& d : dist) {
        if (d == inf) {
            d = -1;
        }
    }

    return dist;
}