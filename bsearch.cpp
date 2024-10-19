#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;
int a[N] = { 0 };

int *find(int query, int n, int *idx_arr)
{
    int l = 0, r = n - 1;
    // 先获取区间的左端点
    // 1 2 2
    while (l < r) {
        int mid = (l + r) >> 1;
        if (a[mid] < query) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (a[l] != query) {
        idx_arr[0] = -1;
        idx_arr[1] = -1;
    }
    idx_arr[0] = l;

    // 然后获取区间的右端点
    l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (a[mid] > query) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    idx_arr[1] = l;
    if (a[l] != query) {
        idx_arr[0] = -1;
        idx_arr[1] = -1;
    }
    return idx_arr;
}

int main()
{
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int query;
    for (int i = 0; i < q; i++) {
        scanf("%d", &query);
        int idx_arr[2] = { -1 };
        find(query, n, idx_arr);
        printf("%d %d\n", idx_arr[0], idx_arr[1]);
    }

    return 0;
}