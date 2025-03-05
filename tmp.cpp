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

const int N = 100010;

int n, m;
int k;

int p[N];

struct edge {
    int a, b, w;
    bool operator<(const edge &m)
    {
        return w < m.w;
    }
} edges[N];

int find(int x)
{
    if (x != p[x]) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int kruskal()
{
    int cnt = 0;
    int res = 0;
    for (int i = 0; i < m; i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        int w = edges[i].w;
        int pa = find(a);
        int pb = find(b);
        // a和b不处于一个集合中，说明a和b至少有一个还没被加入到生成树中，那么将ab这条边加入到集合中就一定不会导致环路，所以就可以直接加入
        // 反正，ab这条边就不能加入，因为会导致环路
        if (pa != pb) {
            p[pa] = pb;
            cnt++;
            res += w;
        }
    }
    if (cnt != n - 1) {
        return 0x3f3f3f3f;
    } else {
        return res;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = { a, b, w };
    }

    sort(edges, edges + m);

    int res = kruskal();
    if (res == 0x3f3f3f3f) {
        cout << "impossible" << endl;
    } else {
        cout << res << endl;
    }

    return 0;
}