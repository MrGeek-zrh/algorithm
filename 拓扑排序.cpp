#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

// #define debug

const int N = 100010;

int n;

enum { UNVISITABLE = 0, VISITABLE, VISITED, REMOVED };
int val[N];
int ne[N];
int head[N];
int tail[N];
int status[N] = { 0 };
// 节点i的父亲的数量，每当减少一个父亲，parent_cnt[i]--;
// 下标是val
int parent_cnt[N] = { 0 };

int print_status[N] = { 0 };

int arr[N];
int print_cnt = 0;
void add_to_arr(int node)
{
    arr[print_cnt] = node;
    print_cnt++;
}

void print()
{
    for (int i = 0; i < print_cnt; i++) {
        cout << arr[i] << " ";
    }
}

bool has_no_child(int root)
{
    return head[root] == 0;
}

bool get_child(int *last_visited_idx, int root, int *child)
{
    int idx = *last_visited_idx;
    while (idx != -1) {
        if (status[idx] == VISITABLE) {
            *child = val[idx];
            status[idx] = VISITED;
            *last_visited_idx = ne[idx];
            return true;
        }
        idx = ne[idx];
    }
    return false;
}

// 将root的所有孩子节点的parent_cnt都--，不论其状态
void dec_all_child_parent_cnt(int root)
{
    int h = head[root];
    int idx = h;
    while (idx != -1) {
        parent_cnt[val[idx]]--;
        idx = ne[idx];
    }
}

void dfs(int root)
{
    if (has_no_child(root)) {
        return;
    }
    int child, last_visited_idx;
    last_visited_idx = head[root];
    dec_all_child_parent_cnt(root);
    while (get_child(&last_visited_idx, root, &child)) {
#ifdef debug
        printf("before=====parent:%d child:%d parent_cnt:%d\n", root, child, parent_cnt[child]);
#endif
#ifdef debug
        printf("after======parent:%d child:%d parent_cnt:%d\n", root, child, parent_cnt[child]);
        print();
        printf("\n");
#endif

        if (parent_cnt[child] <= 0 && print_status[child] == 0) {
            print_status[child] = 1;
            status[child] = REMOVED;
            add_to_arr(child);
            dfs(child);
        }
    }
}

int current_idx = 1;
void insert(int parent, int child)
{
    val[current_idx] = child;
    status[current_idx] = VISITABLE;
    if (head[parent] == 0) {
        head[parent] = current_idx;
        tail[parent] = current_idx;
        ne[tail[parent]] = -1;
    } else {
        ne[tail[parent]] = current_idx;
        tail[parent] = current_idx;
        ne[current_idx] = -1;
    }
    current_idx++;
}

void inc_parent_cnt(int child)
{
    parent_cnt[child]++;
}

// 所有入度为0，并且没被访问过的
int find_no_parent_node(int *root, int *last_visited_node)
{
    for (int i = *last_visited_node; i <= n; i++) {
        if (parent_cnt[i] == 0 && print_status[i] == 0) {
            *last_visited_node = i + 1;
            *root = i;
            return 0;
        }
    }
    return -1;
}

map<string, int> kv_times;

int main()
{
    int m;
    cin >> n >> m;
    string s;
    for (int i = 1; i <= m; i++) {
        int parent, child;
        cin >> parent >> child;
        if (parent == child) {
            cout << -1;
            return 0;
        }

        s = to_string(parent) + to_string(child);
        if (kv_times.count(s) == 0) {
            kv_times[s] = 1;
            inc_parent_cnt(child);
            insert(parent, child);
        }
    }

    int root;
    int start = 1;
    while (find_no_parent_node(&root, &start) != -1) {
        add_to_arr(root);
        dfs(root);
    }
    if (print_cnt == n) {
        print();
    } else {
        cout << -1;
    }
    return 0;
}