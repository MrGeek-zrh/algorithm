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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
    }
    sort(ranges, ranges + n);
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 0; i < n; i++) {
        if (heap.empty() || heap.top() >= ranges[i].l) {
            heap.push(ranges[i].r);
        } else {
            // 最小的右端点都不和这个区间的左端点相交，随机选择一个组放进去就行了。这里就直接选择最小右端点所在的组了。
            heap.pop();
            heap.push(ranges[i].r);
        }
    }
    cout << heap.size();
    return 0;
}