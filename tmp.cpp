#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int N = 100010;
const int M = 2 * 100000 + 10;

struct edge {
    int x;
    int y;
    int w;
    bool operator<(const edge &e)
    {
        return this->w < e.w;
    }
} edge[M];

int n, m;

int res = 0;
int total_cnt = 0;

int parent[N];

int find(int x)
{
    int p = x;
    int t;
    while (parent[p] != p) {
        t = p;
        p = parent[p];
        parent[t] = parent[p];
    }
    return p;
}

bool all_in_same_set(int x, int y)
{
    int p_x = find(x);
    int p_y = find(y);
    return (p_x == p_y);
}

// y加到x集合
void uni(int root, int y)
{
    int p_y = find(y);
    parent[p_y] = root;
}

void kruskal(int mgt_root)
{
    int x, y, w;
    string s;

    for (int i = 1; i <= m; i++) {
        x = edge[i].x;
        y = edge[i].y;
        w = edge[i].w;

        if (all_in_same_set(x, y)) {
            continue;
        } else {
            uni(mgt_root, x);
            uni(mgt_root, y);
            total_cnt++;
            res += w;
        }
    }
}

int main()
{
    cin >> n >> m;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    int x, y, w;
    string s;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> w;
        edge[i] = { x, y, w };
    }

    sort(edge + 1, edge + m + 1);

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    int mgt_root = 0;
    kruskal(mgt_root);
    if (total_cnt < n - 1) {
        cout << "impossible";
    } else {
        cout << res;
    }

    return 0;
}