#include <bits/stdc++.h>

int bin_search(std::vector<int>& arr, int low, int high, int target)
{
    if (high >= low) {

        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            return bin_search(arr, low, mid - 1, target);

        return  bin_search(arr, mid + 1, high, target);
    }

    return high;
}

/*
Тест:
4
2 2 6 8
5 4 9 10
4 0 11 6
8 2 12 12
6
2 2
12 12
10 4
5 5
2 10
2 8
*/

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> rectangles;
    std::set<int> x_set;
    std::set<int> y_set;

    // сжатие координат путем получения только уникальных координат + только координат, которые даны
    for (int i = 0;i < n; ++i)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        x_set.insert(x1);
        x_set.insert(x2);
        y_set.insert(y1);
        y_set.insert(y2);
        rectangles.push_back({{x1, y1}, {x2, y2}});
    }
    x_set.insert(0);
    y_set.insert(0);

    // создаем векторы, чтобы можно было находить индексы
    std::vector<int> x_vector(x_set.begin(), x_set.end());
    std::vector<int> y_vector(y_set.begin(), y_set.end());

    // Пусть кол-во строк - это y ось, а столбцы - это x ось
    std::vector<std::vector<int>> matrix(y_vector.size(), std::vector<int>(x_vector.size(), 0));


    for (int i = 0; i < rectangles.size(); ++i)
    {
        auto [x1, y1] = rectangles[i].first;
        auto [x2, y2] = rectangles[i].second;

        // x - столбцы в матрице, а y - строки в матрице
        int x_left = bin_search(x_vector, 0, x_vector.size() - 1, x1),
        x_right = bin_search(x_vector, 0, x_vector.size() - 1, x2),
        y_left = bin_search(y_vector, 0, y_vector.size() - 1, y1),
        y_right = bin_search(y_vector, 0, y_vector.size() - 1, y2);

        // Увеличиваем занчения в найденном квадрате
        for (int i = y_left; i < y_right; ++i)
        {
            for (int j = x_left;j < x_right; ++j)
            {
                matrix[i][j]++;
            }
        }
    }

    // обрабатываем запросы
    int questions = 0;
    std::cin >> questions;
    for (int i = 0; i < questions; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        // ищем индекс столбца (в векторе с x координатами) и индекс строки ( в векторе с y кооринатами )
        // в bin_search если координаты нет ( в нашем урезаннгом списке ), то возвращаем левую границу
        // в бин поиске, если коорднаты нет, то low - верхняя граница точки, а hogh - нижняя граница.
        // Мы должны вернуть нижнюю для веной индексации
        int index_row = bin_search(y_vector, 0, y_vector.size() - 1, y);
        int index_column = bin_search(x_vector, 0, x_vector.size() - 1, x);

        std::cout << "Answer: " << matrix[index_row][index_column] << "\n";
    }

    return 0;
}
