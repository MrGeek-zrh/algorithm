#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 100010;
const int M = 2 * N;

int n, m;

// 由于是无向边，直接都插入进入吧
int h[N], e[M], ne[M], idx;

int in[N];

queue<int> q;

int p[N];

void insert(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

bool bfs()
{
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    int cnt = 0;

    while (q.size()) {
        int t = q.front();
        q.pop();
        p[cnt] = t;
        cnt++;

        for (int i = h[t]; i != -1; i = ne[i]) {
            in[e[i]]--;
            if (in[e[i]] == 0) {
                // 注意，这里放的是值，不是索引
                q.push(e[i]);
            }
        }
    }
    return cnt == n;
}

int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof(h));

    int a, b;
    while (m--) {
        cin >> a >> b;
        insert(a, b);
        in[b]++;
    }

    bool res = bfs();

    if (res) {
        for (int i = 0; i < n; i++) {
            cout << p[i] << " ";
        }
    } else {
        cout << -1;
    }
    return 0;
}