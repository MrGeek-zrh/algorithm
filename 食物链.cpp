#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

using namespace std;

const int N = 100010;
const int M = 1000100;

int n, m;

int p[N];
int b[N];

unordered_map<int, int> eat;

int query(int x)
{
    int t;
    // 改成用递归，这里就不要再用while了
    if (x != p[x]) {
        t = query(p[x]);
        b[x] += b[p[x]];
        p[x] = t;
    }
    return p[x];
}

int main()
{
    int k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    int d, x, y;
    int res = 0;
    while (k--) {
        cin >> d;
        cin >> x >> y;
        int p_x, p_y;
        p_x = query(x);
        p_y = query(y);
        if (x > n || y > n) {
            res++;
        } else {
            if (d == 1) {
                // 已经在一个集合中，但是距离却不相等，说明是假话
                if (p_x == p_y && (b[x] - b[y]) % 3) {
                    res++;
                    // 还没在一个集合中，说明还没建立关系，直接认为这个是真话
                } else if (p_x != p_y) {
                    p[p_x] = p_y;
                    b[p_x] = b[y] - b[x];
                }
            } else if (d == 2) {
                // 已经建立了关系，但是距离之差不是1，说明是假话
                if (p_x == p_y && (b[x] - b[y] - 1) % 3) {
                    res++;
                } else if (p_x != p_y) {
                    p[p_x] = p_y;
                    b[p_x] = b[y] + 1 - b[x];
                }
            }
        }
    }
    cout << res;
    return 0;
}