#include <bits/stdc++.h>

/*
Graph:
6
7
1 2
2 3
3 4
4 5
2 4
5 1
1 6
*/

int cur_time = 0;

void dfs_first(int vertex, std::vector<std::vector<int>>& edges, std::vector<int>& visited, std::vector<std::pair<int, int>>& tout)
{
    cur_time++;
    visited[vertex] = 1;

    for (int to : edges[vertex])
    {
        if (!visited[to])
        {
            dfs_first(to, edges, visited, tout);
        }
    }

    tout[vertex].first = cur_time++;
    tout[vertex].second = vertex;
}

void dfs_second(int vertex, std::vector<std::vector<int>>& edges, std::vector<int>& visited)
{
    std::cout << vertex + 1 << " ";
    visited[vertex] = 1;

    for (int to : edges[vertex])
    {
        if (!visited[to])
        {
            dfs_second(to, edges, visited);
        }
    }
}

int main()
{
    std::cout << "Enter a number of vertex\n";
    int v; std::cin >> v;
    std::cout << "Enter a number of edges\n";
    int e; std::cin >> e;

    std::vector<std::vector<int>> edges(v);
    std::vector<int> visited(v);
    std::vector<std::pair<int, int>> tout(v);

    for (int i = 0; i < e; ++i)
    {
        int in, to;
        std::cin >> in >> to;
        edges[in - 1].push_back(to - 1);
    }

    dfs_first(0, edges, visited, tout);

    std::sort(tout.begin(), tout.end(), std::greater<std::pair<int, int>>());
    std::vector<std::vector<int>> new_edges(v);

    // reverse all edges
    for (size_t i = 0; i < edges.size(); ++i)
    {
        for (size_t j = 0;j < edges[i].size(); ++j)
        {
            new_edges[edges[i][j]].push_back(i);
        }
    }

    // reset visited vector
    visited = std::vector<int>(v, 0);

    for (std::pair<int, int> time : tout)
    {
        if (!visited[time.second])
        {
            std::cout << "SCC: ";
            dfs_second(time.second, new_edges, visited);
            std::cout << "\n";
        }
    }
    return 0;

}
