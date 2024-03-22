#include <bits/stdc++.h>

struct comparator
{
    bool operator()(const std::tuple<int, int, int>& first, const std::tuple<int, int, int>& second)
    {
        if (std::get<0>(first) == std::get<0>(second))
        {
            return std::get<1>(first) > std::get<1>(second);
        }
        return std::get<0>(first) < std::get<0>(second);
    }
};

int main()
{
    int n;
    std::cin >> n;

    auto comp = comparator();

    std::vector<std::tuple<int, int, int>> input;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        input.push_back(std::make_tuple(a, b, i));
    }

    std::sort(input.begin(), input.end(), comp);
    int max_right = 0;
    int min_right = 1000000001;
    std::vector<int> contained(n);
    std::vector<int> containes(n);

    for (std::tuple<int, int, int> element : input)
    {
        int a, b, i;
        std::tie(a, b, i) = element;

        if (b <= max_right)
        {
            contained[i] = 1;
        }

        max_right = std::max(max_right, b);
    }

    for (auto it = input.rbegin(); it != input.rend(); ++it)
    {
        int a, b, i;
        std::tie(a, b, i) = *it;

        if (b >= min_right)
        {
            containes[i] = 1;
        }

        min_right = std::min(min_right, b);
    }

    for (int element : containes)
    {
        std::cout << element << " ";
    }
    std::cout << "\n";
    for (int element : contained)
    {
        std::cout << element << " ";
    }




    return 0;
}
