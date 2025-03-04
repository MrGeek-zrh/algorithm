#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 100010;

int n, m;
int k;

// 各个点到原点1的距离
int dist[N];

int e[N], ne[N], idx, h[N];
int w[N];

int state[N];

void insert(int x, int y, int z)
{
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx;
    w[idx] = z;
    idx++;
}

queue<int> q;
int spfa(int root)
{
    dist[root] = 0;
    q.push(root);
    state[root] = 1;

    while (q.size()) {
        int t = q.front();
        q.pop();

        state[t] = 0;

        for (int i = h[t]; i != -1; i = ne[i]) {
            // 只有距离需要被更新的时候，并且不在队列中的时候，才将点入队。
            if (dist[e[i]] > dist[t] + w[i]) {
                dist[e[i]] = dist[t] + w[i];
                if (state[e[i]] == 0) {
                    state[e[i]] = 1;
                    q.push(e[i]);
                }
            }
        }
    }
    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(dist, 0x3f, sizeof(dist));
    memset(h, -1, sizeof(h));

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        insert(a, b, c);
    }

    int t = spfa(1);

    if (t == 0x3f3f3f3f)
        puts("impossible");
    else
        printf("%d\n", t);

    return 0;
}