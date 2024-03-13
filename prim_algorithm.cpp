#include <bits/stdc++.h>

bool visited[100] = {false};
std::vector<std::pair<int, int>> graph[100];

class comparator
{
public:
    bool operator()(const std::tuple<int, int, int>& first, const std::tuple<int, int, int>& second)
    {
        return std::get<2>(first) < std::get<2>(second);
    }
};

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int v, u, w;
        std::cin >> v >> u >> w;
        graph[v].push_back({u, w});
    }

    int total_weight = 0;
    std::vector<std::tuple<int, int, int>> spann_graph;

    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, comparator> q;

    q.push(std::make_tuple(-1, 1, 0));

    while (!q.empty())
    {
        std::tuple<int, int, int> temp = q.top();
        q.pop();

        // откуда пришел - где нахожусь сейчас - расстояние
        int v = std::get<0>(temp), u = std::get<1>(temp), distance = std::get<2>(temp);

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;
        total_weight += distance;

        if (v != -1)
        {
            spann_graph.push_back(temp);
        }

        for (std::pair<int, int> element : graph[u])
        {
            int dest_vertex = element.first, weight = element.second;

            if (!visited[dest_vertex])
            {
                q.push(std::make_tuple(u, dest_vertex, weight));
            }
        }
    }

    std::cout << "Total weight of spinning graph: " << total_weight << std::endl;
    for (const std::tuple<int, int, int>& element : spann_graph)
    {
        int v, u, w;
        std::tie(v, u, w) = element;
        std::cout << v << " " << u << " " << w << std::endl;
    }

    return 0;
}
