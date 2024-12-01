#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <queue>
#include <cstring>
#include <set>
#include <utility>

using namespace std;

const int N = 100010;
int head[N] = { 0 };
int tail[N] = { 0 };
int ne[N] = { 0 };
int val[N] = { 0 };
int weight[N] = { 0 };
enum { UNVISITABLE = 0, VISITABLE, VISAITED };
int state[N] = { UNVISITABLE };
int current_idx = 1;

int n, m;

int disk[N];
int find_bool[N] = { 0 };

queue<int> q;

// 去除重边
map<string, int> arc_times;

void insert(int x, int y, int z)
{
    val[current_idx] = y;
    weight[current_idx] = z;
    ne[current_idx] = -1;
    state[current_idx] = VISITABLE;

    if (head[x] == 0) {
        // 空链表
        head[x] = current_idx;
        tail[x] = current_idx;
    } else {
        ne[tail[x]] = current_idx;
        tail[x] = current_idx;
    }

    current_idx++;
}

// disk:node
set<pair<int, int>> unfind_q;

// 用root的所有孩子节点更新disk数组
void update_disk(int root)
{
    int h = head[root];
    // 当前节点没有孩子节点
    if (h == 0) {
        return;
    }
    int t = h;
    while (t != -1) {
        int v = val[t];
        if (find_bool[v] == 1) {
            t = ne[t];
            continue;
        }
        int w = weight[t];
        int new_disk = disk[root] + w;
        int old_disk = disk[v];
        disk[v] = new_disk <= old_disk ? new_disk : old_disk;

        if (old_disk >= new_disk) {
            unfind_q.erase(make_pair(old_disk, v));
            unfind_q.insert(make_pair(disk[v], v));
        }

        t = ne[t];
    }
}

// 查看find数组还有没有没被找到最短距离的节点了
// 还有的话，找到disk最小的node，赋给node，并设该node的find状态为1
bool has_unfind_node(int *node)
{
    if (!unfind_q.empty()) {
        pair<int, int> t = *unfind_q.begin();
        *node = t.second;
        unfind_q.erase(unfind_q.begin());
        return true;
    }
    return false;
}

void dij(int root)
{
    disk[1] = 0;
    find_bool[1] = 1;
    // 更新所有孩子节点的disk
    update_disk(root);
    int node;
    while (has_unfind_node(&node)) {
        find_bool[node] = 1;
        update_disk(node);
    }
}

void print_map()
{
    for (int i = 1; i <= n; i++) {
        int tmp = head[i];
        cout << i << ":";
        while (tmp != -1 && tmp != 0) {
            cout << val[tmp] << " ";
            tmp = ne[tmp];
        }
        cout << endl;
    }
}

void print_val()
{
    for (int i = 1; i <= m; i++) {
        cout << val[i] << endl;
    }
}

void print_disk()
{
    for (int i = 1; i <= n; i++) {
        cout << disk[i] << " ";
    }
}

void update_weight(int x, int y, int z)
{
    int h = head[x];
    int tmp = h;
    while (tmp != -1) {
        if (val[tmp] == y) {
            weight[tmp] = z;
            return;
        }
        tmp = ne[tmp];
    }
}

int main()
{
    cin >> n >> m;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    int x, y, z;
    string s;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        // 要加上逗号，因为1 23 和12 3变成的字符串是一样的！！！
        s = to_string(x) +","+ to_string(y);
        // 去除自环
        if (x != y) {
            // 处理重边
            if (arc_times.count(s) == 0) {
                insert(x, y, z);
                arc_times[s] = z;
            } else if (arc_times[s] >= z) {
                update_weight(x, y, z);
                arc_times[s] = z;
            }
        }
    }
    // print_map();
    memset(disk, 0x3f, sizeof(disk));
    for (int i=2; i<=n; i++) {
        unfind_q.insert(make_pair(disk[i], i));
    }
    dij(1);
    if (disk[n] == 0x3f3f3f3f) {
        cout << -1;
    } else {
        cout << disk[n];
    }
    cout << endl;
    // print_disk();
    // cout << disk[n];
    return 0;
}
