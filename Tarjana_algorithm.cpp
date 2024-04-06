#include <bits/stdc++.h>
// https://yandex.ru/video/preview/7857507657907487533 - ссылка с объяснением
int id = 0;
int countSCC = 0;

void dfs(int vertex, std::vector<std::vector<int>> edges, std::vector<int>& ids, std::vector<int>& lows, std::vector<bool>& onStack, std::stack<int>& st)
{
    st.push(vertex);
    onStack[vertex] = true;

    ids[vertex] = lows[vertex] = id++;

    for (int element : edges[vertex])
    {
        if (ids[element] == -1)
        {
            dfs(element, edges, ids, lows, onStack, st);
        }
        if (onStack[element])
        {
            lows[vertex] = std::min(lows[vertex], lows[element]);
        }
    }

    if (ids[vertex] == lows[vertex])
    {
        while (true)
        {
            int node = st.top();
            st.pop();
            onStack[node] = false;
            lows[node] = ids[vertex];
            if (node == vertex) break;
        }
        countSCC++;
    }
}

int main()
{
    std::cout << "Enter a number of vertex:\n";
    int v;
    std::cin >> v;
    std::cout << "Enter a number of edges\n";
    int e;
    std::cin >> e;
    std::vector<std::vector<int>> edges(e);

    for (int i = 0; i < e; ++i)
    {
        int in, to;
        std::cin >> in >> to;
        edges[in - 1].push_back(to - 1);
    }

    std::vector<int> ids(v, -1); // äëÿ çàïèñè èäåíòèôèêàòîðà êàæäîãî óçëà

    // äëÿ çàïèñè íàèìåíüøåãî èíäåêñà (÷òîáû ìîæíî áûëî ïîíÿòü, ÷òî âåðøèíû ê îäíîé SCC îòíîñÿòñÿ)
    std::vector<int> lows(v);
    std::vector<bool> onStack(v, false);
    std::stack<int> st;

    for (int i = 0; i < v; ++i)
    {
        if (ids[i] == -1)
        {
            dfs(i, edges, ids, lows, onStack, st);
        }
    }


    for (int element : lows)
    {
        std::cout << element << " ";
    }
    return 0;
}
/*
Test:
8
13
1 2
2 1
1 3
2 4
3 4
5 3
4 5
4 6
5 6
5 7
7 6
6 8
8 7
*/

