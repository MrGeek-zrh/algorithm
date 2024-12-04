#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

const int N = 510;

int a[N][N] = { 0 };
int n, m;

// 注意：不是离源点最近的距离，而是离最小生成树最近的距离
int dist[N];
// 是否被纳入了最小生成树中
int state[N] = { 0 };
// 前驱节点
int pre[N];

// 未被纳入最小生成树的节点的距离的有序列表
// dist:node
set<pair<int, int>> node_unadded;

void add_to_set(int node, int d)
{
    node_unadded.insert(make_pair(d, node));
}

int get_from_set()
{
    pair<int, int> tmp = *node_unadded.begin();
    int node = tmp.second;
    node_unadded.erase(tmp);
    return node;
}

void update_all_child_node(int node)
{
    for (int i = 1; i <= n; i++) {
        if (i == node) {
            continue;
        }
        if (state[i] == 1) {
            continue;
        }
        if (a[node][i] == 0x3f3f3f3f) {
            continue;
        }
        int old_dist = dist[i];
        dist[i] = min(old_dist, a[node][i]);
        if (old_dist >= dist[i]) {
            pre[i] = node;
            node_unadded.erase(make_pair(old_dist, i));
            add_to_set(i, dist[i]);
        }
    }
}

int node_num = 0;
int total_weight = 0;

void prim(int root)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[root] = 0;
    pre[root] = -1;
    add_to_set(root, dist[root]);
    while (!node_unadded.empty()) {
        int node = get_from_set();
        state[node] = 1;
        node_num++;
        total_weight += dist[node];
        // 更新所有未被纳入到最小生成素的相邻节点的dist，并且将其放入到node_unadded中
        update_all_child_node(node);
    }
}

int main()
{
    cin >> n >> m;
    // 只有一个顶点
    if (n == 1) {
        cout << 0;
    }
    int u, v, w;
    memset(a, 0x3f, sizeof(a));
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        // 处理自环
        if (u == v) {
            continue;
        } else {
            // 处理重边
            a[u][v] = min(a[u][v], w);
            a[v][u] = min(a[v][u], w);
        }
    }

    prim(1);

    // 如果不存在最小生成树，人为的返回0x3f3f3f3f
    if (node_num != n) {
        cout << "impossible";
    } else {
        cout << total_weight;
    }

    return 0;
}