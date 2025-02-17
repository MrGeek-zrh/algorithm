#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100100;

int n;
int b[2 * N], idx;

// 还可以通过最大重叠区间数量来求：
// 最大重叠区间数量是在按照左端点进行排序以后，某一个时刻，最多重叠的区间数，那么就至少需要这些数量的分组，将这些重叠区间分别放在各个组里。再少于这个数量的组，在最大重叠区间数量的情况下，就无法满足组内没有重叠了。
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        // 如果题目将端点重叠定义为不相交，那么将左端点标记为奇数，右端点为偶数即可：比如[1,4] [4,5]:这时候，就变成了：[3,8] [9,11] 边界就不相交了，就符合条件了
        b[idx++] = l * 2; //标记左端点为偶数。
        b[idx++] = r * 2 + 1; // 标记右端点为奇数。
    }

    sort(b, b + idx);

    int res = 1, t = 0;
    for (int i = 0; i < idx; i++) {
        if (b[i] % 2 == 0)
            t++;
        else
            t--;
        res = max(res, t);
    }
    printf("%d\n", res);
    return 0;
}