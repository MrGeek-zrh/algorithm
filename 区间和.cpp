#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

struct op {
    int x, c;
    bool operator<(const op &w)
    {
        return x < w.x;
    }
} ops[N] = { { 0, 0 } };
int sum[N];

int n, m;
// 找下边界
int find_down(int x)
{
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        // 以后固定下来这种写法， 都是考虑全大于和全小于的区间
        if (ops[mid].x < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (ops[l].x < x) {
        return l + 1;
    }
    return l;
}

// 1 3 4.    2
int find_up(int x)
{
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (ops[mid].x > x) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    if (ops[l].x > x) {
        return l - 1;
    }
    return l;
}

int main()
{
    // 离散化基本思路：将巨大数组的下标和值都分别存在两个数组中，由于下标是递增的，所以可以用二分查找进行下标位置的定位，找到下标的位置以后，再去获取对应的在另一个数组中的值
    // 由于可能包含重复，所以需要分别查找上边界和下边界
    cin >> n >> m;
    int x, c;
    for (int i = 1; i <= n; i++) {
        cin >> x >> c;
        ops[i] = { x, c };
    }
    sort(ops + 1, ops + n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + ops[i].c;
    }
    int l, r;
    for (int i = 1; i <= m; i++) {
        cin >> l >> r;
        int idx_l = find_down(l);
        int idx_r = find_up(r);

        if (idx_l > n || idx_r < 1 || idx_l > idx_r) {
            cout << "0" << endl;
            continue;
        } else {
            cout << sum[idx_r] - sum[idx_l - 1] << "\n";
        }
    }

    return 0;
}