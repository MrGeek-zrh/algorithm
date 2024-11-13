#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int N = 110;
//  存储数据
int a[N][N];
// 存储节点的父亲
int parent[N][N];

int dest_x, dest_y;

queue<pair<int, int>> q;

int n, m;

enum { VISITED = -1, VISITABLE, UNVISITABLE };

int code_num(int x, int y)
{
    return (x - 1) * m + y;
}

void decode_num(int c, int *x, int *y)
{
    *x = (c % m == 0) ? c / m : c / m + 1;
    *y = c - (*x - 1) * m;
}

void make_visitable_child_in_queue(int x, int y)
{
    int child1_x = x - 1;
    int child1_y = y;

    int child2_x = x + 1;
    int child2_y = y;

    int child3_x = x;
    int child3_y = y - 1;

    int child4_x = x;
    int child4_y = y + 1;

    if (child1_x >= 1 && child1_y >= 1 && child1_x <= n && child1_y <= m && a[child1_x][child1_y] == VISITABLE) {
        q.push(make_pair(child1_x, child1_y));
        parent[child1_x][child1_y] = code_num(x, y);
    }
    if (child2_x >= 1 && child2_y >= 1 && child2_x <= n && child2_y <= m && a[child2_x][child2_y] == VISITABLE) {
        q.push(make_pair(child2_x, child2_y));
        parent[child2_x][child2_y] = code_num(x, y);
    }
    if (child3_x >= 1 && child3_y >= 1 && child3_x <= n && child3_y <= m && a[child3_x][child3_y] == VISITABLE) {
        q.push(make_pair(child3_x, child3_y));
        parent[child3_x][child3_y] = code_num(x, y);
    }
    if (child4_x >= 1 && child4_y >= 1 && child4_x <= n && child4_y <= m && a[child4_x][child4_y] == VISITABLE) {
        q.push(make_pair(child4_x, child4_y));
        parent[child4_x][child4_y] = code_num(x, y);
    }
}

void visit_queue(int *x, int *y)
{
    *x = q.front().first;
    *y = q.front().second;
    q.pop();
    a[*x][*y] = VISITED;
}

int reverse_travel(int x, int y)
{
    int times = 0;
    int parent_x = x;
    int parent_y = y;
    while (parent_x != 1 || parent_y != 1) {
        decode_num(parent[x][y], &parent_x, &parent_y);
        x = parent_x;
        y = parent_y;
        times++;
    }
    return times;
}

int bfs(int x, int y)
{
    a[x][y] = VISITED;
    int child_x, child_y;
    make_visitable_child_in_queue(x, y);
    while (!q.empty() && (visit_queue(&child_x, &child_y), child_x != dest_x || child_y != dest_y)) {
        make_visitable_child_in_queue(child_x, child_y);
    }
    return reverse_travel(child_x, child_y);
}

int main(int argc, char *argv[])
{
    cin >> n >> m;
    dest_x = n;
    dest_y = m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int current_x = 1;
    int current_y = 1;
    int times = bfs(current_x, current_y);
    cout << times << endl;

    return 0;
}
