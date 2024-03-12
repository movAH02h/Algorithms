#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int p[1000] = {0};
int h[1000] = {0};

//system of disjoint set
int find_set(int v)
{
    return (p[v] == v) ? v : p[v] = find_set(p[v]);
}

void union_set(int a, int b)
{
    a = find_set(a), b = find_set(b);
    if (h[a] > h[b])
    {
        std::swap(a, b);
    }
    h[b] = std::max(h[b], h[a] + 1);
    p[a] = b;
}

void init(int n)
{
    for (int i = 0; i < n + 1; ++i)
    {
        p[i] = i;
    }
}

struct Edge
{
    Edge(){}
    Edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w){}

    int a;
    int b;
    int w;
};

class comparator
{
public:
    bool operator()(const Edge& a, const Edge& b)
    {
        return a.w < b.w;
    }
};


int main()
{
    int n;
    std::cin >> n;
    init(n);
    std::vector<Edge> edges;
    for (int i = 0; i < n; ++i)
    {
        //first vertex, second vertex, weight
        int a, b, w;
        std::cin >> a >> b >> w;
        edges.push_back(Edge(a,b,w));
    }

    comparator comp;
    std::sort(edges.begin(), edges.end(), comp);

    std::vector<Edge> answer;

    for (auto [a, b, w] : edges)
    {
        if (p[a] != p[b])
        {
            answer.push_back(Edge(a,b,w));
            union_set(a, b);
        }
    }

    for (auto [a,b,w] : answer)
    {
        std::cout << a << " " << b << " " << w << std::endl;
    }

    return 0;
}
