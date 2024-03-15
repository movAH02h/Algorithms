#include <bits/stdc++.h>

void dfs(int current_vertex, std::vector<std::vector<int>>& graph, std::vector<int>& answer, std::vector<int>& visited)
{
    visited[current_vertex] = 1;

    for (int other_vertex : graph[current_vertex])
    {
        if (!visited[other_vertex])
        {
            dfs(other_vertex, graph, answer, visited);
        }
    }

    answer.push_back(current_vertex);
}

int main()
{
    int vertexes, edges;
    std::cin >> vertexes >> edges;

    std::vector<std::vector<int>> graph(vertexes);
    std::vector<int> answer;
    std::vector<int> visited(vertexes, 0);
    for (int i = 0; i < edges; ++i)
    {
        int v, u;
        std::cin >> v >> u;
        graph[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < vertexes; ++i)
    {
        if (!visited[i])
        {
            dfs(i, graph, answer, visited);
        }
    }


    reverse(answer.begin(), answer.end());
    for (int v : answer)
    {
        std::cout << v + 1 << " ";
    }
    return 0;
}

/*
Тест:
5 7
2 1
2 5
2 4
3 1
5 3
4 3
4 5
*/
