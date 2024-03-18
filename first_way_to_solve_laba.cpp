#include <bits/stdc++.h>

bool check_in_rect(int x1, int y1, int x2, int y2, int x, int y)
{
    return (x >= x1 && x < x2 && y < y2 && y >= y1) == 1 ? true : false;
}

int main()
{
    std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> rectangles;

    int number_rect = 0;
    std::cin >> number_rect;

    for (int i = 0; i < number_rect; ++i)
    {
        // x1 and y1 - лева€ нижн€€ точка, x2 and y2 - права€ верхн€€ точка
        int x1,y1,x2,y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        rectangles.push_back({{x1, y1}, {x2, y2}});
    }


    int queries = 0;
    std::cin >> queries;

    for (int i = 0; i < queries; ++i)
    {
        int answer = 0;
        int dot_x, dot_y;
        std::cin >> dot_x >> dot_y;

        for (int i = 0; i < rectangles.size(); ++i)
        {
            bool check_result = check_in_rect(rectangles[i].first.first,
                                              rectangles[i].first.second,
                                              rectangles[i].second.first,
                                              rectangles[i].second.second,
                                              dot_x,
                                              dot_y);
            if (check_result)
            {
                answer++;
            }
        }

        std::cout << "Dot ( " << dot_x << ", " << dot_y << " ) in " << answer << " rectangles\n";
    }
    return 0;
}

