#pragma once

#include <queue>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "shared.hpp"

inline long long dsu_find(std::vector<long long>& parent, long long u) {
    if (parent[u] != u) {
        parent[u] = dsu_find(parent, parent[u]);
    }

    return parent[u];
};


inline void dsu_union(std::vector<long long>& parent, std::vector<long long>& size, long long u, long long v) {
    u = dsu_find(parent, u);
    v = dsu_find(parent, v);

    if (u == v) {
        return;
    }

    if (size[v] > size[u]) {
        std::swap(u, v);
    }

    parent[v] = u;
    size[u] += size[v];
}


inline WeightedGraph kruskal(const WeightedGraph& graph) {
    size_t n = graph.size() - 1;

    std::vector<Edge> edges;
    for (int u = 1; u <= n; ++u) {
        for (const auto& [v, w] : graph[u]) {
            if (u < v) { // don't double add here
                edges.push_back({ u, v, w });
            }
        }
    }

    std::ranges::sort(edges, {}, [](auto& a) {
        return std::get<2>(a);
    });

    WeightedGraph answer(n+1);
    std::vector<long long> parent(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    std::vector<long long> size(n+1, 1);
    for (auto& e : edges) {
        auto& [u, v, w] = e;

        if (dsu_find(parent, u) != dsu_find(parent, v)) {
            answer[u].push_back({v, w});
            answer[v].push_back({u, w});
            dsu_union(parent, size, u, v);
        }
    }

    return answer;
}

inline WeightedGraph prim(const WeightedGraph& graph) {
    size_t n = graph.size() - 1;
    WeightedGraph answer(n + 1);
    std::vector<bool> seen(n+1, false);
    int seen_count = 1;

    auto cmp = [](const auto& a, const auto& b) {
        return std::get<2>(a) > std::get<2>(b);
    };

    std::priority_queue<
        Edge,
        std::vector<Edge>,
        decltype(cmp)
    > pq(cmp);

    for (const auto& [v, w] : graph[1]) {
        pq.push({ 1, v, w });
    }
    seen[1] = true;

    while (seen_count < n) {
        auto [from, to, w0] = pq.top();
        pq.pop();

        if (!seen[to]) {
            seen[to] = true;
            seen_count++;

            answer[from].push_back({ to, w0 });
            answer[to].push_back({ from, w0 });

            for (const auto& [child, w1] : graph[to]) {
                if (seen[child]) continue;
                pq.push({ to, child, w1 });
            }
        }
    }

    return answer;
}

