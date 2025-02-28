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
int cnt;

int a[N];

// 堆的数量是变化的，需要使用cnt判断，而不是n
void down(int x)
{
    int t = x;
    if (2 * x <= cnt && a[t] > a[2 * x]) {
        t = 2 * x;
    }
    if (2 * x + 1 <= cnt && a[t] > a[2 * x + 1]) {
        t = 2 * x + 1;
    }
    if (x != t) {
        swap(a[t], a[x]);
        down(t);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cnt = n;
    for (int i = n / 2; i > 0; i--) {
        down(i);
    }

    for (int i = 1; i <= m; i++) {
        cout << a[1] << " ";
        a[1] = a[cnt];
        cnt--;
        down(1);
    }

    return 0;
}