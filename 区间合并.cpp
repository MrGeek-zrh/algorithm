#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100100;

int n;
struct range {
    int l, r;
    bool operator<(const range &w)
    {
        return l < w.l;
    }
} ranges[N];

int rights[N];

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
    }
    sort(ranges, ranges + n);

    int right_idx = 0;
    int right = ranges[0].l;
    for (int i = 0; i < n; i++) {
        if (ranges[i].l <= right) {
            // 相交
            // 进行合并，并更新右端点
            right = max(ranges[i].r, right);
            rights[right_idx] = right;
        } else {
            // 不可以合并a
            // 区间添加到 rights，作为新区间
            right = ranges[i].r;
            right_idx++;
            rights[right_idx] = right;
        }
    }

    // 注意，这里是right idx+1
    cout << right_idx + 1;

    return 0;
}