// 数组模拟堆
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

const int N = 100010;
const long M = -1e9;
int a[N] = { M };

// 第k次插入的数的索引
// kth: index
map<int, int> kth_map;
// index：kth
map<int, int> idx_map;

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

            kth_map[idx_map[current_idx]] = parent_idx;
            kth_map[idx_map[parent_idx]] = current_idx;
            tmp = idx_map[current_idx];
            idx_map[current_idx] = idx_map[parent_idx];
            idx_map[parent_idx] = tmp;

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
            // 没有孩子节点了，不需要在调整了
            break;
        }
        if (a[current_idx] >= a[child_idx]) {
            int tmp;
            tmp = a[current_idx];
            a[current_idx] = a[child_idx];
            a[child_idx] = tmp;

            kth_map[idx_map[current_idx]] = child_idx;
            kth_map[idx_map[child_idx]] = current_idx;
            tmp = idx_map[current_idx];
            idx_map[current_idx] = idx_map[child_idx];
            idx_map[child_idx] = tmp;

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
    kth_map[kth] = length;
    idx_map[length] = kth;
    // 这是调整后的idx
    up(length);
}

int get_min()
{
    return a[1];
}

// 确定有孩子节点的情况下
int son_min(int idx)
{
    if (2 * idx + 1 <= length) {
        return a[2 * idx] <= a[2 * idx + 1] ? a[2 * idx] : a[2 * idx + 1];
    } else {
        return a[2 * idx];
    }
}

void modify(int k, int x)
{
    int idx = kth_map[k];
    a[idx] = x;
    if (idx / 2 >= 1 && a[idx] <= a[idx / 2]) {
        up(idx);
    } else if ((2 * idx <= length || 2 * idx + 1 <= length) && a[idx] >= son_min(idx)) {
        down(idx);
    }
}

void del_k(int k)
{
    int x = a[length];
    a[length] = M;
    // 将最后一个元素放到第k个插入的元素的位置上，并更新对应的索引关系
    kth_map[idx_map[length]] = kth_map[k];
    idx_map[kth_map[k]] = idx_map[length];
    length--;
    if (length == 0) {
        return;
    } else {
        modify(k, x);
    }
}

void del_min()
{
    del_k(idx_map[1]);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

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
