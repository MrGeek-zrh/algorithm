#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;
const int M = 1000100;

int n, m;

int a[N];
// k：idx  第k个插入的数：在堆中的下标
// 注意，不是用插入的数字本身作为key或者value，而是用下标，因为只有下标才是唯一的
int k_idx[N];
// idx：k
int idx_k[N];
// 整个堆的全局下标索引，也代表了当前堆的元素数量
int idx = 0;
int kth;

// 交换两个堆中位置的三种数组的值，包括元素的值，以及两个映射关系
void heap_swap(int idx_a, int idx_b)
{
    swap(idx_k[idx_a], idx_k[idx_b]);
    swap(k_idx[idx_k[idx_a]], k_idx[idx_k[idx_b]]);
    swap(a[idx_a], a[idx_b]);
}

void up(int t_idx)
{
    int t = t_idx;
    int parent = t_idx / 2;
    if (parent && a[parent] > a[t_idx]) {
        t_idx = parent;
    }
    if (t != t_idx) {
        heap_swap(t, t_idx);
        up(t_idx);
    }
}

void down(int t_idx)
{
    int t = t_idx;
    int son_l = 2 * t_idx;
    int son_r = 2 * t_idx + 1;
    if (son_l <= idx && a[t_idx] > a[son_l]) {
        t_idx = son_l;
    }
    if (son_r <= idx && a[t_idx] > a[son_r]) {
        t_idx = son_r;
    }
    if (t != t_idx) {
        heap_swap(t, t_idx);
        down(t_idx);
    }
}

int main()
{
    cin >> n;
    string op;
    int k, x;
    while (n--) {
        cin >> op;
        if (op == "I") {
            cin >> x;
            idx++;
            a[idx] = x;

            kth++;

            k_idx[kth] = idx;
            idx_k[idx] = kth;

            up(idx);
        } else if (op == "PM") {
            cout << a[1] << endl;
        } else if (op == "DM") {
            a[1] = a[idx];
            heap_swap(1, idx);
            idx--;

            down(1);
        } else if (op == "D") {
            cin >> k;
            int t_idx = k_idx[k];
            a[t_idx] = a[idx];
            heap_swap(t_idx, idx);
            idx--;
            up(t_idx);
            down(t_idx);
        } else if (op == "C") {
            cin >> k >> x;
            int t_idx = k_idx[k];
            a[t_idx] = x;
            up(t_idx);
            down(t_idx);
        }
    }
    return 0;
}