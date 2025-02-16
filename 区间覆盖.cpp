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

const int N = 100010;

struct range {
    int l, r;
    bool operator<(const range &w)
    {
        return l < w.l;
    }
} ranges[N];

int main()
{
    int s, t;
    cin >> s >> t;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
    }
    // 这里是n，不是N
    sort(ranges, ranges + n);
    int res = 0;
    bool success = false;
    for (int i = 0; i < n; i++) {
        int j = i, right = -1e9 - 10;
        // 找到最大的符合条件的右端点
        while (j < n && ranges[j].l <= s) {
            right = max(right, ranges[j].r);
            j++;
        }
        // 如果最大右端点都小于s，什么无法满足条件
        if (right < s) {
            res = -1;
            break;
        }
        // 大于等于s，区间数量+1
        res++;
        // 大于等于区间上限了，直接结束
        if (right >= t) {
            success = true;
            break;
        }
        // 处于区间中间，继续下一轮循环
        s = right;
        // 避免for i++对i的重复++
        i = j - 1;
    }
    // 当最终最大右端点也无法涵盖区间上限的时候，res要设为-1，表明不存在
    if (!success) {
        res = -1;
    }

    cout << res;
    return 0;
}