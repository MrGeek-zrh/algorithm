#include <algorithm>
#include <bits/stdc++.h>
#include <codecvt>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int N = 510;

int n, m;
int k;

int dist[N];

int g[N][N];
int state[N];

int prim()
{
    int res = 0;
    // n个顶点，所以需要n论遍历，每轮都找出当前未加入最小生成树，并且距离最小的点
    for (int i = 0; i < n; i++) {
        int t = -1;
        // 选择一个未加入最小生成树的，距离最小生成树最近的点
        for (int j = 1; j <= n; j++) {
            if (state[j] == 0 && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }
        // 将该点加入到最小生成树
        state[t] = 1;
        if (i != 0 && dist[t] == 0x3f3f3f3f) {
            return 0x3f3f3f3f;
        }
        // 第一个点的dist不能累加，因为初始化的时候被设为了0x3f3f3f3f
        if (i != 0) {
            res += dist[t];
        }
        // 用该点去更新所有其他点到最小生成树的距离
        for (int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], g[t][j]);
        }
    }
    return res;
}

int main()
{
    cin >> n >> m;

    memset(g, 0x3f, sizeof(g));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                g[i][j] = 0;
            }
        }
    }

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[b][a] = g[a][b] = min(g[a][b], c);
    }

    memset(dist, 0x3f, sizeof(dist));
    int res = prim();

    if (res > 0x3f3f3f3f / 2) {
        cout << "impossible" << endl;
    } else {
        cout << res;
    }

    return 0;
}