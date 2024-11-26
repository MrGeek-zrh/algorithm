// 847. 图中点的层次
#include <cstddef>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

const int N = 100010;

// 是不是找到了结果
bool flag = false;

enum { UNVISITABLE = 0, VISITABLE, VISITED };

int status[N] = { UNVISITABLE };
// 下标是idx，值是节点的编号
int val[N];
int ne[N] = { -1 };
// 存储的是val的下标
int head[N] = { -1 };
int tail[N] = { -1 };

int dest;

// 相邻结点的编号都放这里
queue<int> child_num;

// 1到每个点的距离记录下来
int dis[N] = { 0 };

map<string, int> kv_times;

// #define debug

int current_idx = 1;
void insert(int x, int y)
{
    // 自环
    if (x == y) {
        return;
    }
    val[current_idx] = y;
    status[current_idx] = VISITABLE;
    if (head[x] == 0) {
        head[x] = current_idx;
        tail[x] = current_idx;
        ne[tail[x]] = -1;
    } else {
        ne[tail[x]] = current_idx;
        ne[current_idx] = -1;
        tail[x] = current_idx;
    }
    current_idx++;
}

int get_node()
{
    int child = child_num.front();
    child_num.pop();
    return child;
}

bool get_child(int *last_visited_idx, int root, int *child)
{
    int tmp = *last_visited_idx;
    while (tmp != -1) {
        if (status[tmp] == VISITABLE) {
            *child = val[tmp];
            status[tmp] = VISITED;
            *last_visited_idx = ne[tmp];
            return true;
        }
        tmp = ne[tmp];
    }
    return false;
}

bool has_existed(int x)
{
    return dis[x] != 0;
}

// 将孩子节点都放到队列中，并且要设置status为VISITED
// 还需要维护节点的dis数组
void make_child_in_queue(int root)
{
    int child;
    int last_visited_idx = head[root];
    while (get_child(&last_visited_idx, root, &child)) {
        child_num.push(child);
        // BUG:
        if (has_existed(child)) {
            dis[child] = dis[child] > dis[root] + 1 ? dis[root] + 1 : dis[child];
        } else {
            dis[child] = dis[root] + 1;
        }

#ifdef debug
        cout << "root:" << root << " child:" << child << " dis:" << dis[child] << endl;
        cout << endl;
#endif

        if (child == dest) {
            flag = true;
            cout << dis[child];
            return;
        }
    }
}

void dfs(int root)
{
    make_child_in_queue(root);
    while (!child_num.empty()) {
        int child = get_node();
        make_child_in_queue(child);
        if (flag) {
            return;
        }
    }
    cout << -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    dest = n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    int x, y;
    string s;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        s = to_string(x) + to_string(y);
        if (kv_times.count(s) == 0) {
            // 去除重边
            kv_times[s] = 1;
            insert(x, y);
        }
    }

    dis[1] = 0;
    dfs(1);
    return 0;
}