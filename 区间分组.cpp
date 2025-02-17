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
} range[N];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> range[i].l >> range[i].r;
    }
    sort(range, range + n);
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 0; i < n; i++) {
        // 和最小右端点都相交，和其它组肯定也相交
        // 放到新组里
        if (heap.empty() || heap.top() >= range[i].l) {
            heap.push(range[i].r);
        } else {
            // 和最小的右端点不相交，直接加入到最小右端点
            heap.pop();
            heap.push(range[i].r);
        }
    }
    cout << heap.size();
    return 0;
}