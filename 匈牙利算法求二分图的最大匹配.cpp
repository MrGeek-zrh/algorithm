// 匈牙利算法求二分图的最大匹配
#include <iostream>
#include <string.h>

using namespace std;

const int N = 510;
const int M = 100010;

int head[N];
int val[M];
int ne[M];
int current_idx = 1;

int n1, n2, m;

// 表示女方是否被匹配
// idx 是val的值
// - 0：未被匹配
// - 非0：被matched的值代表的元素匹配了
int matched[N] = { 0 };

// 节点是否被递归找过
// idx是val的值
int state[N] = { 0 };

void insert(int u, int v)
{
    val[current_idx] = v;
    ne[current_idx] = head[u];
    head[u] = current_idx;
    current_idx++;
}

bool find(int x)
{
    int h = head[x];
    for (int i = h; i != -1; i = ne[i]) {
        if (state[val[i]] == 0) {
            state[val[i]] = 1;
            if (matched[val[i]] == 0 || find(matched[val[i]])) {
                matched[val[i]] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin >> n1 >> n2 >> m;

    memset(head, -1, sizeof(head));
    int u, v;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        insert(u, v);
    }

    int res = 0;
    for (int i = 1; i <= n1; i++) {
        memset(state, 0, sizeof(state));
        if (find(i)) {
            res++;
        }
    }

    cout << res;

    return 0;
}