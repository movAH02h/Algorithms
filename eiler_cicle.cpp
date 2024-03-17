#include <bits/stdc++.h>

std::vector<int> answer;

void eiler(int current_vertex, std::vector<std::pair<int, int>>* graph, std::vector<int>& visited)
{
    for (int i = 0; i < graph[current_vertex].size(); ++i)
    {
        int to = graph[current_vertex][i].first;
        int idx = graph[current_vertex][i].second;

        if (!visited[idx])
        {
            visited[idx] = 1;
            eiler(to, graph, visited);
        }
    }

    answer.push_back(current_vertex + 1);
}
/*
Test:

4 4
1 2
2 3
3 4
4 1

*/

int main()
{
    int v, e;
    std::cin >> v >> e;

    std::vector<std::pair<int, int>> graph[v];
    std::vector<int> visited(e, 0);

    for (int i = 0; i < e;  ++i)
    {
        int in, to;
        std::cin >> in >> to;
        graph[in - 1].push_back({to - 1, i});
        graph[to - 1].push_back({in - 1, i});
    }

    eiler(0, graph, visited);

    for (int i = 0; i < answer.size(); ++i)
    {
        std::cout << answer[i] << " ";
    }

    return 0;
}

