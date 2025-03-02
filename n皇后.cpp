#include <cctype>
#include <charconv>
#include <cmath>
#include <codecvt>
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

const int N = 9;
const int M = 1000100;

int n, m;

int a[N];
char p[N][N];

// 当前列有没有皇后；当前点的对角线有没有皇后；当前点的反对角线有没有皇后
int col[N], dg[N], rdg[N];

void dfs(int layer)
{
    if (layer == n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << p[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    int x = layer;
    for (int i = 0; i < n; i++) {
        if (col[i] == 0 && dg[i - x + n] == 0 && rdg[i + x] == 0) {
            p[x][i] = 'Q';
            col[i] = dg[i - x + n] = rdg[x + i] = 1;
            dfs(x + 1);
            p[x][i] = '.';
            col[i] = dg[i - x + n] = rdg[x + i] = 0;
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = '.';
        }
    }
    dfs(0);
    return 0;
}