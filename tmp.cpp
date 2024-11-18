// 树的重心
#include <iostream>
#include <map>

using namespace std;

const int N = 100010;
enum { UNVISITABLE = 0, VISITABLE = 1, VISITED };
int status[2 * N] = { UNVISITABLE };
int val[2 * N] = { 0 };
int ne[2 * N] = { -1 };
// 存储的是ne的下标
int head[N] = { 0 };
int tail[N] = { 0 };

int max_cnt = N;
int gravity = UNVISITABLE;

int cnt_arr[2 * N] = { 0 };

int n;

bool is_leaf(int root)
{
    int h = head[root];
    if (h == 0) {
        return true;
    } else {
        return false;
    }
}

bool get_child(int root, int *child)
{
    int h = head[root];
    int idx = h;
    while (idx != -1) {
        if (status[idx] == VISITABLE) {
            *child = val[idx];
            status[idx] = VISITED;
            // 如果是奇数下标，反向边是idx+1；如果是偶数下标，反向边是idx-1
            int reverse_idx = (idx % 2 == 1) ? idx + 1 : idx - 1;
            status[reverse_idx] = VISITED;
            return true;
        }
        idx = ne[idx];
    }
    return false;
}

// 所有最大值中的最小值
int get_max()
{
    return max_cnt;
}

int dfs(int root)
{
    int child_max_cnt = 0;
    int inner_max_cnt = 0;
    if (is_leaf(root)) {
        cnt_arr[root] = 1;
        return 1;
    }
    int child;
    while (get_child(root, &child)) {
        int child_cnt = dfs(child);
        cnt_arr[root] += child_cnt;
        child_max_cnt = child_max_cnt > child_cnt ? child_max_cnt : child_cnt;
    }
    // 加上自己
    cnt_arr[root] += 1;
    int left_cnt = n - cnt_arr[root];
    inner_max_cnt = left_cnt > child_max_cnt ? left_cnt : child_max_cnt;

    max_cnt = max_cnt < inner_max_cnt ? max_cnt : inner_max_cnt;

    gravity = max_cnt < inner_max_cnt ? gravity : root;
    return cnt_arr[root];
}

void print()
{
    for (int i = 1; i <= n; i++) {
        cout << "cnt arr:" << cnt_arr[i] << endl;
    }
}

int current_idx = 1;
void insert(int x, int y)
{
    int h = head[x];
    int t = tail[x];

    status[current_idx] = VISITABLE;
    val[current_idx] = y;

    if (h == 0) {
        head[x] = current_idx;
        tail[x] = current_idx;
        ne[tail[x]] = -1;
    } else {
        ne[t] = current_idx;
        ne[current_idx] = -1;
        tail[x] = current_idx;
    }
    current_idx++;
}

int main(int argc, char *argv[])
{
    cin >> n;
    int x, y;
    tail[1] = 1;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        insert(x, y);
        insert(y, x);
    }

    gravity = 1;
    dfs(1);
    // print();

    int max = get_max();
    cout << max;

    return 0;
}
