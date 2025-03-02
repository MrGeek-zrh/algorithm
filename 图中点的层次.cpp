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
#include <type_traits>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

using namespace std;

const int N = 100010;
const int M = 2 * N;

int n, m;

// 由于是无向边，直接都插入进入吧
int h[N], e[M], ne[M], idx;

// res要初始化为最大的数
int res = N;

bool state[N];

void insert(int a, int b)
{
    int head = h[a];
    e[idx] = b;
    ne[idx] = head;
    h[a] = idx;
    idx++;
}
queue<int> q;

int d[N];

int bfs()
{
    q.push(1);
    // 在遍历子节点之前设置自己的状态位true，可以解决掉自环的情况
    state[1] = true;
    d[1] = 0;

    while (q.size()) {
        int t = q.front();
        q.pop();

        if (t == n) {
            return d[t];
        }

        for (int i = h[t]; i != -1; i = ne[i]) {
            if (state[e[i]]) {
                continue;
            }
            d[e[i]] = d[t] + 1;
            // 将这个节点标记为访问过，就可以解决重边的问题
            // 因为被访问过的节点，后面不会再被访问了
            state[e[i]] = true;
            q.push(e[i]);
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m;

    // 别忘了初始化头结点为-1
    memset(h, -1, sizeof(h));
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        insert(a, b);
    }

    res = bfs();
    cout << res;

    return 0;
}