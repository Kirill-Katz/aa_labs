#pragma once

#include <climits>
#include <queue>
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

inline std::vector<long long> dijkstra(const Graph& graph, int src_node) {
    size_t n = graph.size();

    std::vector<long long> dist(n, LLONG_MAX);
    dist[src_node] = 0;

    std::priority_queue<
        std::pair<long long, int>,
        std::vector<std::pair<long long, int>>,
        std::greater<>
    > pq;

    pq.push({0, src_node});

    while(!pq.empty()) {
        // O(1)
        auto [d, u] = pq.top();
        // O(log(v))
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                // O(log(v))
                pq.push({ dist[v], v });
            }
        }
    }

    // O(log(e)*(v + e)) because we traverse each vertex and each of their edges exactly once
    // and the number of elements in the heap is dependent on the number of edges not hte nubmer
    // of vertices

    return dist;
}

inline std::vector<std::vector<long long>> floyd_warshall(const Graph& graph) {
    std::vector<std::vector<std::vector<long long>>> dp;




}

