#include <cctype>
#include <charconv>
#include <cmath>
#include <codecvt>
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

const int N = 110;
const int M = 1000100;

int n, m;

// 记录迷宫
int a[N][N];

// 所有点到原点的距离，值为-1表示该点未被访问过
int d[N][N];

typedef pair<int, int> PII;

// 点的坐标：x，y
queue<PII> q;

// 按照上 下 左 右 的顺序的坐标偏移量
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int bfs()
{
    memset(d, -1, sizeof(d));
    // 将原点先push进去，方便统一操作，而不需要为了原点单独做判断
    q.push({ 0, 0 });
    d[0][0] = 0;
    PII t;
    int x, y;
    while (!q.empty()) {
        t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            x = t.first + dx[i];
            y = t.second + dy[i];
            // 坐标未越界；点未被访问过；该点可以走通
            if (x >= 0 && x < n && y >= 0 && y < m && d[x][y] == -1 && a[x][y] == 0) {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({ x, y });
            }
        }
    }
    // 一旦最短路径被找到，就会被标记为非-1，后续再有路径找到这个点的时候，不会修改这个点了，所以最终d[n-1][m-1]就是最短路径
    return d[n - 1][m - 1];
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int res = bfs();

    cout << res;

    return 0;
}