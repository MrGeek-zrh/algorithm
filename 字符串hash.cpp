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

typedef unsigned long long ULL;

char a[N];
// 定义为无符号64位数，这样相当于自动mod64
ULL h[N];
// 记录第i个数的权重,方便后面确定子区间移动的位数
ULL p[N];

int main()
{
    cin >> n >> m;
    // 这个初始化很重要
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        // 1~i的hash值就是 1~i-1的hash值左移一位，在加上第i位的数值
        h[i] = h[i - 1] * P + a[i];
        p[i] = p[i - 1] * P;
    }
    int l1, r1, l2, r2;
    while (m--) {
        cin >> l1 >> r1 >> l2 >> r2;
        ULL s1 = h[r1] - h[l1 - 1] * p[r1 - l1 + 1];
        ULL s2 = h[r2] - h[l2 - 1] * p[r2 - l2 + 1];
        cout << (s1 == s2 ? "Yes" : "No") << endl;
    }

    return 0;
}