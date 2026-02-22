#pragma once

#include <vector>

inline std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<int> ans = { start_node };
    std::vector<int> current = { start_node };
    std::vector<bool> visited(graph.size(), false);

    visited[start_node] = true;

    while (!current.empty()) {
        std::vector<int> next;

        for (const auto v : current) {
            for (const auto u : graph[v]) {
                if (!visited[u]) {
                    next.push_back(u);
                    visited[u] = true;
                    ans.push_back(u);
                }
            }
        }

        current = std::move(next);
    }

    return ans;
}

inline std::vector<int> dfs(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<int> ans;
    std::vector<bool> visited(graph.size(), false);

    auto do_dfs = [&](auto&& self, int node) {
        if (visited[node]) return;

        visited[node] = true;
        ans.push_back(node);

        for (const auto v : graph[node]) {
            self(self, v);
        }
    };

    do_dfs(do_dfs, start_node);
    return ans;
}
