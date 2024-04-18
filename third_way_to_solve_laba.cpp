#include <bits/stdc++.h>

// ----------------------------------------------- Lava third method -------------------------------------------------------------
const int ADD = 1;
const int REMOVE = -1;

class Point
{
public:
    int x, y;
    Point(){}
    Point(int _x, int _y) : x(_x), y(_y){}
};

class Rectangle
{
public:
    Point first_point;
    Point second_point;

    Rectangle(int x1, int y1, int x2, int y2) : first_point(x1, y1), second_point(x2, y2){}
};

class Node
{
public:
    int value;
    int left_index;
    int right_index;
    Node* left;
    Node* right;

    Node(int value, Node* left, Node* right, int left_index, int right_index)
    {
        this->value = value;
        this->left_index = left_index;
        this->right_index = right_index;
        this->left = left;
        this->right = right;
    }
};
// 1. ---------------------------------- Переделать SegmenetTreeEvent - сделать тоже самое, только без этого класса ----------------------------------
// Скорее всего надо к Point добавить левый он или правый и сделать аналогичный алгоритм, только с точками прямоугольника. Вот и все ю
// 2. Переделать mid везде, где он ищется
// 3. Переименовать функции
class SegmentTreeEvent
{
public:
    int x;
    int begin_y;
    int end_y;
    int status;

    SegmentTreeEvent(int x, int begin_y, int end_y, int status)
    {
        this->x = x;
        this->begin_y = begin_y;
        this->end_y = end_y;
        this->status = status;
    }
};

int bin_search(std::vector<int>& v, int target)
{
    int left = 0;
    int right = v.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (v[mid] > target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left - 1;
}

void compress_coordinates(std::vector<int>& compress_x, std::vector<int>& compress_y, std::vector<Rectangle>& rectangles)
{
    std::set<int> set_x;
    std::set<int> set_y;

    for (Rectangle element : rectangles)
    {
        set_x.insert(element.first_point.x);
        set_x.insert(element.second_point.x);

        set_y.insert(element.first_point.y);
        set_y.insert(element.second_point.y);
    }

    for (int element : set_x)
    {
        compress_x.push_back(element);
    }

    for (int element : set_y)
    {
        compress_y.push_back(element);
    }
}

Node* insert_node(Node* node, int _start, int _end, int value)
{
    if (_start <= node->left_index && node->right_index <= _end)
    {
        return new Node(node->value + value, node->left, node->right, node->left_index, node->right_index);
    }

    if (_end <= node->left_index || node->right_index <= _start)
    {
        return node;
    }

    Node* new_node = new Node(node->value, node->left, node->right, node->left_index, node->right_index);

    new_node->left = insert_node(new_node->left, _start, _end, value);
    new_node->right = insert_node(new_node->right, _start, _end, value);

    return new_node;
}

Node* build_tree(std::vector<int>& arr, int left_index, int right_index)
{
    if (left_index + 1 == right_index)
    {
        return new Node(arr[left_index], nullptr, nullptr, left_index, right_index);
    }

    int mid = (left_index + right_index) / 2;
    Node* left = build_tree(arr, left_index, mid);
    Node* right = build_tree(arr, mid, right_index);

    return new Node(left->value + right->value, left, right, left_index, right_index);
}

std::vector<Node*> build_persistant_segment_tree(std::vector<Rectangle>& data_rectangles, std::vector<int>& compress_x, std::vector<int>& compress_y)
{
    if (data_rectangles.size() == 0)
    {
        return {};
    }

    std::vector<SegmentTreeEvent> tree_events;
    std::vector<Node*> tree_roots;
    for (Rectangle element : data_rectangles)
    {
        int x1_idx = bin_search(compress_x, element.first_point.x);
        int y1_idx = bin_search(compress_y, element.first_point.y);
        int x2_idx = bin_search(compress_x, element.second_point.x);
        int y2_idx = bin_search(compress_y, element.second_point.y);

        tree_events.push_back(SegmentTreeEvent(x1_idx, y1_idx, y2_idx, ADD));
        tree_events.push_back(SegmentTreeEvent(x2_idx, y1_idx, y2_idx, REMOVE));
    }

    std::sort(tree_events.begin(), tree_events.end(), [](SegmentTreeEvent first, SegmentTreeEvent second){ return first.x < second.x; });

    std::vector<int> arr(compress_y.size(), 0);
    Node* root = build_tree(arr, 0, compress_y.size());
    int x_end = tree_events[0].x;

    for (SegmentTreeEvent event : tree_events)
    {
        if (x_end != event.x)
        {
            tree_roots.push_back(root);
            x_end = event.x;
        }
        root = insert_node(root, event.begin_y, event.end_y, event.status);
    }
    tree_roots.push_back(root);

    return tree_roots;
}


int get_answer(Node* node, int target)
{
    if (node != nullptr)
    {
        int mid = (node->left_index + node->right_index) / 2;
        if (target < mid)
        {
            return node->value + get_answer(node->left, target);
        }
        else
        {
            return node->value + get_answer(node->right, target);

        }
    }
    return 0;
}

std::vector<int> persistent_segment_tree(std::vector<Point>& data_points, std::vector<int>& compress_x, std::vector<int>& compress_y, std::vector<Node*> tree_roots)
{
    std::vector<int> answer(data_points.size());
    if (tree_roots.size() == 0) return answer;

    for (int i = 0; i < data_points.size(); ++i)
    {
        int pos_x = bin_search(compress_x, data_points[i].x);
        int pos_y = bin_search(compress_y, data_points[i].y);

        if (pos_x == -1 || pos_y == -1)
        {
            answer[i] = 0;
        }
        else
        {
            answer[i] = get_answer(tree_roots[pos_x], pos_y);
        }
    }
    return answer;
}

int main()
{
    int number_rect;
    std::cin >> number_rect;
    std::vector<Rectangle> rectangles;

    for (int i = 0; i < number_rect; ++i)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        rectangles.push_back(Rectangle(x1, y1, x2, y2));
    }

    int number_points;
    std::cin >> number_points;
    std::vector<Point> points;

    for (int i = 0; i < number_points; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        points.push_back(Point(x, y));
    }

    std::vector<int> compress_x;
    std::vector<int> compress_y;

    compress_coordinates(compress_x, compress_y, rectangles);

    std::vector<Node*> tree_roots = build_persistant_segment_tree(rectangles, compress_x, compress_y);

    std::vector<int> answer = persistent_segment_tree(points, compress_x, compress_y, tree_roots);

    for (int element : answer)
    {
        std::cout << element << " ";
    }

    return 0;
}
