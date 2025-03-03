#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 510;
const int M = 2 * N;

int n, m;

// 各个点到原点1的距离
int dist[N];
int state[N];

// 各个点到其孩子节点的距离
// 也就是用领结矩阵的方式将图保存了下来
int g[N][N];

int dij(int root)
{
    dist[root] = 0;
    // 遍历n次，每次都是选取未被访问过的点中，到原点1的距离最小的点，然后用该点更新其相邻节点到原点的距离
    for (int i = 0; i < n; i++) {
        // 找到state为0的点中，dist最小的点
        int t = -1;
        // 每次查找都要遍历n个点
        for (int j = 1; j <= n; j++) {
            // 判断t==-1，是为了初始化这个查找过程
            if (state[j] == 0 && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        // 找到的t就是state为0，且dist最小的点
        // 设置t的state为1
        state[t] = 1;
        // 更新该点相邻节点的dist
        // 注意，这里是遍历整个图了，所以下标是从1开始了
        for (int m = 1; m <= n; m++) {
            dist[m] = min(dist[m], dist[t] + g[t][m]);
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
    memset(g, 0x3f, sizeof(g));

    int x, y, z;
    while (m--) {
        cin >> x >> y >> z;
        // 可能存在重边，所以需要注意下
        g[x][y] = min(g[x][y], z);
    }

    int res = dij(1);

    cout << res;

    return 0;
}