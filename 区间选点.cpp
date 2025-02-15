#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

struct range {
    int l, r;
    bool operator<(const range &W)
    {
        return r < W.r;
    }
} range[N];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> range[i].l >> range[i].r;
    }
    sort(range, range + n);
    int res = 0;
    int right = -1e9 - 10;
    for (int i = 0; i < n; i++) {
        // 这里是range[i].l,不是r，因为只有当l大于前一个区间的r的时候，才需要更新。
        if (right < range[i].l) {
            res++;
            right = range[i].r;
        }
    }
    cout << res;
    return 0;
}
