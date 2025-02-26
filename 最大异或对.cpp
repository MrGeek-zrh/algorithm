#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int N = 100010;
const int M = 31 * N;

int n;

int idx = 1, son[M][2];

int a[N];

void insert(int x)
{
    int parent = 0;
    for (int i = 30; i >= 0; i--) {
        if (son[parent][(x >> i) & 1] == 0) {
            son[parent][(x >> i) & 1] = idx;
            idx++;
        }
        parent = son[parent][(x >> i) & 1];
    }
}

int query(int x)
{
    int res = 0;
    int parent = 0;
    for (int i = 30; i >= 0; i--) {
        // 这里要注意是！，不是~，因为这里不是位的取反操作，是整数的取反操作
        if (son[parent][!((x >> i) & 1)] != 0) {
            res += (1 << i);
            parent = son[parent][!((x >> i) & 1)];
        } else {
            parent = son[parent][(x >> i) & 1];
        }
    }
    return res;
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        insert(a[i]);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, query(a[i]));
    }
    cout << res;

    return 0;
}