#include <bits/stdc++.h>

void _search(std::vector<int>& temp, int k, int n)
{
    if (k == n + 1)
    {
        for (int i = 0; i < temp.size(); ++i)
        {
            std::cout << temp[i] << " ";
        }
        std::cout << "\n";
    }
    else
    {
        // ������� � �������� � ����������� �������� ��������
        temp.push_back(k);
        _search(temp, k + 1, n);
        //������� � �������� ��� ���������� �������� ��������
        temp.pop_back();
        _search(temp, k + 1, n);
    }
}

int main()
{
    int n = 3;
    std::vector<int> temp;
    _search(temp, 1, n);
    return 0;
}
