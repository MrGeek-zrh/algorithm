// 区间和

#include <cstdio>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int x[N] = { 0 };
int c[N] = { 0 };

typedef pair<int, int> PII;

vector<PII> a;
map<int, int> a_map;

// 1 3 5 8 9
int get_idx_on_a(int q, int n)
{
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (a[mid].first < q) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

// 创建两个数组，大小为10^5，分别存储x和对应的c
// 每当查询l，r之间的数字之和的时候，首先查找l，r在小数组中对应的下标。下面以查找l为例：
//   1. 通过二分查找。可以用获取到右边数组最小值的模版。当l不在数组中的时候，如何判断他所在的下标区间呢？也就是当 a[L]!=l的时候，l是在哪个区间呢？
//   2. 获取到范围以后，这个范围内的数字都直接加上就行了
// 现在这种情况，只能处理没有重复，且序号递增的情况
// 想要处理重复且序号不一定递增的情况：
// 下面两个目标通过map就能实现
//  1. 去重
//  2. 排序
int main()
{
    int l = 0, r = 0;

    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &c[i]);
        // 去重，
        // map自动排序了，默认就按照升序
        a_map[x[i]] += c[i];
    }

    int idx = 0;
    for (auto pair : a_map) {
        a.push_back({ pair.first, pair.second });
        idx++;
    }
    // int idx = 0;
    // for (int i = 0; i < n; i++) {
    //     scanf("%d %d", &x[i], &c[i]);
    //     auto it = a_map.find(x[i]);
    //     if (it == a_map.end()) {
    //         a.push_back({ x[i], c[i] });
    //         a_map[x[i]] = idx++;
    //     } else {
    //         a[it->second].second += c[i];
    //     }
    // }
    // sort(a.begin(),a.end());

    int res;
    int l_idx, r_idx;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l, &r);
        res = 0;
        l_idx = get_idx_on_a(l, idx);
        if (a[l_idx].first < l) {
            l_idx = l_idx + 1;
        }

        r_idx = get_idx_on_a(r, idx);
        if (a[r_idx].first > r) {
            r_idx = r_idx - 1;
        }

        if (r < a[l_idx].first) {
            res = 0;
        } else {
            while (l_idx <= r_idx) {
                res += a[l_idx].second;
                l_idx++;
            }
        }

        printf("%d\n", res);
    }
    return 0;
}