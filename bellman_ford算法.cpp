//853. 有边数限制的最短路

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 10010;

struct {
    int x, y, w;
} edges[N];

int n, m, k;

const int M = 510;
int dist[M];
int backup[M];

void bellman_ford(int start, int end, int k)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    for (int i = 1; i <= k; i++) {
        memcpy(backup, dist, sizeof(dist));
        for (int j = 1; j <= m; j++) {
            int node = edges[j].y;
            int parent_node = edges[j].x;
            int weight = edges[j].w;
            dist[node] = min(dist[node], backup[parent_node] + weight);
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].x >> edges[i].y >> edges[i].w;
    }

    bellman_ford(1, n, k);
    if (dist[n] >= 0x3f3f3f3f / 2) {
        cout << "impossible";
    } else {
        cout << dist[n];
    }
    return 0;
}