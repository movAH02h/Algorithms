#include <bits/stdc++.h>

using namespace std;

int n;
int a[100000];     //������
int tree[400004];  //������ ��������. � �������� �������� �����

//���������� ������ �� ������������ �������.
//v - ����� ������� �������; tl, tr - ������� ���������������� �������
void build_tree(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];    //����� ������� �� ������ �������� ����� ����� ��������
    } else {
        //tm - ������� ������� �������.
        //������� ����������� �� ��� ������� [tl; tm], [tm + 1; tr]
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

//������ �����
//l, r - ������� �������;
//v - ����� ������� �������; tl, tr - ������� ���������������� �������
int get_sum(int l, int r, int v, int tl, int tr) {
    //������� 1
    if (l <= tl && tr <= r) {
        return tree[v];
    }

    //������� 2
    if (tr < l || r < tl) {
        return 0;
    }

    //������� 3
    int tm = (tl + tr) / 2;
    return get_sum(l, r, v * 2,     tl,     tm)
         + get_sum(l, r, v * 2 + 1, tm + 1, tr);
}

//������ �����������
//idx - ������ ��������, val - ����� ��������
//v - ����� ������� �������; tl, tr - ������� ���������������� �������
void update(int idx, int val, int v, int tl, int tr) {
    //������� 1
    if (idx <= tl && tr <= idx) {    //�� ��, ��� � idx == tl == tr
        a[idx] = val;
        tree[v] = val;
        return;
    }

    //������� 2
    if (tr < idx || idx < tl) {
        return;
    }

    //������� 3
    int tm = (tl + tr) / 2;
    update(idx, val, v * 2,     tl,     tm);
    update(idx, val, v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int main() {
    //���� �������...

    build_tree(1, 0, n - 1);    //��������� ����� ������.
                                //��� ������� ������ ���������� ��� ���� ����������.

    //����� ������ ������� ���� get_sum(l, r, 1, 0, n - 1) � update(idx, val, 1, 0, n - 1);
}
