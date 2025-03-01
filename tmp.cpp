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

const int P = 131;
const int N = 100003;
const int M = 1000100;

int n, m;

int a[N];

void dfs(int layer, int state)
{
    if (layer == n) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!((state >> i) & 1)) {
            a[layer] = i + 1;
            dfs(layer + 1, state + (1 << i));
        }
    }
}

int main()
{
    cin >> n;

    dfs(0, 0);
    return 0;
}