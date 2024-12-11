#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int N = 2 * 100010;

int val[N];
int ne[N];
int head[N] = { 0 };
int tail[N] = { 0 };
enum { UNVISITABLE = 0, VISITABLE, VISITED };
int status[N] = { UNVISITABLE };

int current_idx = 1;

int n, m;

map<string, int> edge_times;

bool is_bin = true;

// 顶点的颜色
typedef enum { UNCOLOR = 0, RED, BLACK } COLOR;
COLOR color[N] = { UNCOLOR };

void insert(int u, int v)
{
    val[current_idx] = v;
    ne[current_idx] = -1;
    status[current_idx] = VISITABLE;

    if (head[u] == 0) {
        head[u] = current_idx;
        tail[u] = current_idx;
    } else {
        ne[tail[u]] = current_idx;
        tail[u] = current_idx;
    }

    current_idx++;
}

int node_cnt = 0;

void update_reverse_status(int root, int child)
{
    int h = head[root];
    while (h != -1) {
        if (val[h] == child) {
            status[h] = VISITED;
            return;
        }
        h = ne[h];
    }
}

bool get_child(int root, int *child, int *last_visited_idx)
{
    if (head[root] == 0) {
        return false;
    }
    int idx = *last_visited_idx;
    while (idx != -1) {
        if (status[idx] == VISITABLE) {
            status[idx] = VISITED;
            // 无向图，这里应该反向也要更新
            // 有什么办法可以较好的实现呢？
            *child = val[idx];
            *last_visited_idx = idx;
            // update_reverse_status(*child, root);
            return true;
        }
        idx = ne[idx];
    }
    return false;
}

bool has_child(int root, int *child, int *last_visited_idx)
{
    return get_child(root, child, last_visited_idx);
}

COLOR reverse_parent_color(COLOR parent_color)
{
    return parent_color == RED ? BLACK : RED;
}

void print_node(int root, int child)
{
    printf("root: %d[%d]\nchild: %d[%d]\n", root, color[root], child, color[child]);
}

// #define DEBUG

void dfs(int root, COLOR parent_color)
{
    if (!is_bin) {
        return;
    }
    int child;

    int last_visited_idx = head[root];
    while (has_child(root, &child, &last_visited_idx)) {
        if (color[child] == parent_color) {
#ifdef DEBUG
            cout << "\nnot bin =========" << endl;
            print_node(root, child);
#endif
            is_bin = false;
            return;
        } else {
            if (color[child] == UNCOLOR) {
                color[child] = reverse_parent_color(parent_color);
                node_cnt++;

#ifdef DEBUG
                print_node(root, child);
#endif

                dfs(child, color[child]);
            } else {
#ifdef DEBUG
                cout << "\n已经被上色，颜色不一直 =========" << endl;
                print_node(root, child);
#endif
                continue;
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    if (n == 1) {
        cout << "Yes";
        return 0;
    }
    int u, v;
    string s1, s2;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        // 处理自环
        if (u == v) {
            cout << "No";
            return 0;
        }
        // 处理重边
        insert(u, v);
        insert(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == UNCOLOR) {
            color[i] = RED;
            node_cnt++;
            dfs(i, RED);
        }
    }

    if (node_cnt != n) {
        cout << "No";
        return 0;
    }

    cout << (is_bin ? "Yes" : "No");

    return 0;
}
