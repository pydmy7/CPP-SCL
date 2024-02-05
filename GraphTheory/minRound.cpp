// require: dijkstra
int minRound(std::vector<std::vector<Edge>> adj, int st, int ed) {
    auto item = std::partition(adj[st].begin(), adj[st].end(), [&ed](const Edge& edge) {
        return edge.v != ed;
    });

    int mind = item->d;
    for (auto it = std::next(item); it != adj[st].end(); ++it) {
        mind = std::min(mind, it->d);
    }

    adj[st].erase(item, adj[st].end());

    auto dist = dijkstra(adj, st);

    int ret = dist[ed] == -1 ? -1 : mind + dist[ed];
    return ret;
}