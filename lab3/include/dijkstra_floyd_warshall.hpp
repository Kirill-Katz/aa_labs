#pragma once

#include <climits>
#include <queue>
#include <utility>
#include <vector>
#include "shared.hpp"


inline std::vector<long long> dijkstra(const WeightedGraph& graph, int src_node) {
    constexpr long long INF = (1LL << 60);

    size_t n = graph.size() - 1;

    std::vector<long long> dist(n+1, INF);
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

inline std::vector<std::vector<long long>> floyd_warshall(const WeightedGraph& graph) {
    constexpr long long INF = (1LL << 60);

    size_t n = graph.size() - 1;
    std::vector<std::vector<long long>> dp(n+1, std::vector<long long>(n+1, INF));

    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
    }

    for (int u = 1; u <= n; ++u) {
        for (const auto& [v, w] : graph[u]) {
            dp[u][v] = std::min(dp[u][v], w);
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dp[i][k] >= INF) continue; // cannot reach k from i for now
            for (int j = 1; j <= n; ++j) {
                if (dp[k][j] >= INF) continue; // cannot reach j from k for now
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    return dp;
}



