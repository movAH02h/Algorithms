#include <bits/stdc++.h>

int p[1000];

int height[10000] = {0};

// disjoint set
int find_set(int a)
{
    return (p[a] == a) ? a : p[a] = find_set(p[a]);
}

void union_sets(int a, int b)
{
    int a_set = find_set(a);
    int b_set = find_set(b);

    if (height[a_set] > height[b_set])
    {
        std::swap(a_set, b_set);
    }

    height[b_set] = std::max(height[b_set], height[a_set] + 1);
    p[a_set] = b_set;
}

void init_set(int vertex)
{
    for (int i = 0;i < vertex + 1; ++i)
    {
        p[i] = i;
    }
}
void init_graph(std::vector<std::vector<int>>& graph, int edges)
{
     for (int i = 0; i < edges; ++i)
     {
         int v, u, w;
         std::cin >> v >> u >> w;
         graph.push_back({v, u, w});
     }
}

void boruvka(std::vector<std::vector<int>>& graph, int vertex, int edges)
{
    int trees = vertex;
    std::vector<std::vector<int>> answer;
    int sum = 0;

    while (trees > 1)
    {
        std::vector<int> smallest_edge(vertex + 1, -1);
        for (int i = 0; i < graph.size(); ++i)
        {
            int setA = find_set(graph[i][0]);
            int setB = find_set(graph[i][1]);

            if (setA != setB)
            {
                if (smallest_edge[setA] == -1 ||
                    graph[smallest_edge[setA]][2] > graph[i][2])
                {
                    smallest_edge[setA] = i;
                }

                if (smallest_edge[setB] == -1 ||
                    graph[smallest_edge[setB]][2] > graph[i][2])
                {
                    smallest_edge[setB] = i;
                }
            }
        }

        for (int i = 1; i < vertex + 1; ++i)
        {
            if (smallest_edge[i] != -1)
            {
                int setA = find_set(graph[smallest_edge[i]][0]);
                int setB = find_set(graph[smallest_edge[i]][1]);

                if (setA != setB)
                {
                    answer.push_back({graph[smallest_edge[i]][0], graph[smallest_edge[i]][1], graph[smallest_edge[i]][2]});
                    sum += graph[smallest_edge[i]][2];
                    union_sets(setA, setB);
                    trees--;
                }
            }

        }

    }
    std::cout << "Minimum weight of spinning tree: " << sum << std::endl;
    std::cout << "Edges of spinning tree:\n";
    for (size_t i = 0; i < answer.size(); ++i)
    {
        for (size_t j = 0; j < answer[i].size(); ++j)
        {
            std::cout << answer[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int main()
{
    std::vector<std::vector<int>> graph;
    int v, e;
    std::cin >> v >> e;
    init_graph(graph, e);
    init_set(v);

    boruvka(graph, v, e);
    return 0;
}
