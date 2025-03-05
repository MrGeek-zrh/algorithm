#include <algorithm>
#include <bits/stdc++.h>
#include <codecvt>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 210;

int n, m;
int k;

int cnt[N];
// 各个点到原点1的距离
int dist[N][N];

int g[N][N];

void floyd()
{
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min((dist[i][k] + dist[k][j]), dist[i][j]);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = 0x3f3f3f3f;
            }
        }
    }

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        dist[a][b] = min(dist[a][b], c);
    }

    floyd();

    while (k--) {
        int x, y;
        cin >> x >> y;
        if (dist[x][y] > 0x3f3f3f3f / 2) {
            cout << "impossible" << endl;
        } else {
            cout << dist[x][y] << endl;
        }
    }

    return 0;
}