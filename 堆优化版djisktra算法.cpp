#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 1e6;
const int M = 2 * N;

int n, m;

// 各个点到原点1的距离
int dist[N];
int state[N];

// 各个点到其孩子节点的距离
int h[N], e[M], ne[M], idx = 0;
// 顶点i到其父节点的距离
int w[M];
void insert(int x, int y, int z)
{
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx;
    w[idx] = z;
    idx++;
}

// 顶点到原点的距离：顶点的编号
typedef pair<int, int> PII;

int dij(int root)
{
    dist[root] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    // 原点到自己的距离是0
    q.push({ dist[root], root });

    // 遍历n次，每次都是选取未被访问过的点中，到原点1的距离最小的点，然后用该点更新其相邻节点到原点的距离
    while (q.size()) {
        // 找到state为0的点中，dist最小的点
        // 选择dist最小的点
        PII t = q.top();
        q.pop();
        // 判断state是否为0
        if (state[t.second] != 0) {
            continue;
        } else {
            // 找到了复合要求的点
            // 设置t的state为1
            state[t.second] = 1;
            // 更新该点相邻节点的dist
            for (int m = h[t.second]; m != -1; m = ne[m]) {
                // 易错：w的下标是idx，不是值
                dist[e[m]] = min(dist[e[m]], dist[t.second] + w[m]);
                q.push({ dist[e[m]], e[m] });
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) {
        return -1;
    } else {
        return dist[n];
    }
}

int main()
{
    cin >> n >> m;

    memset(dist, 0x3f, sizeof(dist));
    memset(w, 0x3f, sizeof(w));
    memset(h, -1, sizeof(h));

    int x, y, z;
    while (m--) {
        cin >> x >> y >> z;
        // 这里不需要再处理重边的权重选择问题了，因为对于同一条边，小根堆在排序的时候，权重小的一定是在前面的，也会被先选中
        // 被选中以后，就会被打上别访问过的标记，后续就不会在被访问了
        insert(x, y, z);
    }

    int res = dij(1);

    cout << res;

    return 0;
}