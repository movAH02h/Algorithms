#include <bits/stdc++.h>

void dfs(std::vector<int>& h, std::vector<int>& d, std::vector<std::vector<int>>& graph, std::vector<int>& visited, int current_vertex, int parent)
{
    visited[current_vertex] = 1;
    h[current_vertex] = d[current_vertex] = (parent == -1) ? 0 : (h[parent] + 1);

    for (int next_vertex: graph[current_vertex])
    {
        if (next_vertex != parent)
        {
            if (!visited[next_vertex])
            {
                dfs(h, d, graph, visited, next_vertex, current_vertex);
                d[current_vertex] = std::min(d[current_vertex], d[next_vertex]);

                if (h[current_vertex] < d[next_vertex])
                {
                    std::cout << "Bridge: " << current_vertex + 1 << "-" << next_vertex + 1 << "\n";
                }
            }
            else
            {
                d[current_vertex] = std::min(d[current_vertex], h[next_vertex]);
            }
        }
    }
}
/*
Тест:

10 12
1 2
1 4
2 4
2 10
2 9
2 3
3 4
4 5
5 7
5 6
7 6
6 8
*/

int main()
{
    int v, e;
    std::cin >> v >> e;

    std::vector<int> h(v, -1);
    std::vector<int> d(v, 1000000);
    std::vector<int> visited(v, 0);

    std::vector<std::vector<int>> graph(v);

    for (int i = 0; i < e; ++i)
    {
        int in, to;
        std::cin >> in >> to;
        graph[in - 1].push_back(to - 1);
        graph[to - 1].push_back(in - 1);
    }

    dfs(h, d, graph, visited, 0, -1);


    return 0;
}

