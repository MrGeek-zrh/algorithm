#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <cstring>

using namespace std;

const int N = 100010;
const long M = -1e9;
int a[N] = { M };

// 第k次插入的数的索引
map<int, int> kth_map;

int length = 0;
int kth = 0;

// 从idx开始向上调整
int up(int idx)
{
    int current_idx = idx;
    int parent_idx = current_idx / 2;
    while (parent_idx >= 1) {
        if (a[parent_idx] > a[current_idx]) {
            int tmp;
            tmp = a[parent_idx];
            a[parent_idx] = a[current_idx];
            a[current_idx] = tmp;
            current_idx = parent_idx;
            parent_idx = current_idx / 2;
        } else {
            // 新插入的不会破坏现有的小根堆
            break;
        }
    }
    return current_idx;
}

// 从idx开始向下调整
int down(int idx)
{
    int current_idx = idx;
    int child_idx;
    while (current_idx <= length) {
        if (2 * current_idx + 1 <= length) {
            child_idx = a[2 * current_idx] <= a[2 * current_idx + 1] ? 2 * current_idx : 2 * current_idx + 1;
        } else if (2 * current_idx <= length) {
            child_idx = 2 * current_idx;
        } else {
            break;
        }
        if (a[current_idx] >= a[child_idx]) {
            int tmp;
            tmp = a[current_idx];
            a[current_idx] = a[child_idx];
            a[child_idx] = tmp;
            current_idx = child_idx;
        } else {
            break;
        }
    }
    return current_idx;
}

void insert(int x)
{
    kth++;
    length++;
    a[length] = x;
    // 这是调整后的idx
    int idx = up(length);
    kth_map[kth] = idx;
}

int get_min()
{
    return a[1];
}

int son_min(int idx)
{
    return a[2 * idx] <= a[2 * idx + 1] ? a[2 * idx] : a[2 * idx + 1];
}

void modify(int k, int x)
{
    int idx = kth_map[k];
    a[idx] = x;
    // TODO:
    // 这里维护kth_map我觉得有点问题
    if (a[idx] <= a[idx / 2] && idx / 2 >= 1) {
        kth_map[k] = up(idx);
    } else if (a[idx] >= son_min(idx)) {
        kth_map[k] = down(idx);
    }
}

void del_k(int k)
{
    int x = a[length];
    a[length] = M;
    length--;
    modify(k, x);
}

void del_min()
{
    del_k(1);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    memset(a, M, N * sizeof(int));

    string op;
    int x;
    int k;
    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "I") {
            cin >> x;
            insert(x);
        } else if (op == "PM") {
            int min = get_min();
            cout << min << endl;
        } else if (op == "DM") {
            del_min();
        } else if (op == "D") {
            cin >> k;
            del_k(k);
        } else if (op == "C") {
            cin >> k >> x;
            modify(k, x);
        }
    }
    return 0;
}
