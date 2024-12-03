#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

const int N = 100010;

int head[N] = { 0 };
int tail[N] = { 0 };
int val[N];
int ne[N];
int weight[N];

// 当前节点有没有被加入到队列中过
int state[N] = { 0 };

int n, m;

// 边：权重
map<string, int> arc_w;

int dist[N];

int current_idx = 1;
void insert(int x, int y, int w)
{
    val[current_idx] = y;
    ne[current_idx] = -1;
    weight[current_idx] = w;

    if (head[x] == 0) {
        head[x] = current_idx;
        tail[x] = current_idx;
    } else {
        ne[tail[x]] = current_idx;
        tail[x] = current_idx;
    }
    current_idx++;
}

// 更新邻接表的权重
void update_w(int x, int y, int w)
{
    int h = head[x];
    if (h == 0) {
        return;
    }
    int tmp = h;
    while (tmp != -1) {
        if (val[tmp] == y) {
            weight[tmp] = w;
            return;
        }
        tmp = ne[tmp];
    }
}

queue<int> q;

void add_to_q(int node)
{
    q.push(node);
}

int get_front()
{
    int node = q.front();
    q.pop();
    return node;
}

void update_childs(int parent)
{
    int h = head[parent];
    if (h == 0) {
        return;
    }
    int tmp = h;
    while (tmp != -1) {
        int old_dist = dist[val[tmp]];
        dist[val[tmp]] = min(old_dist, dist[parent] + weight[tmp]);
        if (dist[val[tmp]] != old_dist) {
            if (state[val[tmp]] == 0) {
                add_to_q(val[tmp]);
                state[val[tmp]] = 1;
            }
        }
        tmp = ne[tmp];
    }
}

void spfa(int root)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[root] = 0;
    state[root] = 1;
    add_to_q(root);
    while (!q.empty()) {
        int parent = get_front();
        state[parent] = 0;
        // 使用从队列取出的节点，更新其孩子节点。孩子节点的dist如果被更新了，就将其加入到队列中
        update_childs(parent);
    }
}

int main()
{
    cin >> n >> m;

    int x, y, z;
    string s;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        // 处理自环
        if (x == y) {
            if (n == 1) {
                cout << 0;
                return 0;
            }
            continue;
        }
        // 处理重边
        s = to_string(x) + "," + to_string(y);
        if (arc_w.count(s) == 0) {
            // 不是重边
            arc_w[s] = z;
            insert(x, y, z);
        } else {
            // 是重边
            // 如果新边权重更小，则更新邻接表和arc_w
            if (z < arc_w[s]) {
                update_w(x, y, z);
                arc_w[s] = z;
            }
            // 否则保持原来的最小边权重
        }
    }

    spfa(1);

    if (dist[n] == 0x3f3f3f3f) {
        cout << "impossible";
    } else {
        cout << dist[n];
    }

    return 0;
}